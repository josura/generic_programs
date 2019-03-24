#include <iostream>

using namespace std;

/* 
	I sistemi operativi danno l'illusione del parallelismo con il multitasking. La CPU divide il suo tempo tra più programmi.
	L'ordine di esecuzione di programmi (scheduling della CPU) può avvenire FCFS(first come first served) o Shortest Job First.
	Con 4 programmi, P0=21 ms, P1=3 ms, P2= 1ms, P3=2 ms, con la prima strategia c'è un tempo medio di attesa di 17,5 ms tra
	un'operazione e l'altra; con la seconda c'è solo 2,5 ms di media.
	Ecco a che servono gli algoritmi di ordinamento, che devono essere efficenti.
	Ordinamento per scambio:
	Confrontare il primo elemento con tutti gli altri e facciamo uno scambio se l'ordinamento non è corretto; alla fine nella
	prima posizione ci sarà il minimo, lo rifaccio nell'array più piccolo etc.
*/

void scambia(int& a, int& b){
	int aux=a;
	a=b;
	b=aux;
}

void OrdScambio(int a[], int n){
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			if(a[i]>a[j]) scambia(a[i],a[j]);
		}
	}
}

void Stampa(int a[], int n){
	for(int i=0; i<n; i++) cout << a[i] << " ";
	cout << endl;
}

int main(){
	int v[10]={4,7,1,23,3,2,134,9,11,8};
	cout << "Vettore iniziale: \n";
	Stampa(v, 10);
	OrdScambio(v,10);
	cout << "Vettore finale: \n";
	Stampa(v, 10);
	return 0;
}