#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/mman.h>
#include <fcntl.h>

#define BUFSIZE 2048
#define ANALYZE 1
#define TOT 2
#define DEFAULT "."
#define END "finefinefine"

typedef struct{
	long mtype;
	char mtext[BUFSIZE];
	int dim_file;
	int tot_file;
	int num_file;
} msg;

void scanner(int ds_coda, char* path, int numfile){
	DIR * cartella;
	struct dirent *elem;
	struct stat statbuf;
	char file_path[BUFSIZE];
	msg messaggio;
	if((cartella=opendir(path))==NULL){
		perror("opendir");
		exit(1);
	}
	while((elem=readdir(cartella))!=NULL){
		if(lstat(elem->d_name, &statbuf)==-1){
			perror("lstat");
			exit(2);
		}
		if(S_ISREG(statbuf.st_mode)){
			numfile++;
			printf("File n. %d\n", numfile);
			strcpy(file_path, path);
			strcat(file_path, "/");
			strcat(file_path, elem->d_name);
			printf("Scanner: %s\n", file_path);
			messaggio.mtype=ANALYZE;
			messaggio.dim_file=statbuf.st_size;
			strcpy(messaggio.mtext, file_path);
			if(msgsnd(ds_coda, &messaggio, sizeof(messaggio)-sizeof(long), 0)==-1){
				perror("msgsnd scanner");
				exit(2);
			}
		} else if(S_ISDIR(statbuf.st_mode)){
			if (strcmp(elem->d_name, ".") == 0 || strcmp(elem->d_name, "..") == 0)
                continue;
			scanner(ds_coda, elem->d_name, numfile);
		}
	}
	chdir("..");
	closedir(cartella);
}

void analyzer(int ds_coda){
	msg messaggio;
	char * file;
	int fd, file_size, cont;
	bool eof = 0;
	int contfile = 0;
	int numfile = -1;
	while(1){
		if(msgrcv(ds_coda, &messaggio, sizeof(messaggio)-sizeof(long), ANALYZE, 0)==-1){
		perror("msgrcv analyzer");
		exit(2);
		}
		if(strcmp(messaggio.mtext, END) == 0){
			eof = 1;
			numfile=messaggio.num_file;
		}
		if(numfile==contfile && eof) break;
		if((fd=open(messaggio.mtext, O_RDONLY))==-1){
			perror("open");
			exit(2);
		}
		contfile++;
		file_size=messaggio.dim_file;
		if((file=(char*)mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0))==MAP_FAILED){
			perror("mmap");
			exit(2);
		}
		cont=0;
		for(int i=0; i<file_size; i++){
			if((file[i]>='a' && file[i]<='z') || (file[i]>='A' && file[i]<='Z')) cont++;
		}
		printf("Analyzer: %s  %d\n", messaggio.mtext, cont);
		messaggio.mtype=TOT;
		messaggio.tot_file=cont;
		if(msgsnd(ds_coda, &messaggio, sizeof(messaggio)-sizeof(long), 0)==-1){
			perror("msgsnd analyzer");
			exit(2);
		}
		if(munmap(file, file_size)==-1){
			perror("munmap");
			exit(2);
		}
		if(close(fd)==-1){
			perror("close");
			exit(2);
		}
	}

}

int main(int argc, char *argv[]){
	msg messaggio;
	if(argc>2){
		fprintf(stderr, "Utilizzo: %s [directory]\n", argv[0]);
		exit(1);
	}
	char * path;
	strcpy(path, DEFAULT);
	int ds_coda;
	if(argc==2) path = argv[1];
	if((ds_coda=msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0600))==-1){
		perror("msgget");
		exit(1);
	}
	if(fork() != 0){
		if(fork() != 0){
			bool eof = 0;
			int totale = 0;
			int contfile = 0;
			int numfile = -1;
			while(1){
				if(msgrcv(ds_coda, &messaggio, sizeof(messaggio)-sizeof(long), TOT, 0)==-1){
					perror("msgrcv padre");
					exit(2);
				}
				if(strcmp(messaggio.mtext, END) == 0){
					eof=1;
					numfile=messaggio.num_file;
				}
				if(numfile==contfile && eof){
					printf("numfile: %d, contfile: %d\n", numfile, contfile);
					break;
				}
				contfile++;
				totale+=messaggio.tot_file;
			}
			printf("Padre: totale di %d caratteri alfabetici\n", totale);
		} else{
			int numfile = 0;
			scanner(ds_coda, path, numfile);
			strcpy(messaggio.mtext, END);
			messaggio.num_file=numfile;
			messaggio.mtype=ANALYZE;
			if(msgsnd(ds_coda, &messaggio, sizeof(messaggio)-sizeof(long), 0)==-1){
				perror("msgsnd fine analyzer");
				exit(2);
			}
			messaggio.mtype=TOT;
			if(msgsnd(ds_coda, &messaggio, sizeof(messaggio)-sizeof(long), 0)==-1){
				perror("msgsnd fine padre");
				exit(2);
			}
		}
	} else{
		analyzer(ds_coda);
	}
	msgctl(ds_coda, IPC_RMID, 0);
}