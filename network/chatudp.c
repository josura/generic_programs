#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

void errore(int val,const char* strin){
    if(val<0){
        perror(strin);
        exit(1);

    }
}

int main(int argc, char**argv)
{
  int sockfd, n;
  struct sockaddr_in remote_addr;
  char sendline[1000];
  char recvline[1000];
  socklen_t len = sizeof(remote_addr);

  if (argc != 3)
  { printf("usage:  UDPchatsemplice <remote_IP remote_port>\n");
    return 1;
  }

  errore((sockfd=socket(AF_INET,SOCK_DGRAM,0)),"socket ");
  memset(&remote_addr,0,sizeof(remote_addr));
  remote_addr.sin_family = AF_INET;
  remote_addr.sin_addr.s_addr=inet_addr(argv[1]);
  remote_addr.sin_port=htons(atoi(argv[2]));
  if(!fork()){
    printf("aspetto messaggi da %s...\n",argv[1]);
    errore(n=recvfrom(sockfd,recvline,1000,0,(struct sockaddr *) &remote_addr, &len),"rcvfrom");
    recvline[n]=0;
    while(strncmp(recvline,"quit",2)!=0){
        printf("From IP:%s Port:%d msg:%s \n", inet_ntoa(remote_addr.sin_addr),  ntohs(remote_addr.sin_port), recvline);
        errore(n=recvfrom(sockfd,recvline,1000,0,(struct sockaddr *) &remote_addr, &len),"rcvfrom");
        recvline[n]=0;
	}
	exit(0);
  }
  while (fgets(sendline, 1000,stdin) != NULL){
        sendto(sockfd,sendline,strlen(sendline),0,
        (struct sockaddr *)&remote_addr, sizeof(remote_addr));
        if(strncmp(sendline,"quit",2)!=0)exit(0);

  }
  exit(0);
}
