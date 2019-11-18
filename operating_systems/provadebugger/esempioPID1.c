#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>    //per le varie cose di fork


int main(){
    pid_t pidFiglio=fork();
    if(pidFiglio==0){
        sleep(1);      //il padre diventa init (PID == 1)
        printf(" valore pid figlio: %i  e padre %i \n",getpid(),getppid());
        return 0;
    }
    else{
        printf(" valore pid padre: %i  e nonno %i",getpid(),getppid());
        //sleep(1);
        return 0;
    }

}
