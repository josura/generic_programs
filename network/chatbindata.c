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


int netSock;
struct addrinfo hints,*res;
struct sockaddr_in self_addr,remot_addr;

void parse_args_addr(int argc, char **argv) {
	if(argc < 2){
	    printf("Use:  PORT_ascolto");
	    exit(0);
    }
    char persona_ip[100];
    struct addrinfo * rp;
	memcpy(persona_ip, argv[1], strlen(argv[1]));
    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;        //telling the program to bind to the IP of the host it's running on
    getaddrinfo(NULL,argv[1],&hints,&res);    //if we want a specific IP we drop AI_PASSIVE end input in the first argument
    bzero( &self_addr,sizeof(self_addr));
    self_addr.sin_family = AF_INET;
	self_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	self_addr.sin_port = htons(atoi(argv[1]));
    //if((netSock=socket(AF_INET,SOCK_STREAM,0))<0)
    /*if((netSock=socket(res->ai_family,res->ai_socktype,res->ai_protocol))<0)
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
    else printf("Socket successfully binded..\n");*/
    for (rp = res; rp != NULL; rp = rp->ai_next) {
               netSock = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (netSock == -1)
                   continue;

               if (bind(netSock, rp->ai_addr, rp->ai_addrlen) < 0)
                   break;                  /* Success */
               close(netSock);
           }
    if (rp == NULL) {               /* No address succeeded */
               fprintf(stderr, "Could not bind\n");
               exit(EXIT_FAILURE);
           }

    freeaddrinfo(res);           /* No longer needed */
}

void errore(){
    printf("errore %s \n",strerror(errno));     //si puo usare perror ma chissa se funziona
}

void *ReceivingMessage(void *threadid){
    struct thread_data* tid = (struct thread_data*)threadid;   //non li sto usando ma per usarli li posso passare in questo modo
    char buff[SIZE];
    bzero(buff,SIZE);
    while(1){
        int n = recv(tid->socketfd,buff,SIZE-1,0);
        if(n==0) continue;
        buff[n] = 0;
        printf("\nPid=%d: received from %s:%d \n the message: %s\n",getpid(),inet_ntoa(tid->rem_addr.sin_addr), ntohs(tid->rem_addr.sin_port), buff );
    }
    pthread_exit(NULL);
 }



int main(int argc, char **argv){
    parse_args_addr(argc,argv);
    int error;
    pthread_t thread;
    struct thread_data dati;
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
    int rc = pthread_create(&thread, NULL, ReceivingMessage, &dati);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        return 0;
    }
    char line[999];
    while (fgets(line,999,stdin) != NULL){
        printf("\nsended from %s:%d the following: %s\n",
	    inet_ntoa(self_addr.sin_addr), ntohs(self_addr.sin_port), line );
        send(dati.socketfd,line,strlen(line),0);
   }
    pthread_exit(NULL);
}
