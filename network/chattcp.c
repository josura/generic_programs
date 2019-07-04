       #include <stdlib.h>
       #include <stdio.h>
       #include <unistd.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <arpa/inet.h>
       #include <netdb.h>
       #include <sys/shm.h>

       #define BUF_SIZE 500

       typedef struct{
        int quit;
       }mex;

       int tryconnect(int *sockfd,const char* port,const char* address){
        struct addrinfo hints;
           struct addrinfo *result, *rp;
           int  s;
           size_t len;

           /* Obtain address(es) matching host/port */

           memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_STREAM; /* stream socket */
           hints.ai_flags = 0;
           hints.ai_protocol = 0;          /* Any protocol */

           s = getaddrinfo(address, port, &hints, &result);
           if (s != 0) {
               fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }

           /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully connect(2).
              If socket(2) (or connect(2)) fails, we (close the socket
              and) try the next address. */

           for (rp = result; rp != NULL; rp = rp->ai_next) {
               *sockfd = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (*sockfd == -1)
                   continue;

               if (connect(*sockfd, rp->ai_addr, rp->ai_addrlen) != -1){
                /* Success */
                freeaddrinfo(result);
                return 1;

               }
               close(*sockfd);
           }

           /* No address succeeded */
               fprintf(stderr, "Could not connect\n");
               freeaddrinfo(result);
               return -1;

       }

       void doBind(int * sockfd,const char* port){

           struct addrinfo hints;
           struct addrinfo *result, *rp;
           int s;
           memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_STREAM; /* stream socket */
           hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
           hints.ai_protocol = 0;          /* Any protocol */
           hints.ai_canonname = NULL;
           hints.ai_addr = NULL;
           hints.ai_next = NULL;

           s = getaddrinfo(NULL, port, &hints, &result);
           if (s != 0) {
               fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }

           /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully bind(2).
              If socket(2) (or bind(2)) fails, we (close the socket
              and) try the next address. */

           for (rp = result; rp != NULL; rp = rp->ai_next) {
               *sockfd = socket(rp->ai_family, rp->ai_socktype,
                       rp->ai_protocol);
               if (*sockfd == -1)
                   continue;

               if (bind(*sockfd, rp->ai_addr, rp->ai_addrlen) == 0){
                   break;                  /* Success */
               }

               close(*sockfd);
           }

           if (rp == NULL) {               /* No address succeeded */
               fprintf(stderr, "Could not bind\n");
               exit(EXIT_FAILURE);
           }

           freeaddrinfo(result);
       }

       int main(int argc, char *argv[]){
           int sfd, s,finalsock;
           struct sockaddr_in remote;
           char buf[BUF_SIZE];
           socklen_t remote_len;
           ssize_t nread;

           if (argc <3) {
               fprintf(stderr, "Usage: %s address port\n", argv[0]);
               exit(EXIT_FAILURE);
           }
            if(tryconnect(&sfd,argv[2],argv[1])<0){
                doBind(&sfd,argv[2]);
                if(listen(sfd,1)<0){perror("listen");exit(1);}
                printf("listening for connection\n");
                if((finalsock=accept(sfd,(struct sockaddr*)&remote,&remote_len))<0){perror("accept");exit(1);}
                printf("connected to %s : %i \n",inet_ntoa(remote.sin_addr),ntohs(remote.sin_port));
            }
            else{
                finalsock=sfd;
                remote.sin_addr.s_addr=inet_addr(argv[1]);
                remote.sin_port=htons(atoi(argv[2]));
                printf("connected to %s : %s \n",argv[1],argv[2]);
            }
            int shmid=shmget(2341,sizeof(mex),0666|IPC_CREAT);
            if(shmid<0){
                perror("shmid");
                exit(1);
               }

            mex* messa=(mex*)shmat(shmid,NULL,0666|IPC_CREAT);
            messa->quit=0;
                     /* No longer needed */

           /* Read messaggi */
           if(!fork()){
                nread = recv(finalsock,buf,BUF_SIZE,0);
                while(strncmp(buf,"quit",2)!=0){
                    if (nread == -1) continue;
                    if(nread == 0 || nread==1)break;
                    if(messa->quit==1)break;
                    buf[nread-1]=0;
                    printf("\nPid=%d: received from %s:%d \n the message: %s\n",getpid(),inet_ntoa(remote.sin_addr),ntohs(remote.sin_port), buf );
                    nread = recv(finalsock,buf,BUF_SIZE,0);
                }
                messa->quit=1;
                exit(0);
           }
           /* processo padre manda messaggi da tastiera   */
           while(fgets(buf,BUF_SIZE,stdin)!=NULL && (messa->quit!=1)){
                buf[strlen(buf)]=0;
                if (send(finalsock,buf,strlen(buf),0)<0)fprintf(stderr, "Error sending response\n");
                printf("\nPid=%d: sending to %s:%d \n the message: %s\n",getpid(),inet_ntoa(remote.sin_addr),ntohs(remote.sin_port), buf );
                if(strncmp(buf,"quit",2)==0)break;
           }
           messa->quit=1;
           exit(0);

       }

