#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>    //per le varie cose di fork


int main(){
    pid_t pidFiglio=fork();
    while(fork()>=0){
            sleep(1);
        printf("sono il processo %i \n",getpid());
    }
}

