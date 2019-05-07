#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>

#define SIZE 100

struct thread_data{
    int socketfd;
    struct sockaddr_in rem_addr;
};

int netSock;
struct addrinfo hints,*res;
struct sockaddr_in persona;
struct sockaddr_in self_addr;

void parse_args_addr(int argc, char **argv,struct thread_data* datiRem) {
	if(argc < 3){
	    printf("Use: IP_dest PORT_dest");
	    return 0;
    }
    struct addrinfo * rp;
    char persona_ip[100];
	memcpy(persona_ip, argv[1], strlen(argv[1]));
    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    getaddrinfo(argv[1],argv[2],&hints,&res);
    bzero( &persona,  sizeof(struct sockaddr_in));
    bzero( &datiRem->rem_addr,  sizeof(persona));
        datiRem->rem_addr.sin_family=persona.sin_family = AF_INET;
        datiRem->rem_addr.sin_addr.s_addr=persona.sin_addr.s_addr = inet_addr(argv[1]);
        datiRem->rem_addr.sin_port=persona.sin_port = htons(atoi(argv[2]));

    self_addr.sin_family = AF_INET;
	self_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	self_addr.sin_port = htons(atoi(argv[2]));
    netSock=-1;
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
    struct thread_data dati;
    dati.socketfd=1;
    parse_args_addr(argc,argv,&dati);
    int error;
    struct sockaddr_in persona;
    pthread_t threadRec;
    int rc=pthread_create(&threadRec, NULL, ReceivingMessage,&dati);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        errore();
        return 0;
    }
    char line[999];
    while (fgets(line,999,stdin) != NULL){
        send(netSock,line,strlen(line),0);
        printf("\nsended to %s:%d the following: %s\n",
	    inet_ntoa(persona.sin_addr), ntohs(persona.sin_port),line );
   }
    pthread_exit(NULL);
}
