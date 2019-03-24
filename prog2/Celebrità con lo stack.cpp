#include <iostream>
#include <time.h>
#include <stdlib.h>
#define INVITATI 30

using namespace std;

class Invitato{
	private:
		bool celebrita;
		int posizione;
	public:
		void Inizializza(bool val, int pos){celebrita=val; posizione=pos;}
		bool ECelebrita(){return celebrita;}
		bool conosce(Invitato);
		int RivelaPos(){return posizione;}
};

bool Invitato::conosce(Invitato a)	{
	if(a.ECelebrita()) return 1;
	else return 0;
}

void Inizializza(Invitato a[]){
	srand(time(0));
	int indice=rand()%INVITATI;
	cout << "Valore casuale: " << indice << endl;
	for(int i=0; i<INVITATI; i++){
		if(i==indice) a[i].Inizializza(1,i);
		else a[i].Inizializza(0,i);
	}
}

class Nodo{
	public:
		Nodo(Invitato x) {p=x; succ=NULL;}
		Invitato get_invitato(){return p;}
		void Assegna(Invitato x){p=x;}
		Nodo* Successivo(){return succ;}
		void AssegnaSuccessivo(Nodo* p){succ=p;}
	private:
		Invitato p;
		Nodo* succ;
};

class Pila{
	public:
		Pila() {pp=NULL;}
		~Pila();
		bool PilaVuota() {return !pp;}
		bool SoloUno(){
			if ((pp!=NULL) && (pp->Successivo()==NULL))) return 1;
			else return 0;
		}
		Invitato PrimoElemento(){
			if(pp!=NULL) return pp->get_invitato();
			else return NULL;
		}
		void Push(Invitato x);
		Invitato Pop();
		//void StampaPila();
	private:
		Nodo *pp;
		void CancellaNodo();
};
/*
void Pila::StampaPila(){
	Nodo* pnodo=p;
	if(pnodo==NULL) cout << "Lista vuota! \n";
	while (pnodo!=NULL){
		cout << pnodo->get_valore() << endl;
		pnodo=pnodo->Successivo();
	}
}*/

void Pila::Push(Invitato x){
	Nodo* aux=new Nodo(x);
	if (pp) aux->AssegnaSuccessivo(pp); //abbiamo esposto la testa, inserimento in testa
	p=aux;
}

void Pila::CancellaNodo(){
	Nodo* pnodo;
	if (pp) {
		pnodo=pp;
		pp=pp->Successivo();
		delete pnodo;
	}
}

Invitato Pila::Pop(){
	Invitato e;
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
}