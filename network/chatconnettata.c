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

#define SIZE 100

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
struct sockaddr_in persona;
struct sockaddr_in self_addr;

void parse_args_addr(int argc, char **argv) {
	if(argc < 3){
	    printf("Use: IP_dest PORT_dest");
	    return 0;
    }
    addrinfo * rp;
    char persona_ip[100];
	memcpy(persona_ip, argv[1], strlen(argv[1]));
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    getaddrinfo(argv[1],atoi(argv[2]),&hints,&res);
    bzero( &persona,  sizeof(dest_addr));
        persona.sin_family = AF_INET;
        persona.sin_addr.s_addr = inet_addr(argv[1]);
        persona.sin_port = htons(atoi(argv[2]));
	
    self_addr.sin_family = AF_INET; 
	self_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	self_addr.sin_port = htons(atoi(argv[2]));
    for (rp = res; rp != NULL; rp = rp->ai_next) {
               netSock = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (netSock == -1)
                   continue;

               if (connect(netSock, rp->ai_addr, rp->ai_addrlen) < 0)
                   break;                  /* Success */

               close(netSock);
           }
    if (rp == NULL) {               /* No address succeeded */
               fprintf(stderr, "Could not connect\n");
               exit(EXIT_FAILURE);
           }

    freeaddrinfo(res);           /* No longer needed */
}

void errore(){
    printf("errore %s \n",strerror(errno));
}

void *ReceivingMessage(void *threadid)
 {
    long tid;
    struct thread_data* tid = (struct thread_data*)threadid;   //non li sto usando ma per usarli li posso passare in questo modo
    char buff[SIZE];
    bzero();
    while(1){
        n = recv(netSock,buff,SIZE,0);
        if(n==0) continue;
        mesg[n] = 0;
        printf("\nPid=%d: received from %s:%d \n the message: %s\n",getpid(),inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), mesg );
    }
    pthread_exit(NULL);
 }



int main(int argc, char **argv){
    parse_args_addr(argc,argv);	
    int netSock,error;
    struct sockaddr_in persona;
    pthread_t thread;
    struct thread_data* pdati;
    struct thread_data dati;
    dati.boh=0;
    dati.address=persona;
    pdati=&dati;
    netSock=socket(AF_INET,SOCK_STREAM,0);
    if(netSock<0)
	{
		perror("Client Error: Socket not created succesfully");
		return 0;
	}
    else{
        printf("Socket succesfully created... \n");
    }
    // Binding newly created socket to given IP and verification 
    if ((bind(netSock, (struct sockaddr*)&persona, sizeof(persona))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else printf("Socket successfully binded..\n");
    rc = pthread_create(&thread, NULL, ReceivingMessage(), (void *)pdati);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        return 0;
    }
    char line[999];
    while (fgets(line,999,stdin) != NULL){
        send(netSock,line,strlen(sendline),0);
        printf("\nreceived from %s:%d the following: %s\n", 
	    inet_ntoa(persona.sin_addr), ntohs(persona.sin_port), recvline );
   }
    pthread_exit(NULL);
}

