/* aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa(aa)aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
	Strutture dati
	Con accesso diretto: array, senza dover attraversare la sequenza
	Accesso sequenziale: per raggiungere l'elemento i-esimo dobbiamo percorrere gli elementi nelle posizioni precedenti.
	Liste: gli elementi sono in sequenza da un punto di vista logico, sono disposti in modo arbitrario a livello fisico.
	Se volessi memorizzare un certo numero di oggetti molto grande indefinito usare un array non è la soluzione efficente.
	Ogni volta che mi serve più spazio faccio un nuovo array e ne distruggo un altro...?Nah. L'operazione costa abbastanza, O(n).
	Soluzione con costo ammortizzato:
	d: dimensione array; n(num elementi)<=d. L'unica volta che dovrò fare un raddoppio è O(n), aggiungendo gli elementi da n a 2n
	abbiamo complessità O(1). (n+n)/2.
	Algoritmo di cancellazione: finché il numero di elementi è inferiore a 1/4 della dimensione dell'array, continuo a cancellare,
	sennò riduco la dimensione. Faccio cancellazioni finché n=d/4, in quel caso scatta la contrazione e alloco un array di
	dimensione metà e copio gli elementi. L'applicazione di copia mi costa O(n), ma ho le prime n operazioni hanno O(1) ognuna,
	quindi costanti; mediamente il costo è basso, sempre costante, ma si occupa sempre il doppio dello spazio.
	Lista concatenata: oltre ad avere lo spazio per contenere l'elemento, devo averlo per il puntatore; lo spreco di spazio è
	sempre più significativo negli array. Con la lista prendo un campo dati e un campo puntatori(32 bit). Una sequenza lineare di
	elementi che non necessariamente occupa zone contigue di memoria. Liste doppiamente concatenate: con 3 campi, ogni elemento ha
	anche un puntatore al precedente, si può scorrere da testa e coda e viceversa. Liste circolari semplici: l'ultimo elemento
	punta al primo, non c'è un vero e proprio primo elemento; lista circolare doppiamente concatenata, due versi.
	Nel caso delle liste concatenate l'inserimento è costante, a differenza degli array in cui il caso peggiore è n.
	Si definisce una struttura dati nodo, con un intero e un puntatore al nodo, o una classe, è uguale. */

#include <iostream>

using namespace std;

class Elemento{ //Modo 1
	public:
		int valore;
		Elemento* succ;
		Elemento(Elemento* n, int d) : succ(n), valore(d) {} //Ogni volta che viene creato quest'oggetto (il nodo) lo metto in testa
};

void stampa(Elemento* p){
	Elemento* primo=p;
	while(primo!=NULL){
		cout << " " << primo->valore << endl;
		primo=primo->succ;
	}
}

struct Nodo{ //Modo 2
	int valore2;
	Nodo* succ2;
};

void inserisci(Nodo*& testa, int val){ //Come il costruttore del modo 1
	Nodo* nuovo=new Nodo;
	nuovo->valore2=val;
	nuovo->succ2=testa;
	testa=nuovo; //sto spostando la testa al primo elemento.
}

void stampa2(Nodo* p){
	Nodo* primo=p;
	while(primo!=NULL){
		cout << " " << primo->valore2 << endl;
		primo=primo->succ2;
	}
}

struct lista{ //Modo 3
	Nodo* testa;
};

void inserisci2(lista& L, int val){
	Nodo* nuovo=new Nodo;
	nuovo->valore2=val;
	nuovo->succ2=L.testa;
	L.testa=nuovo;
}

void stampa3(lista L){
	while(L.testa!=NULL){
		cout << " " << L.testa->valore2 << endl;
		L.testa=L.testa->succ2;
	}
}

int main(){
	Elemento* testa=NULL;
	testa=new Elemento(testa,1); //Testa qua vale NULL, il primo nodo conterrà 1 e punterà a NULL
	testa=new Elemento(testa,2); //Quando creo un nuovo nodo, questo punterà alla testa corrente. Quindi ora la lista contiene 2 1
	testa=new Elemento(testa,3); 
	stampa(testa); //Saranno stampati in ordine decrescente perché il costruttore inserisce il valore che gli dò in input nel valore
	//e il successivo è quello che va in input
	
	Nodo* testa2=NULL;
	inserisci(testa2,1);
	inserisci(testa2,2);
	inserisci(testa2,3);
	stampa2(testa2);
	
	lista L;
	L.testa=NULL;
	inserisci2(L,1);
	inserisci2(L,2);
	inserisci2(L,3);
	stampa3(L);
	
	return 0;
}