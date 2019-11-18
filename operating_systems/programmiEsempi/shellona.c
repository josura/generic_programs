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

#define BUFSIZE 2048
#define BUFCOMANDO 200

void staccaTutto(int * input,int numValues){
    int i=0;
    while(i<numValues){
        close(input[i]);
        i++;
    }
}

void readWriteMappata(const char* input,const char* output ){
    int inputfd, outputfd;
    char *src, *dst;
    struct stat sb;

    if ((inputfd = open(input, O_RDONLY)) == -1) {
        perror(input);
        exit(1);
    }

    /* recupera le informazioni sul file sorgente */
    if (fstat(inputfd, &sb) < 0) {
        perror(input);
        exit(1);
    }

    /* apre il file destinazione troncandolo o creandolo */
    if ((outputfd = open(output, O_RDWR | O_CREAT | O_TRUNC,
                      (sb.st_mode & 0777))) == -1) {
        perror(output);
        exit(1);
    }

    /* controlla se il file sorgente è vuoto: creerebbe problemi sia con lseek
     * che con mmap */
    if (sb.st_size == 0)
        exit(0);

    /* espande il file destinazione alla dimensione voluta prima di mapparlo:
     * utilizza 'ftruncate' */
    if (ftruncate(outputfd, sb.st_size) == -1) {
        perror("ftruncate su destinazione");
        exit(1);
    }
    /* si poteva usare anche un 'lseek' (alla posizione 'sb.st_size -1') e un
     * 'write' per un solo byte */

    /* mappa il file sorgente */
    if ((src = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, inputfd, 0)) == MAP_FAILED) {
        perror("mmap su sorgente");
        exit(1);
    }

    /* mmap il file destinazione */
    if ((dst = (char *)mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, outputfd, 0)) == MAP_FAILED) {
        perror("mmap su destinazione");
        exit(1);
    }

    /* copia il contenuto della sorgente sulla destinazione: usa 'memcpy' per
     * maggiore efficienza */
    memcpy(dst, src, sb.st_size);

    /* operazioni di chiusura non indispensabili... */
    munmap(src, sb.st_size);
    munmap(dst, sb.st_size);
    close(inputfd);
    close(outputfd);
}

void catta(const char* input[],int numValues,const char* output){
    int openfd[numValues],targetfd,readn,writen;
    int i=0;
    while(i<numValues){
        openfd[i]=open(input[i],O_RDONLY);
        if(openfd<0){
            printf("%s : ",input[i]);
            perror("openfd ");
            staccaTutto(openfd,i);
            return;
        }
        i++;
    }
    char buffer[BUFSIZE];
    if(strncmp(output,"stdout",4)!=0){
        targetfd=open(output,O_RDWR|O_CREAT|O_TRUNC,0666);
        if(targetfd<0){
            printf("%s : ",output);
            perror("targetfd ");
            staccaTutto(openfd,numValues);
            return;
        }
        i=0;
        while(i<numValues){
            while ((readn=read(openfd[i],buffer, BUFSIZE)) > 0)
                write(targetfd, buffer,readn);
            close(targetfd);
            i++;
        }
    }
    else {
        i=0;
        while(i<numValues){
            while ((readn=read(openfd[i],buffer, BUFSIZE)) > 0)
                write(1, buffer,readn);
            i++;
        }
    }
    staccaTutto(openfd,numValues);

}

void printaiuto(const char* funz){
        printf("Lista comandi disponibili: \n\t concat: sintassi {cat input1 [input2,input3, ...] [ > output.txt] }\n");
        return;
}

const char* substring(const char* string, int inizio,int fine){
    if(fine==0 || strlen(string)<fine)fine=strlen(string);
    if(inizio>fine)return "";
    char *out=malloc(fine-inizio+1);
    int i=0;
    while(i<fine-inizio){
        out[i]=string[inizio+i];
        i++;
    }
    out[i]=0;
    return out;
}

int trovaMaggiore(const char* parola){
    int i;
    for(i=0;i<strlen(parola);i++){
        if(parola[i]=='>')return i;
    }
    return -1;
}

int trovaPrimaLetteraAfter(const char* parola,int inizio){
    int i;
    for(i=inizio; i<strlen(parola); i++){
        if(parola[i]=='>')return -2;
        if(!isspace(parola[i]))return i;
    }
    return -1;
}

int trovaPrimaSpazioAfter(const char* parola,int inizio){
    int i;
    for(i=inizio; i<strlen(parola); i++){
        if(isspace(parola[i]))return i;
    }
    return -1;
}

int trovaParole(const char * funz){
    int cont=0,primoSpace=0,primaLett;
    while((primaLett=trovaPrimaLetteraAfter(funz,primoSpace))>=0){
            if(primaLett<0 )return cont;
                cont++;
            primoSpace=trovaPrimaSpazioAfter(funz,primaLett);
            if(primoSpace<0 )return cont;
        }
        return cont;
}

void scegliComando(const char* funz){
    if(strncmp(funz,"cat",3)==0){
        int i=0;
        const char* sorgenti=substring(funz,4,0);
        int red=trovaMaggiore(sorgenti), primaLett,primoSpace=0,numeroValori=trovaParole(sorgenti);
        const char* input[numeroValori];
        while((primaLett=trovaPrimaLetteraAfter(sorgenti,primoSpace))>=0){
            primoSpace=trovaPrimaSpazioAfter(sorgenti,primaLett);
            if(primoSpace<0 )primoSpace=strlen(sorgenti);
            if(primaLett<0 )return;
            input[i]=substring(sorgenti,primaLett,primoSpace);
            i++;
        }
        if(red<=0) catta(input,numeroValori,"stdout");
        else {
            primaLett=trovaPrimaLetteraAfter(sorgenti,red+1);
            primoSpace=trovaPrimaSpazioAfter(sorgenti,primaLett);
            const char* output=substring(sorgenti,primaLett,primoSpace);
            catta(input,numeroValori,output);
        }
    }

}

int main(int argc,char* argv[]){
    printf("////////////////////////////////////////////////////\n");
    printf("Benvenuti nella shell dentro la shell ricreata da me \n");
    printf("provare la maggior parte dei comandi disponibili \n");
    printf("scrivere help per vedere i comandi disponibili \n");
    printf("////////////////////////////////////////////////////\n\n");
//    sleep(2);
//    system("clear");
    if(argc>1 && argv[1][0]!='-'){
        printf("le possibili modalità di apertura sono le seguenti\n");
    }
    char comando[BUFCOMANDO]="";
    while(strcmp(comando,"quit")!=0){
        printf("<<<shellona>>> ");
//        fscanf(stdin,"%s", comando);
        fgets(comando,BUFCOMANDO, stdin);
        comando[strlen(comando)-1]=0;
        if(!strcmp(comando,"help")) printaiuto(comando);
        scegliComando(comando);
    }
    return 0;
}
