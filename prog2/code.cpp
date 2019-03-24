#include <iostream>

using namespace std;

/*
	Struttura FIFO, first in first out; accesso alla struttura dati da 2 punti invece che 1. Due indici, uno fronte e uno fine, si sposta la fine
	della coda, l'inserimento viene fatto là.
	Operazioni: enqueue: aggiunge un elemento alla coda
	dequeue: rimuovere un elemento, quello in testa
	front: legge l'elemento in testa
	isEmpty: vuota, isFull piena.
	Implementandola con un array e aggiungendo e "rimuovendo" elementi, ad un certo punto l'array sarà pieno. Appena arrivo alla 		  	posizione 4 di un array di 5 elementi, quindi l'ultima, poi ricomincio da 0. Uso l'operazione modulo, array circolari.
	Aggiungiamo un campo di numero di elementi presenti nella coda.
*/

const int MaxDimCoda=10;

class Coda{
	public:
		Coda();
		void Enqueue(int elem);
		int Dequeue();
		void StampaCoda();
		int Testa() {return testa;}
		bool CodaVuota() {return num_elementi==0;}
		bool CodaPiena() {return num_elementi==MaxDimCoda;}
	private:
		int VettoreCoda[MaxDimCoda];
		int testa;
		int fine;
		int num_elementi;
};

Coda::Coda(): testa(0), fine(-1), num_elementi(0)	{}

void Coda::Enqueue(int elemento){
	if(CodaPiena()) cerr << "Coda piena!\n";
	else{
		fine=(fine+1)%MaxDimCoda;
		VettoreCoda[fine]=elemento;
		num_elementi++;
	}
}

int Coda:: Dequeue(){
	if(CodaVuota()){
		cerr << "Coda vuota!\n";
		return -1;
	}
	else{
		int x=VettoreCoda[testa];
		testa=(testa+1)%MaxDimCoda;
		num_elementi--;
		return x;
	}
}

void Coda::StampaCoda(){
	if(CodaVuota()) cerr << "Coda vuota!\n";
	else{
		int i=testa, x=0;
		while((i % MaxDimCoda)!=fine){
			cout << "Posizione " << x << " : " << VettoreCoda[i % MaxDimCoda] << endl;
			x++; i++;
		}
		cout << "Posizione " << x << " : " << VettoreCoda[fine] << endl;
	}
}

int main(){
	Coda coda;
	int x=coda.Dequeue();
	for(int i=0; i<MaxDimCoda; i++) coda.Enqueue((i+1)*10);
	cout << endl;
	coda.StampaCoda();
	for(int i=0; i<MaxDimCoda-1; i++) coda.Dequeue();
	cout << endl;
	coda.StampaCoda();
	for(int i=0; i<MaxDimCoda; i++) coda.Enqueue((i+1)*7);
	coda.StampaCoda();
	return 0;
}