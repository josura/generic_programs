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
#define COMPA 1
#define RESU 2

void swapStringchar(char *string1,char *string2){
    char temp[SIZE];
    strcpy(temp,string1);
    strcpy(string1,string2);
    strcpy(string2,temp);
}

typedef struct{
    long mtype;
    char stringa1[SIZE];
    char stringa2[SIZE];
    int value;
    int eof;
}comparare;

void errore(int val,const char* str){
    if(val<0){
        perror(str);
        exit(1);
    }
}

int partition (char arr[][SIZE], int low, int high,int msqid){
    char* pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++){
        comparare com;
        strcpy(com.stringa1,arr[j]);
        strcpy(com.stringa2,pivot);
        com.mtype=COMPA;
        errore(msgsnd(msqid,&com,sizeof(com)-sizeof(long),0),"msgsnd");
        errore(msgrcv(msqid,&com,sizeof(com)-sizeof(long),RESU,0),"msgrcv");
        if (com.value<=0){
            i++;
            swapStringchar(arr[i], arr[j]);
        }
    }
    swapStringchar(arr[i + 1],arr[high]);
    return (i + 1);
}

void quickSort(char arr[][SIZE], int low, int high,int msqid){
    if (low < high){
        int pi = partition(arr, low, high,msqid);
        quickSort(arr, low, pi - 1,msqid);
        quickSort(arr, pi + 1, high,msqid);
    }
}

int countWords(char* filptr,int size){
   int count = 0;
   int i;
   for(i=0;i<size;i++){
       if (filptr[i] == '\n' || filptr[i]==' ')
           count++;
   }
   return count-1;
}

void Sorter(int msqid,int pipefd[2],const char* pathname){
    struct stat sb;
    char* filptr;
    int fd=open(pathname,O_RDONLY);
    errore(fd,"open");
    errore(lstat(pathname,&sb),"lstat");
    if((filptr=(char*)mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0))==MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    int numwords=countWords(filptr,sb.st_size);
    if( numwords==0)exit(0);
    char stringona[1000];
    bzero(stringona,1000);
    strncpy(stringona,filptr,sb.st_size);
    char * tmp=strtok(stringona,"\n");
    char words[numwords][SIZE];
    strcpy(words[0],tmp);
    int i;
    while((tmp = strtok(NULL,"\n"))!=NULL){
        strcpy(words[i],tmp);
        i++;
    }
    quickSort(words,0,numwords-1,msqid);
    for(i=0;i<numwords;i++){
        write(pipefd[1],words[i],strlen(words[i]));
    }
    comparare com;
    com.eof=1;
    com.mtype=COMPA;
    errore(msgsnd(msqid,&com,sizeof(com)-sizeof(long),0),"msgsnd");
    exit(0);


}

void Comparer(int msqid){
    comparare com;
    errore(msgrcv(msqid,&com,sizeof(com)-sizeof(long),COMPA,0),"msgrcv cmp");
    while(com.eof!=1){
        if(strcasecmp(com.stringa1,com.stringa2)>0 && strlen(com.stringa1)<=strlen(com.stringa2)){
            com.value=1;
        }
        else if(strcasecmp(com.stringa1,com.stringa2)==0) com.value=0;
        else com.value=-1;

        com.mtype=RESU;
        errore(msgsnd(msqid,&com,sizeof(com)-sizeof(long),0),"msgsnd cmp");
        errore(msgrcv(msqid,&com,sizeof(com)-sizeof(long),COMPA,0),"msgrcv cmp");
    }
    exit(0);
}

int main(int argc,char* argv[]){
    if(argc<2){
        printf("usage : sort-list [file]");
        exit(1);
    }
    int msqid,pipefd[2];
    errore(pipe(pipefd),"pipe");
    errore((msqid=msgget(2314,0666|IPC_CREAT)),"msgget");


    if(!fork()){
        close(pipefd[0]);
        Sorter(msqid,pipefd,argv[1]);
    }
    if(!fork()){
        close(pipefd[0]);
        close(pipefd[1]);
        Comparer(msqid);
    }
    close(pipefd[1]);
    char buffer[SIZE];
    while(read(pipefd[0],buffer,SIZE)>0){
        puts(buffer);
    }
    wait(NULL);
    wait(NULL);
    msgctl(msqid,IPC_RMID,0);
}
