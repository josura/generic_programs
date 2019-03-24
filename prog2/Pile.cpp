#include <iostream>

using namespace std;

/*
	Pile
	Struttura LIFO, last in first out, ogni volta che inseriamo un elemento questo sarà il primo ad essere 
	cancellato. Operazione di inserimento push, di cancellazione pop.
	Una pila può essere realizzata con un array o una lista semplice. Se la pila è vuota dobbiamo fare
	in modo di non poter fare pop, viceversa se è piena. Indice per la cima della pila etc.
*/

const int MaxDimPila=100;

class Pila{
	public:
		Pila();
		void Push(int el);
		int Pop();
		void StampaPila();
		int PilaPiena();
		int PilaVuota();
	private:
		int VettorePila[MaxDimPila];
		int cima;
};

Pila::Pila() : cima(-1) {};

int Pila::PilaPiena() {
	if(cima==(MaxDimPila-1)) return 1;
	else return 0;
}

int Pila::PilaVuota(){
	if(cima==-1) return 1;
	else return 0;
}

void Pila::Push(int x){
	if(PilaPiena()) cout << "Stack overflow! \n";
	else {
		cima++;
		VettorePila[cima]=x;
	}
}

int Pila::Pop(){
	int x;
	if(PilaVuota()){
		cout << "Stack underflow! \n";
		exit(1);
	}
	else{
		x=VettorePila[cima];
		cima--;
		return x;
	}
}

void Pila::StampaPila(){
	if(PilaVuota()) cout << "Cazz stampo, è vuota. \n";
	else{
		for(int i=cima; i>=0; i--) cout << "Posizione " << i << " : " << VettorePila[i] << endl;
	}
}

int main(){
	Pila p;
	p.StampaPila();
	p.Push(4);
	p.Push(7);
	p.Push(8);
	p.StampaPila();
	int x=p.Pop();
	p.StampaPila();
	return 0;
}	