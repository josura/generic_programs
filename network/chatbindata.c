#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>
#include<netdb.h>

#define SIZE 100

struct thread_data{
    int socketfd;
    struct sockaddr_in rem_addr;
};

struct addrinfo {
    int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
    int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
    int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
    int              ai_protocol;  // use 0 for "any"
    size_t           ai_addrlen;   // size of ai_addr in bytes
    struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
    char            *ai_canonname; // full canonical hostname

    struct addrinfo *ai_next;      // linked list, next node
};
int getaddrinfo(const char *node, const char *service,
                       const struct addrinfo *hints,
                       struct addrinfo **res);


int netSock;
struct addrinfo hints,*res;
struct sockaddr_in self_addr,remot_addr;

void parse_args_addr(int argc, char **argv) {
	if(argc < 2){
	    printf("Use:  PORT_ascolto");
	    exit(0);
    }
    char persona_ip[100];
	memcpy(persona_ip, argv[1], strlen(argv[1]));
    bzero(&hints,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;        //telling the program to bind to the IP of the host it's running on
    getaddrinfo(NULL,argv[1],&hints,&res);    //if we want a specific IP we drop AI_PASSIVE end input in the first argument
    bzero( &self_addr,sizeof(self_addr));
    self_addr.sin_family = AF_INET; 
	self_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	self_addr.sin_port = htons(atoi(argv[1]));
    //if((netSock=socket(AF_INET,SOCK_STREAM,0))<0)
    if((netSock=socket(res->ai_family,res->ai_socktype,res->ai_protocol))<0)
	{
		perror("Client Error: Socket not created succesfully");
		exit (0);
	}
    else{
        printf("Socket succesfully created... \n");
    }
    // Binding newly created socket to given IP and verification 
    if ((bind(netSock, res->ai_addr, res->ai_addrlen)) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else printf("Socket successfully binded..\n");
}

void errore(){
    printf("errore %s \n",strerror(errno));     //si puo usare perror ma chissa se funziona
}

void *ReceivingMessage(void *threadid){
    struct thread_data* tid = (struct thread_data*)threadid;   //non li sto usando ma per usarli li posso passare in questo modo
    char buff[SIZE];
    bzero();
    while(1){
        n = recv(tid->socketfd,buff,SIZE-1,0);
        if(n==0) continue;
        mesg[n] = 0;
        printf("\nPid=%d: received from %s:%d \n the message: %s\n",getpid(),inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), mesg );
    }
    pthread_exit(NULL);
 }



int main(int argc, char **argv){
    parse_args_addr(argc,argv);	
    int error;
    pthread_t thread;
    struct thread_data* pdati;
    struct thread_data dati;
    pdati=&dati;
    if ((listen(netSock,5)) != 0) { 
        printf("Listen failed...\n"); 
        errore();
        exit(1); 
    } 
    else
        printf("Server listening..\n"); 
    int len = sizeof(remot_addr);
    dati.socketfd=accept(netSock,&remot_addr,len);
    dati.rem_addr=remot_addr;
    rc = pthread_create(&thread, NULL, ReceivingMessage(), (void *)pdati);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        return 0;
    }
    char line[999];
    while (fgets(line,999,stdin) != NULL){
        printf("\nsended from %s:%d the following: %s\n", 
	    inet_ntoa(self_addr.sin_addr), ntohs(self_addr.sin_port), line );
        send(dati.socketfd,line,strlen(sendline),0);
   }
    pthread_exit(NULL);
}

