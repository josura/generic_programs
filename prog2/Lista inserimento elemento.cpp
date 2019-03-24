#include <iostream>

using namespace std;

struct Nodo{
	int valore;
	Nodo* succ;
};

class ListaSemplice{
	public:
		ListaSemplice(){testa=NULL;}
		~ListaSemplice();
		void stampa();
		void inserisci_in_testa(int val);
		void inserisci(Nodo* precedente, Nodo* seguente, int val);
		Nodo* RivelaTesta(){return testa;}
	private:
		Nodo * testa;
};

ListaSemplice::~ListaSemplice(){
	Nodo* iter=testa;
	while(iter!=NULL){
		Nodo* temp=iter->succ; //Prima mi creo una copia del successivo
		delete iter; //cancello l'elemento corrente, al primo giro la testa
		iter=temp; //E mi sposto all'indirizzo del successivo
	}
}

void ListaSemplice::stampa(){
	Nodo* iter=testa;
	while(iter!=NULL){
		cout << " " << iter->valore << endl;
		iter=iter->succ;
	}
	cout << endl;
}

void ListaSemplice::inserisci_in_testa(int val){
	Nodo* nuovo=new Nodo;
	nuovo->valore=val;
	nuovo->succ=testa;
	testa=nuovo;
}

void ListaSemplice::inserisci(Nodo* precedente, Nodo* seguente, int val){
	Nodo* nuovo=new Nodo;
	nuovo->valore=val;
	nuovo->succ=seguente; //senza seguente nuovo->succ=precedente->succ; Bisogna controllare se precedente è un puntatore a NULL, perché sennò non potrei fare l'assegnamento
	precedente->succ=nuovo;
}

int main(){
	ListaSemplice lista;
	Nodo* p;
	lista.inserisci_in_testa(20);
	lista.inserisci_in_testa(10);
	lista.inserisci_in_testa(5);
	lista.stampa();
	p=lista.RivelaTesta();
	while((p!=NULL) && (p->valore!=10)) p=p->succ;
	if(p!=NULL) lista.inserisci(p,p->succ,15);
	lista.stampa();
	return 0;
}

/*
	Ricerca di un elemento in una lista. Ci creiamo un puntatore di supporto che fa da iteratore. Inizialmente punterà alla testa.
	Se il puntatore è diverso da NULL, controlliamo che sia uguale a quello che dobbiamo cercare e facciamo quello che dobbiamo
	fare. Restituiamo NULL se non lo troviamo, l'indirizzo dell'elemento se c'è.
*/