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
#include <unistd.h>
#include <wait.h>
#include <ctype.h>

#define ANAL 1
#define SCAN 2
#define MSGBUF 1024

typedef struct{
    long mtype;
    char pathname[MSGBUF];
    int file_dim;
    int tot_car;
    int eof;
}msgdir;


void errore(int val,const char* mesg){
    if(val<0){
        perror(mesg);
        exit(1);
    }
}

void scanning(int msqid,const char* pathname){
    DIR* direct;
    struct dirent* elem;
    struct stat sb;
    char copia[MSGBUF];
    if((direct=opendir(pathname))==NULL){
        perror("opendir");
        exit(1);
       }
    msgdir messaggio;
    while((elem=readdir(direct))!=NULL){
        if(!(strcmp(elem->d_name,".")) || !(strcmp(elem->d_name,"..")) )continue;
        strcpy(copia,pathname);
        strcpy(messaggio.pathname,strcat(strcat(copia,"/"),elem->d_name));
        errore(lstat(messaggio.pathname,&sb),strcat(elem->d_name," lstat"));
        switch(sb.st_mode & S_IFMT){
            case S_IFREG:
                fprintf(stdout,"Scanner : %s\n",messaggio.pathname);
                messaggio.file_dim=sb.st_size;
                messaggio.mtype=ANAL;
                messaggio.eof=0;
                errore(msgsnd(msqid,&messaggio,sizeof(messaggio)-sizeof(long),0),"msgsnd");
                break;
            case S_IFDIR:
                if(!(strcmp(elem->d_name,".")) || !(strcmp(elem->d_name,"..")) ) continue;
                scanning(msqid,elem->d_name);
                break;
            default: break;
        }
    }
    chdir("..");
    closedir(direct);
}

void Scanner(int msqid,const char* pathname){
    scanning(msqid,pathname);
    msgdir msgal;
    msgal.mtype=ANAL;
    msgal.eof=1;
    strcpy(msgal.pathname,pathname);
    errore(msgsnd(msqid,&msgal,sizeof(msgal)-sizeof(long),0),"msgsnd");
    exit(0);

}

void Analyzer(int msqid){
    msgdir messaggio;
    msgdir out;
    int fd;
    char* puntfile;
    errore(msgrcv(msqid,&messaggio,sizeof(messaggio)-sizeof(long),ANAL,0),"msgrcv");
    while(messaggio.eof==0){
        errore(fd=open(messaggio.pathname,O_RDONLY),"open");

        if((puntfile=(char*)(mmap(0,messaggio.file_dim,PROT_READ,MAP_PRIVATE,fd,0)))==MAP_FAILED){
            perror("mmap");
            exit(1);
        }
        int cont=0;
        for(int i=0;i<messaggio.file_dim;i++){
            if(isalpha(puntfile[i]))cont++;
        }
        fprintf(stdout,"Analyzer : %s %i\n",messaggio.pathname,cont);
        out.file_dim=messaggio.file_dim;
        out.mtype=SCAN;
        out.eof=0;
        strcpy(out.pathname,messaggio.pathname);
        out.tot_car=cont;
        errore( msgsnd(msqid,&out,sizeof(messaggio)-sizeof(long),0) ,"msgsnd");
        errore(munmap(puntfile,messaggio.file_dim),"munmap");
        close(fd);
        errore(msgrcv(msqid,&messaggio,sizeof(messaggio)-sizeof(long),ANAL,0),"msgrcv");
    }
    msgdir msgal;
    msgal.mtype=SCAN;
    msgal.eof=1;
    strcpy(msgal.pathname,messaggio.pathname);
    msgsnd(msqid,&msgal,sizeof(msgal)-sizeof(long),0);
    exit(0);
}

int main(int argc,char** argv){
    int msqid;
    if(argc<2){
        printf("usage: alpha-usage [directory]");
        exit(0);
    }
    errore((msqid=msgget(1234,0666|IPC_CREAT)),"msgget");
    int msgid;
    if(!fork()){
        Scanner(msqid,argv[1]);
    }
    if(!fork()){
        Analyzer(msqid);
    }
    int cont=0;
    msgdir messaggio;
    errore(msgrcv(msqid,&messaggio,sizeof(messaggio)-sizeof(long),SCAN,0),"msgrcv");
    while(messaggio.eof==0){
        cont+=messaggio.tot_car;
        errore(msgrcv(msqid,&messaggio,sizeof(messaggio)-sizeof(long),SCAN,0),"msgrcv");
    }

    wait(NULL);
    wait(NULL);
    printf("PADRE: totale di %i caratteri nel file %s\n",cont,argv[1]);
    msgctl(msqid,IPC_RMID,0);
}
