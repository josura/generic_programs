#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <math.h>

int main(){
    int openfd=open("falzo.txt",O_RDONLY);
    if(openfd<0){
        perror("falzo.txt");
        exit(1);
    }
    char comando[10];

    while(strcmp(comando,"ciao")!=0){
        char stringa[128];
        int numb=read(openfd,stringa,128);
        lseek(openfd,0,SEEK_SET);
        fprintf(stdout,stringa);
        scanf("%s",comando);
    }
}
