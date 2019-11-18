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
    int openfd=open("falzo.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(openfd<0){
        perror("falzo.txt");
        exit(1);
    }
    char comando[10];
    unsigned i=0;
    while(strcmp(comando,"ciao")!=0){
        const char* stringa="ciao\n";
        write(openfd,stringa,strlen(stringa));
        sleep(1);
    }
}
