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
#include<stdbool.h>

#define SIZE 100

struct thread_data{
    int socketfd;
    struct sockaddr_in rem_addr;
};


int socketto;
struct sockaddr_in self_addr,remot_addr;

void errore(){
    printf("errore %s \n",strerror(errno));     //si puo usare perror ma chissa se funziona
}

void *ReceivingMessage(void *threadid){
    struct thread_data* tid = (struct thread_data*)threadid;   //non li sto usando ma per usarli li posso passare in questo modo
    char buff[SIZE],prec[SIZE];
    bzero(buff,SIZE);
    while(1){
        int n = recv(tid->socketfd,buff,SIZE-1,0);
        if(n==0) continue;
        buff[n] = 0;
	 if(strlen(buff)==0)continue;
	    if(strncmp(buff,prec,SIZE-2)==0)continue;
	 if(strncmp(buff,"quit",2)==0){close(tid.socketfd);printf("chat chiusa\n");return;}
        printf("\nPid=%d: received from %s:%d \n the message: %s\n",getpid(),inet_ntoa(tid->rem_addr.sin_addr), ntohs(tid->rem_addr.sin_port), buff );
    	strcpy(prec,buff);
    }
    pthread_exit(NULL);
}

void bindolocaleTCP(int* sockfd,char* porta){
    struct addrinfo hints,*res,* rp;
    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;        //telling the program to bind to the IP of the host it's running on
    getaddrinfo(NULL,porta,&hints,&res);    //if we want a specific IP we drop AI_PASSIVE end input in the first argument
    for (rp = res; rp != NULL; rp = rp->ai_next) {
               *sockfd = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (*sockfd == -1)
                   continue;

               if (bind(*sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   break;                  /* Success */
               close(*sockfd);
           }
    if (rp == NULL) {               /* No address succeeded */
               fprintf(stderr, "Could not bind\n");
               exit(EXIT_FAILURE);
           }

    freeaddrinfo(res);           /* No longer needed */
}

void connettoremotoTCP(int *socketto,const char *indirizzo_rem ,int porta){

}

bool tryconnect(int argc, char **argv){
    struct addrinfo hints,*res,* rp;
    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    getaddrinfo(argv[1],argv[2],&hints,&res);
    bzero( &remot_addr,  sizeof(remot_addr));
        remot_addr.sin_family= AF_INET;
        remot_addr.sin_addr.s_addr= inet_addr(argv[1]);
        remot_addr.sin_port=htons(atoi(argv[2]));
    struct timeval tim;
    tim.tv_sec=0;
    tim.tv_usec=1;
    self_addr.sin_family = AF_INET;
	self_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	self_addr.sin_port = htons(atoi(argv[2]));
    for (rp = res; rp != NULL; rp = rp->ai_next) {
               socketto = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (socketto == -1)
                   continue;

                setsockopt(socketto,SOL_SOCKET,SO_RCVTIMEO,&tim,sizeof (tim));
               if (connect(socketto, rp->ai_addr, rp->ai_addrlen)< 0){
		    freeaddrinfo(res);
                    return false;   //non è riuscito a connettere

                } else {
                    break;                  /* Success */
                }
               close(socketto);
           }
    if (rp == NULL) {               /* No address succeeded */
               fprintf(stderr, "Could not connect\n");
               exit(EXIT_FAILURE);
           }

    freeaddrinfo(res);           /* No longer needed */
    return true;
}

bool trybind(int argc, char **argv){
	bindolocaleTCP(&socketto,argv[1]);
	pthread_t thread;
    	struct thread_data dati;
    	if ((listen(socketto,5)) != 0) {
        	printf("Listen failed...\n");
        	errore();
        	exit(1);
    	}
    	else
        	printf("Server listening..\n");
    	int len = sizeof(remot_addr);
    	dati.socketfd=accept(socketto,(struct sockaddr*)&remot_addr,&len);
    	dati.rem_addr=remot_addr;
    	int rc = pthread_create(&thread, NULL, ReceivingMessage, &dati);
    	if (rc){
        	printf("ERROR; return code from pthread_create() is %d\n", rc);
        	return 0;
    	}
    	char line[999];
    	while (fgets(line,999,stdin) != NULL){
                if(strncmp(line,"quit",2)==0){close(dati.socketfd);printf("chat chiusa\n");return;}
                printf("\t sended to %s:%d\n",
                inet_ntoa(dati.rem_addr.sin_addr), ntohs(dati.rem_addr.sin_port) );
		if(strlen(line)==0)continue;
                send(dati.socketfd,line,strlen(line),0);
   	}
	return true;
}

void parse_args_addr(int argc, char **argv) {
	if(argc < 2){
	    printf("Use:  IP_remoto PORT_ascolto");
	    exit(0);
    }
    bool connesso=tryconnect(argc,argv);
    if(connesso==true){
        printf("connesso a %s : %s \n",argv[1],argv[2]);
        struct thread_data dati;
        dati.socketfd=socketto;
        dati.rem_addr=remot_addr;
            pthread_t threadRec;
            int rc=pthread_create(&threadRec, NULL, ReceivingMessage,&dati);
            if (rc){
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                errore();
                return;
            }
            char line[999];
            while (fgets(line,999,stdin) != NULL){
                if(strncmp(line,"quit",2)==0){close(dati.socketfd);printf("chat chiusa\n");return;}
                printf("\t sended to %s:%d\n",
                inet_ntoa(dati.rem_addr.sin_addr), ntohs(dati.rem_addr.sin_port) );
                send(dati.socketfd,line,strlen(line),0);

            }
    }
    else {
            printf("connesione non riuscita, procedo con il bind\n");
            trybind(argc,argv);
    }

}


int main(int argc, char **argv){
    parse_args_addr(argc,argv);
    int error;

    pthread_exit(NULL);
}

