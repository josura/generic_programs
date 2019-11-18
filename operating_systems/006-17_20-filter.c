#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LEN 1024
#define FINAL 0
#define EMPTY 1

void errore(int val,const char* str){
    if(val<0){
        perror(str);
        exit(1);
    }
}

typedef struct{
    char riga[MAX_LEN];
    int eof;
}messaggio;

int UP(int semid,int semnum){
	struct sembuf ops[1] = {{semnum,+1,0}};
	return semop(semid, ops, 1);
}

int DOWN(int semid,int semnum){
	struct sembuf ops[1] = {{semnum,-1,0}};
	return semop(semid, ops, 1);
}

int primaoccorrenza(char * stringa,const char* occ){
    int i,j=0;
    for(i=0;i<strlen(stringa);i++){
        if(stringa[i]==occ[j]){
            for(j=1;j<strlen(occ) && stringa[i+j]==occ[j];j++){
            }
            if(j>=strlen(occ))return i;
            j=0;
        }
    }
    return -1;
}

void Filter(messaggio* cond,int semid,const char* filtro, int numfil,int totfil){
    char truefilter[MAX_LEN];
    strcpy(truefilter,filtro+1);
    while(1){
        DOWN(semid,numfil);
        if(cond->eof<0){

            if(numfil>=totfil-1){
                UP(semid,FINAL);
            } else
            UP(semid,numfil+1);
            exit(0);
        }
         int i;
        char buffer[MAX_LEN];
        strcpy(buffer,cond->riga);
        if(filtro[0]=='^'){
            char* occ;
            while((occ=strstr(buffer,truefilter))!=NULL){
                for(i=0;i<strlen(truefilter);i++){
                    occ[i]=toupper(occ[i]);
                }
            }
        }
        else if(filtro[0]=='_'){
            strcpy(buffer,cond->riga);
            char* occ;
            while((occ=strstr(buffer,truefilter))!=NULL){
                for(i=0;i<strlen(truefilter);i++){
                    occ[i]=tolower(occ[i]);
                }
            }
        } else{
            char sostit[MAX_LEN],filtrovero[MAX_LEN];
            char * car=truefilter;
            i=0;
            while(car[i]!='|'){
                i++;
            }
            car=truefilter+i+1;
            strcpy(sostit,car);
            strncpy(filtrovero,truefilter,i);
            char* occ;
            while((occ=strstr(buffer,filtrovero))!=NULL){
                char bufsin[MAX_LEN],bufdes[MAX_LEN];
                int numcardes=primaoccorrenza(buffer,filtrovero);
                strncpy(bufsin,buffer,numcardes);
                occ=occ+strlen(filtrovero);
                strcpy(bufdes,occ);
                strcat(bufsin,strcat(sostit,bufdes));
                strcpy(buffer,bufsin);
            }
        }
        strcpy(cond->riga,buffer);
        if(numfil>=totfil-1){
            UP(semid,FINAL);
        } else
        UP(semid,numfil+1);
    }
}

int main(int argc,const char** argv){
    if(argc<3){
        printf("usage : filter file.txt filter1 filter2");
        exit(1);
    }
    int shmid,semid,i;
    messaggio* condiviso;
    errore((shmid=shmget(IPC_PRIVATE,sizeof(messaggio),0666|IPC_CREAT)),"shmget");
    errore((semid=semget(IPC_PRIVATE,argc-1,0666|IPC_CREAT)),"semget");
     errore(semctl(semid,EMPTY,SETVAL,1),"semctl");
    for(i=2;i<argc-1;i++){
    		errore(semctl(semid,i,SETVAL,0),"semctl");
    }
    errore(semctl(semid,FINAL,SETVAL,0),"semctl");
    condiviso=(messaggio*)shmat(shmid,NULL,0);
    if(condiviso==(messaggio*)-1){
        perror("shmat");
        exit(1);
    }
    for(i=0;i<argc-2;i++){
    	if(!fork()){
    		Filter(condiviso,semid,argv[i+2],i+2,argc);
    	}
    }
    char buffer[MAX_LEN];
    FILE* fil=fopen(argv[1],"r");
    if(fil==NULL){
        perror("fopen");
        exit(1);
    }
    condiviso->eof=1;
    errore(semctl(semid,EMPTY,SETVAL,1),"semctl");
    errore(semctl(semid,FINAL,SETVAL,0),"semctl");
    if(fgets(buffer,MAX_LEN,fil)==NULL){
                condiviso->eof=-1;
                UP(semid,2);

        }
    while(1){
        strcpy(condiviso->riga,buffer);
        UP(semid,2);
        DOWN(semid,FINAL);
        puts(condiviso->riga);
        if(fgets(buffer,MAX_LEN,fil)==NULL){
                condiviso->eof=-1;
                UP(semid,2);
                break;

        }
    }
    for(i=0;i<argc-2;i++)wait(NULL);
    shmctl(shmid,IPC_RMID,0);
    semctl(semid,0,IPC_RMID,0);

}
