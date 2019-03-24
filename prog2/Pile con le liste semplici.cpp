#include <iostream>

using namespace std;

/*
	Pile
	Struttura LIFO, last in first out, ogni volta che inseriamo un elemento questo sarà il primo ad essere 
	cancellato. Operazione di inserimento push, di cancellazione pop.
	Una pila può essere realizzata con un array o una lista semplice. Se la pila è vuota dobbiamo fare
	in modo di non poter fare pop, viceversa se è piena. Indice per la cima della pila etc.
*/

class Nodo{
	public:
		Nodo(int x) {valore=x; succ=NULL;}
		int get_valore(){return valore;}
		void Assegna(int x){valore=x;}
		Nodo* Successivo(){return succ;}
		void AssegnaSuccessivo(Nodo* p){succ=p;}
	private:
		int valore;
		Nodo* succ;
};

class Pila{
	public:
		Pila() {p=NULL;}
		~Pila();
		bool PilaVuota() {return !p;}
		int PrimoElemento(){
			if(p!=NULL) return p->get_valore();
			else return -1;
		}
		void Push(int x);
		int Pop();
		void StampaPila();
	private:
		Nodo *p;
		void CancellaNodo();
};

void Pila::StampaPila(){
	Nodo* pnodo=p;
	if(pnodo==NULL) cout << "Lista vuota! \n";
	while (pnodo!=NULL){
		cout << pnodo->get_valore() << endl;
		pnodo=pnodo->Successivo();
	}
}

void Pila::Push(int x){
	Nodo* aux=new Nodo(x);
	if (p) aux->AssegnaSuccessivo(p); //abbiamo esposto la testa, inserimento in testa
	p=aux;
}

void Pila::CancellaNodo(){
	Nodo* pnodo;
	if (p) {
		pnodo=p;
		p=p->Successivo();
		delete pnodo;
	}
}

int Pila::Pop(){
	int e;
	e=PrimoElemento();
	CancellaNodo();
	return e;
}

Pila::~Pila(){
	Nodo* pnodo;
	while(p!=0){
		pnodo=p;
		p=p->Successivo();
		delete pnodo;
	}
}

int main(){
	Pila p;
	p.Push(4);
	p.Push(5);
	p.Push(12);
	p.StampaPila();
	while(!p.PilaVuota()){
		cout << p.PrimoElemento() << "\t";
		p.Pop();
	}
	cout << endl;
	p.Push(34);
	p.StampaPila();
	p.~Pila();
	p.StampaPila();
	return 0;
}	