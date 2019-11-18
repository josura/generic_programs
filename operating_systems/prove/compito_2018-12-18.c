#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>
#include <ctype.h>

#define SIZE 1024

typedef struct{
    long mtype;
    char mesg[SIZE];
    short eof;
}messaggio;

void errore(int val,const char* text){
    if(val<0){
        perror(text);
        exit(1);
    }
}

void Reader(int * pipefd,const char* file){
    close(pipefd[0]);
    FILE* fil;
    char buffer[SIZE];
    if((fil=fopen(file,"r"))==NULL){
        perror("fopen");
        exit(1);
    }
    while(fgets(buffer,SIZE,fil)!=NULL){
        write(pipefd[1],buffer,strlen(buffer));
    }
    exit(0);
}

void Writer(int msqid){
    messaggio mex;
    while(1){
            errore(msgrcv(msqid,&mex,sizeof(mex)-sizeof(long),0,0),"msgget");
            if(mex.eof!=1) write(1,mex.mesg,strlen(mex.mesg));
            else {exit(0);
        }
    }

}


int main(int argc,char* argv[]){
    if(argc<3){
        printf("usage: grep-strano [parola] [file]");
        exit(1);
    }
    int pipefd[2];
    int msqid;
    errore((msqid=msgget(7777,0666|IPC_CREAT)),"msgget");
    errore(pipe(pipefd),"pipe");
    char buffer[SIZE];
    if(!fork()){
        Reader(pipefd,argv[2]);
    }
    if(!fork()){
       close(pipefd[0]);
       close(pipefd[1]);
        Writer(msqid);
    }
    close(pipefd[1]);
    int len;
    while(1){
            len=read(pipefd[0],buffer,SIZE);
            if(len<=2)break;
            if(strstr(buffer,argv[1])!=NULL){
                messaggio messag;
                strcpy(messag.mesg,buffer);
                errore(msgsnd(msqid,&messag,sizeof(messag)-sizeof(long),0),"msgget");
            }
    }
    messaggio messag;
    messag.eof=1;
    errore(msgsnd(msqid,&messag,sizeof(messag)-sizeof(long),0),"msgget");
    wait(NULL);
    wait(NULL);
    msgctl(msqid,IPC_RMID,0);


}
