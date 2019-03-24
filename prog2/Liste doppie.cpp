#include <iostream>

using namespace std;

struct Nodo{
	int valore;
	Nodo* succ;
	Nodo* prec;
};

class ListaDoppia{
	public:
		ListaDoppia(){testa=NULL;}
		~ListaDoppia();
		void stampa();
		void inserisci_in_testa(int val);
		void inserisci_in_coda(Nodo* p, int val);
		void inserisci(Nodo* prec, Nodo* succ, int val);
		Nodo* Ricerca(int val);
		Nodo* head(){return testa;}
	private:
		Nodo* testa;
};

ListaDoppia:: ~ListaDoppia(){
	Nodo* iter=testa;
	while(iter!=NULL){
		Nodo *temp=iter->succ;
		delete iter;
		iter=temp;
	}
}

void ListaDoppia::stampa(){ //stampo sia il successivo che il precedente, per essere certi che i puntatori funzionino correttamente
	Nodo* iter=testa;
	while(iter!=NULL){
		cout << " " << iter->valore << "\t Successivo: ";
		if(iter->succ!=NULL) cout << iter->succ->valore;
		else cout << "NULL";
		cout << "\t Precedente: ";
		if(iter->prec!=NULL) cout << iter->prec->valore << endl;
		else cout << "NULL\n";
		iter=iter->succ;
	}
}

void ListaDoppia:: inserisci_in_testa(int val){
	Nodo* nuovo=new Nodo;
	nuovo->valore=val;
	if(testa!=NULL){
		nuovo->succ=testa;
		testa->prec=nuovo;
		testa=nuovo; //è importante l'ordine! Se faccio questo prima sballa tutto
	}
	else {
		testa=nuovo;
		nuovo->succ=NULL;
		nuovo->prec=NULL;
	}
}

void ListaDoppia::inserisci(Nodo* precedente, Nodo* successivo, int val){
	Nodo* nuovo=new Nodo;
	nuovo->valore=val; //allochiamo e settiamo il valore del nuovo nodo
	nuovo->succ=successivo;
	nuovo->prec=precedente;
	successivo->prec=nuovo;
	precedente->succ=nuovo;
}

void ListaDoppia::inserisci_in_coda(Nodo* p, int val){
	Nodo* nuovo=new Nodo;
	nuovo->valore=val;
	nuovo->succ=NULL; //perché lo sto inserendo in coda, non ha successivo
	nuovo->prec=p;
	p->succ=nuovo;
}

int main(){
	ListaDoppia lista;
	for(int i=10; i>0; i--) lista.inserisci_in_testa(i*10);
	lista.stampa();
	cout << "Immettere l'elemento da inserire: ";
	int x; cin >> x;
	if(lista.head()->valore > x) lista.inserisci_in_testa(x);
	else{
		Nodo* p=lista.head();
		while((p->succ!=NULL) && (p->succ->valore <= x)){
			p=p->succ;
		}
		if(p->succ!=NULL) lista.inserisci(p, p->succ, x);
		else {
			lista.inserisci_in_coda(p,x);
		}
	}
	lista.stampa();
	return 0;
}

/*
	Nodi che puntano alle posizioni a sinistra e a destra (posizioni logiche, non ci sono realmente in memoria).
	Ho due nodi, A e B: A punta a B, B punta ad A. Per inserire un elemento C, il successivo di C diventa il successivo di A,
	dopo il successivo di A diventa C, il precedente di C deve diventare A, e il precedente di B deve diventare C.	
*/
