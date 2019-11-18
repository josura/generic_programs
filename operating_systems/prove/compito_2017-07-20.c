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

#define SIZE 512

enum semtype{EMPTY=0,SCAN,STAT};

typedef struct{
    char pathname[SIZE];
    int num_blocks;
}messaggio;

void errore(int val,const char* str){
    if(val<0){
        perror(str);
        exit(1);
    }
}

void initializeSem(int semid){
    errore(semctl(semid,EMPTY,SETVAL,1),"semctrl");
    errore(semctl(semid,SCAN,SETVAL,0),"semctrl");
    errore(semctl(semid,STAT,SETVAL,0),"semctrl");

}

int UP(int semid,int semnum){
    struct sembuf ops[]={{semnum,+1,0}};
    return semop(semid,ops,1);
}

int DOWN(int semid,int semnum){
    struct sembuf ops[]={{semnum,-1,0}};
    return semop(semid,ops,1);
}


void Stater(messaggio* condiviso,int semid){
    exit(0);
}

void Scanner(messaggio* condiviso,int semid,const char* pathname){
    exit(0);
}

int main(int argc,char** argv){
    if(argc<2){
        printf("usage : du-- [directyr]* ");
        exit(1);
    }
    int shmid,semid;
    errore((shmid=shmget(2312,sizeof(messaggio),0666|IPC_CREAT)),"shmget");
    errore((semid=semget(5341,3,0666|IPC_CREAT)),"semget");
    messaggio* condiviso;
    if((condiviso=(messaggio*)shmat(shmid,NULL,0))==(messaggio*)-1){
        perror("shmat");
        exit(1);
    }
    initializeSem(semid);

    if(!fork()){
        Stater(condiviso,semid);
    }
    int i;
    for(i=0;i<argc-1;i++){
        Scanner(condiviso,semid,argv[i+1]);
    }

    for(i=0;i<argc-1;i++) wait(NULL);
    wait(NULL);
    shmctl(shmid,IPC_RMID,0);
    semctl(semid,0,IPC_RMID,0);
}

