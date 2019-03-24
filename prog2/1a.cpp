#include <iostream>

using namespace std;

void inserire(int a[], int n){
	for(int i=0; i<n; i++){
		cout<< "Inserire un intero: ";
		cin >> a[i];
		cout << endl;
	}
}

void stampa(int a[], int n){
	for(int i=0; i<n; i++){
		cout << a[i] << "|";
	}
}

int* concatena(int a[], int b[], int n){
	int* puntatore;
	//int* c;
	//int c[2*n];
	int * c = new int[2*n];
	for(int i=0; i<n; i++){
		c[i]=a[i];
		c[n+i]=b[i];
	}
	puntatore=c;
	cout << "Vettore ottenuto dopo la concatenazione: " << endl;
	stampa(puntatore, 2*n);
	return puntatore;
}

int main(){
	int a[6], b[6];
	int * c;
	cout << "Creazione del vettore a: " << endl;
	inserire(a,6);
	stampa(a,6);
	cout << "Creazione del vettore b: " <<endl;
	inserire(b,6);
	stampa(b,6);
	c=concatena(a,b,6);
	cout << "Vettore ottenuto dopo la concatenazione: "  << endl;
	stampa(c,12);
	return 0;
}