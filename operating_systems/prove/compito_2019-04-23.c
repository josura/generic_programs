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

#define KEYSHM 1234
#define KEYSEM 4321
#define SIZE 512


enum semtype{EMPTY=0,FILEGEN,DIREC};

typedef struct{
    char pathname[SIZE];
    int numbyte;
    int eof;
}record;

int UP(int semid,int semnum){
    struct sembuf ops[]={{semnum,+1,0}};
    return semop(semid,ops,1);
}

int DOWN(int semid,int semnum){
    struct sembuf ops[]={{semnum,-1,0}};
    return semop(semid,ops,1);
}



void errore(int val,const char* st){
    if(val<0){
        perror(st);
        exit(1);
    }
}

void initializeSem(int semid){
    errore(semctl(semid,EMPTY,SETVAL,1),"semctrl");
    errore(semctl(semid,FILEGEN,SETVAL,0),"semctrl");
    errore(semctl(semid,DIREC,SETVAL,0),"semctrl");

}

void Reader(record* condiviso, int semid,  char* pathname){
    DIR* direct;
    struct dirent* elem;
    struct stat sb;
    if((direct=opendir(pathname))==NULL){
        perror("opendir");
        exit(1);
    }
    while((elem=readdir(direct))!=NULL){
        if(!strcmp(elem->d_name,".") || !strcmp(elem->d_name,".."))continue;
        char copia[SIZE];
        strcpy(copia,pathname);
        strcpy(copia,strcat(strcat(copia,"/"),elem->d_name));
        errore(lstat(copia,&sb)," lstat");
        switch(sb.st_mode & S_IFMT){
            case S_IFREG:
                DOWN(semid,EMPTY);
                strcpy(condiviso->pathname,copia);
                condiviso->numbyte=sb.st_size;
                UP(semid,FILEGEN);
                break;
            case S_IFDIR:
                if(!(strcmp(elem->d_name,".")) || !(strcmp(elem->d_name,"..")) )continue;
                DOWN(semid,EMPTY);
                strcpy(condiviso->pathname,copia);
                condiviso->numbyte=sb.st_size;
                UP(semid,DIREC);
                break;
            default: break;
        }
    }
    DOWN(semid,EMPTY);
    condiviso->eof=1;
    UP(semid,FILEGEN);
    DOWN(semid,EMPTY);
    UP(semid,DIREC);
}

void Fileconsumer(record* condiviso,int semid){
    while(1){
        DOWN(semid,FILEGEN);
        if(condiviso->eof==1){
            UP(semid,EMPTY);
            exit(0);
        }
        printf("%s [ file di %i byte]\n",condiviso->pathname,condiviso->numbyte);
        UP(semid,EMPTY);
    }
}

void Dirconsumer(record* condiviso,int semid){
    while(1){
        DOWN(semid,DIREC);
        if(condiviso->eof==1){
            UP(semid,EMPTY);
            exit(0);
        }
        printf("%s [ directory di %i byte]\n",condiviso->pathname,condiviso->numbyte);
        UP(semid,EMPTY);
    }
}


int main(int argc,char** argv){
    int shmid,semid;
    errore((shmid=shmget(KEYSHM,sizeof(record),IPC_CREAT | 0666)),"shmget");
    errore((semid=semget(KEYSEM,3,IPC_CREAT | 0666)),"shmget");
    initializeSem(semid);
    record * condiviso;
    if((condiviso=(record*)shmat(shmid,NULL,0))==(record*)-1){
        perror("shmat");
        exit(1);
    }

    if(!fork()){
        Fileconsumer(condiviso,semid);
    }
    if(!fork()){
        Dirconsumer(condiviso,semid);
    }
    int i;
    for(i=0;i<argc-1;i++){
        if(!fork()){
            Reader(condiviso, semid , argv[i+1]);
        }
    }
    for(i=0;i<argc-1;i++){
        wait(NULL);
    }
    wait(NULL);
    wait(NULL);
    shmctl(shmid,IPC_RMID,0);
    semctl(semid,0,IPC_RMID,0);

}
