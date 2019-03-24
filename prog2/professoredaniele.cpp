// Daniele Alma X81000455

#include<fstream>
#include<cstdlib>
#include<iostream>
#include <string>
#include <sstream>
#include<algorithm>

using namespace std;

void selectionsort(char *a, int n){
	int min;
	int tmp;
	for(int i=0; i<n-1; i++){
		min = i;
		for(int j=i+1; j<n; j++){
			if(a[j]<a[min]) min = j;
		}
		tmp = a[i];
		a[i]=a[min];
		a[min]=tmp;
	}
}

int main(){
	ifstream read;
	ofstream write;
	unsigned short numcifre;
	bool nonpresente = true;
	read.open("input.txt");
	if (read.fail())
	{
		cout<< "Apertura input.txt fallita!\n";
		exit(1);
	}
	write.open("output.txt");
	if(write.fail())
	{
		cout << "Non sono riuscito a scrivere l'output.txt!'\n";
		exit(1);
	}
	while(!read.eof()){
		nonpresente = true;
		string combinazione, promemoria;
		unsigned short n,w = 0;
		read >> numcifre;
		char alfabeto[numcifre];
		char wildcard[numcifre];
		for(int i=0; i<numcifre; i++) read >> alfabeto[i];
		read >> promemoria;
		for(int j=0;j<numcifre;j++){
   			nonpresente=true;
   			for(int k=0;k<numcifre && nonpresente;k++){
    			if(promemoria[k]==alfabeto[j]) nonpresente=false;
   			}
   		if(nonpresente) wildcard[n++]=alfabeto[j];
  		}
		selectionsort(wildcard,n);
		for(int i=0; i<n; i++) cout << endl << wildcard[i];
		do{
			w=0;
			combinazione = promemoria;
			for(int i=0; i<numcifre; i++){
				if(promemoria[i]=='*'){
					combinazione[i]=wildcard[w++];
				}
			}
		write << combinazione << " ";
		} while(next_permutation(wildcard,wildcard+n));
		write << endl;
	}
	read.close();
	write.close();
	return 0;
}
