/*
    Homework n.2

    Estendere l'esempio 'move.c' visto a lezione per supportare i 2 casi speciali:
    - spostamento cross-filesystem: individuato tale caso, il file deve essere
      spostato utilizzando la strategia "copia & cancella";
    - spostamento di un link simbolico: individuato tale caso, il link simbolico
      deve essere ricreato a destinazione con lo stesso contenuto (ovvero il percorso
      che denota l'oggetto referenziato); notate come tale spostamento potrebbe
      rendere il nuovo link simbolico non effettivamente valido.

    La sintassi da supportare e' la seguente:
     $ homework-2 <pathname sorgente> <pathname destinazione>
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>

#define BUFSIZE 2048

int main(int argc, char *argv[]) {
    struct stat src_statbuf, dst_statbuf;
    int src_d, dst_d, size;
    char buffer[BUFSIZE];
    char *dst_dir;

    if (argc != 3) {
        fprintf(stderr, "utilizzo: %s <file-esistente> <nuovo-nome-e-o-posizione>\n", argv[0]);
        exit(1);
    }

    if (lstat(argv[1], &src_statbuf) == -1) {
        perror(argv[1]);
        exit(1);
    }

    /* determina il tipo di oggetto da spostare */
    switch (src_statbuf.st_mode & S_IFMT) {
    case S_IFLNK:
        /* legge il pathname del link simbolico */
        if ((size = readlink(argv[1], buffer, BUFSIZE)) == -1) {
            perror(argv[1]);
            exit(1);
        }
        buffer[size] = '\0';

        /* crea un nuovo link simbolico con lo stesso pathname
           quest'ultimo potrebbe non essere piu' corretto...   */
        if (symlink(buffer, argv[2]) == -1) {
            perror(argv[2]);
            exit(1);
        }
        break;
    case S_IFREG:
        /* estrae dalla destinazione la directory padre: ne crea
           una copia perche' dirname potrebbe modificare la stringa */
        strncpy(buffer, argv[2], BUFSIZE);
        dst_dir = dirname(buffer);
        if (stat(dst_dir, &dst_statbuf) == -1) {
            perror(dst_dir);
            exit(1);
        }

        /* controlla che si tratti effettivamente di una directory */
        if (!S_ISDIR(dst_statbuf.st_mode)) {
            fprintf(stderr, "il percorso '%s' non sembra essere una directory!\n", dst_dir);
            exit(1);
        }

        /* cerca di capire se la sorgente e la directory di destinazione risiedono sullo stesso file-system;
           in alternativa si poteva tentare la creazione dell'hard-link e verificare la condizione
           (errno==EXDEV) in caso di errore                                                         */
        if (src_statbuf.st_dev == dst_statbuf.st_dev) {     // si trovano sullo stesso file-system
            printf("stesso fs\n");
            /* crea un hard-link a partire dal file esistente */
            if (link(argv[1], argv[2]) == -1) {
                perror(argv[2]);
                exit(1);
            }
        } else {    // si trovano su due file-system diversi: non posso usare gli hard-link
            printf("diverso fs\n");
            /* effettua una copia standard del file sorgente sulla destinazione */
            if ((src_d = open(argv[1], O_RDONLY)) == -1) {
                perror(argv[1]);
                exit(1);
            }
            if ((dst_d = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, (src_statbuf.st_mode & 0777))) == -1) {
                perror(argv[2]);
                exit(1);
            }
            do {
                if ((size = read(src_d, buffer, BUFSIZE)) == -1) {
                    perror(argv[1]);
                    exit(1);
                }
                if (write(dst_d, buffer, size) == -1) {
                    perror(argv[2]);
                    exit(1);
                }
            } while (size == BUFSIZE);
            close(src_d);
            close(dst_d);
        }
        break;
    default:
        fprintf(stderr, "tipo di oggetto non supportato!\n");
        exit(1);
    }
    /* rimuove l'oggetto sorgente */
    if (unlink(argv[1]) == -1) {
        perror(argv[1]);
        exit(1);
    }
}


