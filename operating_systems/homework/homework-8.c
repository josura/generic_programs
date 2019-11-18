/*
    Homework n.8

    Modificare l'homework precedente (n.7) sostituendo il canale di comuniciazione
    offerto dalla coda di messaggi tra padre e figlio con un segmento di memoria
    condiviso e una coppia di semafori (esattamente due) opportunamente utilizzati
    per il coordinamento.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define DIM_MSG 4096
#define S_COMMAND 0
#define S_OUTPUT  1
#define STD_IN  0
#define STD_OUT 1
#define STD_ERR 2

int WAIT(int sem_des, int num_semaforo) {
    struct sembuf operazioni[1] = {{num_semaforo, -1, 0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo) {
    struct sembuf operazioni[1] = {{num_semaforo, +1, 0}};
    return semop(sem_des, operazioni, 1);
}

void errore(int val,const char * err){
    if(val<0){
        perror(err);
        exit(1);
    }
}

void controllaAccapo(char* stringa){
    if ( stringa[strlen(stringa)-1]== '\n' )
            stringa[strlen(stringa)-1] = '\0';
}

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

/* si occupa di leggere i comandi dal prompt, di inviarli sul buffer condiviso
   e di riceverne l'output sullo stesso                                          */
void gestore_terminale(int id_shm, int id_sems) {
    int len;
    char *messaggio;

    if ((messaggio = (char *) shmat(id_shm, NULL, 0))== (char *)-1){
        perror("shmat");
        exit(1);
    }
    while (1) {
        /* legge il comando da tastiera e lo inserisce direttamente nel buffer condiviso */
        printf("> ");
        fgets(messaggio, DIM_MSG, stdin);
        len = strlen(messaggio);
        controllaAccapo(messaggio);

        /* segnala la disponibilita' del comando sul buffer, controllando anche se e' il comando di uscita */
        if ( strcmp(messaggio, "exit") != 0 ) {
            SIGNAL(id_sems, S_COMMAND);
        } else {
            SIGNAL(id_sems, S_COMMAND);
            break;
        }
        /* NB: non posso fare il SIGNAL prima del confronto: rischierei che il comando sia sovrascritto dall'output */

        /* aspetta che sia disponibile l'output sul buffer */
        WAIT(id_sems, S_OUTPUT);
        printf("%s", messaggio);
    }

    exit(0);
}

void forkExec(char* comando,int pipefd[2]){
            /* redireziona lo standard output sulla pipe */
            close(STD_OUT);
            dup(pipefd[1]);
            /* redireziona lo standard error sulla pipe */
            close(STD_ERR);
            dup(pipefd[1]);
            /* chiude il canale di lettura sulla pipe */
            close(pipefd[0]);
            int argomenti=trovaParole(comando);
            char*  argc[argomenti+1];
            argc[0]=strtok(comando," ");
            int i=1;
            while((argc[i]=strtok(NULL," "))!=NULL){
                i++;
            }
            execvp(argc[0], argc);
            fprintf(stderr, "Errore nell'esecuzione di '%s'\n", comando);
            exit(2);
}


void forkPassaggioPipe(int id_sems,char* messaggio,int pipefd[2]){
            /* chiude il canale di scrittura sulla pipe */
            close(pipefd[1]);

            /* legge l'output del comando dalla pipe e lo scrive direttamente sul buffer */
            int len = read(pipefd[0], messaggio, DIM_MSG-1);
            messaggio[len] = '\0';

            /* segnala la disponibilita' dell'output sul buffer condiviso */
            SIGNAL(id_sems, S_OUTPUT);

            /* chiude il restante canale sulla pipe */
            close(pipefd[0]);
}

/* si occupa di ricevere i comandi dalla coda, di eseguirli tramite dei processi figli,
   di catturarne l'output/error tramite redirezione su pipe e inviarne il risultato
   indietro con un messaggio                                                            */
void esecutore(int id_shm, int id_sems) {
    char *messaggio;
    int pipefd[2];

    if((messaggio = (char *) shmat(id_shm, NULL, 0))== (char *)-1){
        perror("shmat");
        exit(1);
    }
    while (1) {
        /* aspetta che il comando dia disponibile sul buffer condiviso */
        WAIT(id_sems, S_COMMAND);

        if ( strcmp(messaggio, "exit") == 0 )
            break;

        /* crea una nuova pipe per il nuovo figlio */
        if (pipe(pipefd) == -1 ) {
            perror("pipe");
            exit(1);
        }

        if ( fork() == 0 ) {
            forkExec(messaggio,pipefd);
        } else {
            forkPassaggioPipe(id_sems,messaggio,pipefd);
        }
    }

    shmctl(id_shm, IPC_RMID, NULL);
    semctl(id_sems, 0, IPC_RMID, 0);

    exit(0);
}

int main() {
    int id_shm, id_sems;
    key_t chiave = IPC_PRIVATE;

    /* crea un segmento di memoria condiviso per scambiarsi messaggi */
    errore((id_shm = shmget(chiave, DIM_MSG, IPC_CREAT|IPC_EXCL|0600)),"shmget");
    fprintf(stdout,"id memoria condivisa %i \n",id_shm);

    /* crea 2 semafori (S_COMMAND, S_OUTPUT) */
    errore ((id_sems = semget(chiave, 2, IPC_CREAT|IPC_EXCL|0600)),"semget");
    fprintf(stdout,"id semaforo %i \n",id_sems);

    // imposta i valori iniziali dei semafori
    semctl(id_sems, S_COMMAND, SETVAL, 0);
    semctl(id_sems, S_OUTPUT, SETVAL, 0);
//    int values[]={0,0};
//    semctl(id_sems,0,SETALL,values);

    if ( fork() != 0 )
        gestore_terminale(id_shm, id_sems);
    else
        esecutore(id_shm, id_sems);
    shmctl(id_shm,IPC_RMID,0);
    semctl(id_sems,0,IPC_RMID);

}



