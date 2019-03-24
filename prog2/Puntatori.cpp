#include <iostream>

using namespace std;

void stampa1(int a[], int n){
	for(int i=0; i<n; i++)
		cout << *(a+i) << " ";
	cout << endl;
}
void stampa2(int a[], int n){
	int* p=a;
	for(int i=0; i<n; i++)
		cout << *p++ << " ";
	cout << endl;
}

void stampa3(int a[], int n){
	for(int i=0; i<n; i++)
		cout << *a++ << " ";
	cout << endl; 
}

void stampap(int* v[], int n){
	for(int i=0; i<n; i++)
		cout << **(v+i) << " ";
	cout << endl;
}

double inversi(int k){
	if (k==0) return 0;
	else return 1.0/k;
}

double quadrati(int k){
	return (double) k*k;
}

double somma(int n, double (*f) (int)){ //puntatore a funzione generica che prende in input un intero
	double s=0;
	for(int i=1; i<=n; i++) s+=f(i);
	return s;
}

void bubblesort(int*v[], int n){
	for(int i=0; i<n-1; i++){
		for(int k=0; k<n-1-i; k++){
			if(*v[k]>*v[k+1]) {
				int *temp=v[k];
				v[k]=v[k+1];
				v[k+1]=temp;
			}
		}
	}
}

int main(){
	int n=10;
	int a[]={1,2,5,8,2,3,5,4,2,0};
	int* b[10];
	stampa3(a,n);
	stampa1(a,n);
	stampa2(a,n);
	/* for(int i=0; i<n; i++)
			cout << *a++ << " ";
		 Non si può fare! Il nome dell'array è un puntatore costante, non posso incrementarlo. Nel metodo
		 veniva copiato quindi si poteva fare */
	char c;
	char* primo;
	primo=&c;
	for(c='A'; c<='Z'; c++) cout << *primo << ", ";
	cout << endl << "Somma degli inversi dei primi 5 interi:"
		<< somma(5,inversi);
	cout << endl << "Somma dei quadrati dei primi 5 interi:"
		<< somma(5,quadrati);
	for(int i=0; i<10; i++) b[i]=a+i;
	cout << endl << "A: " << endl;
	stampa2(a,10);
	cout << "B: " << endl;
	stampap(b,10);
	bubblesort(b,10);
	cout << "A: " << endl;
	stampa2(a,10);
	cout << "B: " << endl;
	stampap(b,10);
	return 0;
}

/*
	
 */