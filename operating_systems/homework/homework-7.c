/*
    Homework n.7

    Modificare l'homework precedente (n.6) facendo in modo che il figlio che
    riceve il comando da eseguire tramite la coda, catturi lo standard output
    e lo standard error del figlio nipote usando la redirezione su pipe tra
    processi. L'output catturato dovrà essere mandato indietro al padre
    tramite un messaggio (per semplicita', assumiamo sufficiente grande).
    Tale contenuto sara' poi visualizzato sul terminale dal padre.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define DIM_MSG 4096
#define STD_IN  0
#define STD_OUT 1
#define STD_ERR 2

typedef struct {
    long mtype;
    char mtext[DIM_MSG];
} msg;

int trovaPrimaLetteraAfter(const char* parola,int inizio){
    int i;
    for(i=inizio; i<strlen(parola); i++){
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


void controllaAccapo(char* stringa){
    if ( stringa[strlen(stringa)-1]== '\n' )
            stringa[strlen(stringa)-1] = '\0';
}

void errore(int ret,const char* str){
    if(ret<0){
        perror(str);
            exit(1);
    }
}
/* si occupa di leggere i comandi dal prompt, di inviarli sulla coda dei messaggi
   e di riceverne l'output con un messaggio di ritorno                            */
void gestore_terminale(int coda) {
    msg messaggio;
    int len;

    while (1) {
        printf("> ");
        fgets(messaggio.mtext, DIM_MSG, stdin);
        len = strlen(messaggio.mtext);
//        if ( messaggio.mtext[len-1] == '\n' )
//            messaggio.mtext[len-1] = '\0';
        controllaAccapo(messaggio.mtext);

        /* invia il messaggio con il comando da eseguire */
        messaggio.mtype = 1;
        errore( msgsnd(coda, &messaggio, strlen(messaggio.mtext)+1, 0),"msgsend");
        if ( strcmp(messaggio.mtext, "exit") == 0 )
            break;
        /* riceve il messaggio con l'output del comando eseguito */
        errore ( msgrcv(coda, &messaggio, DIM_MSG, 0, 0),"msgrcv");
        printf("%s", messaggio.mtext);
    }

    exit(0);
}

/* si occupa di ricevere i comandi dalla coda, di eseguirli tramite dei processi figli,
   di catturarne l'output/error tramite redirezione su pipe e inviarne il risultato
   indietro con un messaggio                                                            */
void esecutore(int coda) {
    msg messaggio;
    int pipefd[2];
    int len;

    while (1) {
        /* riceve il messaggio con il comando da eseguire */
        errore ( msgrcv(coda, &messaggio, DIM_MSG, 0, 0),"msgrcv");

        if ( strcmp(messaggio.mtext, "exit") == 0 )
            break;

        /* crea una nuova pipe per il nuovo figlio */
        errore(pipe(pipefd),"pipe");

        if ( fork() == 0 ) {
            /* redireziona lo standard output sulla pipe */
            close(STD_OUT);
            dup(pipefd[1]);
            /* redireziona lo standard error sulla pipe */
            close(STD_ERR);
            dup(pipefd[1]);
            /* chiude il canale di lettura sulla pipe */
            close(pipefd[0]);
            int argomenti=trovaParole(messaggio.mtext);
            char*  argc[argomenti+1];
            argc[0]=strtok(messaggio.mtext," ");
            int i=1;
            while((argc[i]=strtok(NULL," "))!=NULL){
                i++;
            }
            execvp(argc[0], argc);
            fprintf(stderr, "Errore nell'esecuzione di '%s'\n", messaggio.mtext);
            exit(2);
        } else {
            /* chiude il canale di scrittura sulla pipe */
            close(pipefd[1]);

            /* legge l'output del comando dalla pipe e lo invia indietro come messaggio */
            len = read(pipefd[0], messaggio.mtext, DIM_MSG-1);
            messaggio.mtext[len] = '\0';
            messaggio.mtype = 1;    // in realtà non stiamo sfruttando i differenti tipi di messaggi
            errore ( msgsnd(coda, &messaggio, strlen(messaggio.mtext)+1, 0),"msgsnd");
            /* chiude il restante canale sulla pipe */
            close(pipefd[0]);
        }
    }

    msgctl(coda, IPC_RMID, NULL);

    exit(0);
}

int main() {
    int ds_coda;
    key_t chiave = IPC_PRIVATE;

    errore ( (ds_coda = msgget(chiave, IPC_CREAT|IPC_EXCL|0600)),"msgget");

    if ( fork() != 0 )
        gestore_terminale(ds_coda);
    else
        esecutore(ds_coda);
}


