/*
	Un albero è un grafo diretto(un insieme di nodi legati a due a due da archi direzionati) in cui ogni nodo può avere un solo arco 				entrante ed un qualunque numero di archi uscenti.
	I nodi senza archi uscenti sono foglie, i nodi senza archi entranti radici.
	Negli alberi ogni nodo ha al massimo 1 arco entrante. Alberi n-ari, ogni nodo può avere fino ad n successori.
	Nodo che non ha archi entranti: radice; un nodo a cui si arriva figlio, nodi con stesso padre fratelli. Il modo per raggiungere da una 		radice e una foglia è un cammino. I nodi che non hanno archi uscenti sono foglie, se non sono foglie sono nodi interni. Un nodo
	interno è una radice di un sottoalbero.
	Un albero è un insieme di nodi che o è vuoto oppure c'è un nodo che chiamiamo radice da cui discendono 0 o più sottoalberi che
	sono essi stessi alberi. Definizione ricorsiva.
	Arità dell'albero il numero massimo di figli che ha un nodo. Livelli, livello 0 la radice, i figli livello 1 etc. Il numero dei passi da fare
	dalla radice corrisponde al livello.
	La profondità o altezza di un albero è la lunghezza del cammino più lungo da radice a foglia.
	Metteremo un campo padre che punta...al padre.
	Albero equilibrato: albero nel quale tutte le foglie si trovano allo stesso livello e dato k numero massimo di figli per nodo, ogni nodo 		interno ha esattamente k figli. Alberi degeneri: liste.
	Dimostrazione per induzione che un albero binario nella posizione i ha 2^i nodi.
	
	Caso base: radice, 2^0, 1 nodo
	Ipotesi induttiva, 2^k nodi
	2*2^k=2^(k+1)
	
	Contare il numero totale di nodi con k livelli
	Sommatoria(i=0...k) 2^i=2^(k+1)-1
	Dimostrazione per induzione, di nuovo.
	Caso base, k=0. Albero con solo la radice. sommatoria(i=0...0) 2^i=1
	Ipotesi induttiva: sommatoria(i=0...k-1)2^i=2^k - 1
	sommatoria(i=0...k)2^i=sommatoria(i=0...k-1)2^i + 2^k
	Sostituiamo l'ipotesi induttiva
	2^k-1+2^k=(2*2^k)-1=2^(k+1)-1
	
	Come visitare un albero? Deve percorrere tutti i nodi e visitarli massimo 1 volta. Visita in profondità: dopo il nodo corrente viene 			visitato un suo figlio, poi se non c'è un altro figlio si torna indietro (backtracking) verso un altro eventuale figlio.
	Albero binario di ricerca: si applica con una relazione d'ordine. Se y è un nodo nel sottoalbero sinistro di radice x allor il valore
	di y è minore strettamente a quello di x, altrimenti è maggiore o uguale. Il caso dell'uguaglianza si può mettere sia a destra 
	che a sinistra.
	Se abbiamo un albero con 11 nodi e dobbiamo mettere i numeri da 1 a 11, devo mettere 1(il più piccolo) nel ramo che si
	ottiene andando sempre a sinistra, 11 in quello andando sempre a destra. Per prendere 10 vado in un nodo più piccolo di 11
	(andando a sinistra) e lo metto a destra. Sopra 11 il massimo dei rimanenti. Minimo, massimo, vice-minimo, vice-massimo etc.
	Albero binario di ricerca: ogni nodo ha al massimo 2 figli (binari), supponiamo di inserire elementi per i quali sia possibile stabilire
	una relazione di ordinamento.
	Tre strategie fondamentali per visitare un albero binario di ricerca:
	visita preorder(prima la radice, poi sottoalbero sinistro e poi quello destro); inorder(sottoalbero sinistro, radice, sottoalbero destro);
	postorder(prima sottoalbero sinistro, poi quello destro e poi la radice).
	Qual è la complessità? Sicuro almeno n, perché ogni nodo viene visitato almeno 1 volta.
	t(n)={ c se n=0 (il controllo di p=NULL); se n!=0, t(k)+t(n-k-1)+d }, perché k è il numero di elementi nel sottoalbero sinistro, n-k-1
	sottoalbero destro e 1 la radice.
	t(n)<=(c+d)n+c
	Dimostriamo per induzione al solito.
	Caso base, n=0: t(n)<=(c+d)*0 + c
	t(n)<=c, vero perché t(n)=c
	Ipotesi induttiva: Per ogni m<n, t(m)<=(c+d)m+c
	t(n)=t(k)+t(n-k-1)+d<=(c+d)k+c+(c+d)*(n-k-1)+c+d<=(c+d)(k-k+n-1)+2c+d=(c+d)n-c-d+2c+d=(c+d)n+c
	Quindi complessità di O(n)
	
	Procedura di inserimento: prima creo un nodo, qui ci metto il campo valore che intendo inserire; il nodo sarà una nuova foglia.
	Si fa un cammino adeguato fino a raggiungere il padre.
	Complessità della procedura di inserimento: complessità massima n, complessità minima logn, nel caso di albero bilanciato.
	Massimo e minimo banali, per il massimo vado sempre a destra e per il minimo a destra.
	Cancellazione di un nodo: ci sono tre casi, il nodo non ha figli, ne ha uno solo o ne ha due. Vanno dal più semplice al più difficile.
	Nel caso non abbia figli, basta cancellarlo e far puntare il padre a null; nel caso ci sia un solo figlio, basta sostituire padre col figlio.
	Nel caso di due figli, creo il successore y di z(il nodo che voglio cancellare), il successore InOrder per essere precisi, quello
	che nella visita inOrder appare subito dopo di z. Questo
	successore si trova necessariamente nel sottoalbero destro di radice z; y prende la posizione di z nell'albero. Questo y può anche
	essere il minimo del sottoalbero destro di z. Se questo ha un sottoalbero, lo devo prendere a parte; il figlio destro di questo
	dovrà diventare il figlio destro di z; il figlio sinistro quello sinistro di z. Il figlio sinistro del figlio destro di y diventa il figlio destr
	di y. Bel casotto.
	Complessità della cancellazione: data dal minimo, la cui complessità è lineare sull'altezza (caso peggiore: albero degenere); le altre
	hanno complessità costante, sono if e else (if). Anche il successore dipende dall'altezza.
	Dimostriamo per induzione il metodo per calcolare l'altezza. Caso base funziona, viene 0. Il massimo dell'altezza
	tra i due sottoalberi è h-1 per ipotesi induttiva.
*/

#include <iostream>
#include <cstdlib>

const int MaxDimTree=100;

using namespace std;

struct Nodo{
	int val;
	Nodo* left;
	Nodo* right;
	Nodo* padre;
};

class albero{
	public:
		albero() : radice(NULL)	{}
		void Insert(int val);
		void stampa();
		void Trapianta(Nodo* u, Nodo* v);
		void Cancella(Nodo* z);
		Nodo* Find(int x);
		Nodo* Minimo(Nodo* root);
	private:
		void visitaInorder(Nodo* p);
		void Inorder_Iterativa();
		void visitaPreorder(Nodo* p);
		void visitaPostorder(Nodo* p);
		Nodo* radice;
};

struct item{
	Nodo* Elemento;
	item* succ;
};

class Pila{
	private:
		item* p;
		void CancellaNodo();
	public:
		Pila(){p=NULL;}
		bool PilaVuota() {return !p;}
		Nodo* PrimoElemento() {if (p!=NULL) return p->Elemento;}
		void Push(Nodo* x);
		Nodo* Pop();
};

void Pila::Push(Nodo* x){
	item* aux=new item;
	aux->Elemento=x;
	if(p) aux->succ=p;
	else aux->succ=NULL;
	p=aux;
}

void Pila::CancellaNodo(){
	item *pnodo;
	if (p) {
		pnodo=p;
		p=p->succ;
		delete pnodo;
	}
}

Nodo* Pila::Pop(){
	Nodo* e;
	e=PrimoElemento();
	CancellaNodo();
	return e;
}

void albero::Insert(int valore)	{
	Nodo* nuovo=new Nodo;
	Nodo* x=radice, *y=NULL;
	nuovo->val=valore;
	nuovo->left=NULL;
	nuovo->right=NULL;
	while(x!=NULL){
		y=x;
		if (x->val > valore) x=x->left;
		else x=x->right; 
	}
	nuovo->padre=y;
	if (y==NULL) radice=nuovo;
	else if(valore<y->val) y->left=nuovo;
	else y->right=nuovo;	
}

void albero::visitaInorder(Nodo* p){
	if(p!=NULL){
		visitaInorder(p->left);
		cout << p->val << "\t";
		visitaInorder(p->right);
	}
}

void albero::visitaPostorder(Nodo* p){
	if(p!=NULL){
		visitaPostorder(p->left);
		visitaPostorder(p->right);
		cout << p->val << "\t";
	}
}

void albero::visitaPreorder(Nodo* p){
	if(p!=NULL){
		cout << p->val << "\t";
		visitaPreorder(p->left);
		visitaPreorder(p->right);
	}
}

void albero::stampa(){
/*	cout << "Visita Preorder: ";
	visitaPreorder(radice);
	cout << endl; */
	cout << "Visita Inorder ricorsiva: ";
	visitaInorder(radice);
	cout << endl;
	cout << "Visita Inorder iterativa: ";
	Inorder_Iterativa();
	cout << endl;
/*	cout << "Visita Postorder: ";
	visitaPostorder(radice);
	cout << endl << endl; */ 
}

void albero::Inorder_Iterativa(){
	Pila stack;
	Nodo* current=radice;
	bool done=0;
	while(!done){
		if (current!=NULL) {
			stack.Push(current);
			current=current->left;
		}
		else if(stack.PilaVuota())	done=true;
		else{
			current=stack.Pop();
			cout << current->val << "\t";
			current=current->right;
		}
	}
}

void albero::Trapianta(Nodo* u, Nodo* v){
	if(u->padre==NULL) radice=v;
	else if(u==u->padre->left) u->padre->left=v;
	else u->padre->right=v;
	if(v!=NULL) v->padre=u->padre;	
}

Nodo* albero::Minimo(Nodo* x){
	Nodo* min=x;
	while(min!=NULL && min->left!=NULL) min=min->left;
	return min;
}

void albero::Cancella(Nodo* z){
	if(z==NULL) exit(0);
	Nodo* y;
	if(z->left==NULL) Trapianta(z,z->right);
	else if	(z->right==NULL) Trapianta(z,z->left);
	else{
		y=Minimo(z->right);
		if(y->padre!=z){
			Trapianta(y,y->right);
			y->right=z->right;
			y->right->padre=y;
		}
		Trapianta(z,y);
		y->left=z->left;
		y->left->padre=y;
	}
	delete z;
}

Nodo* albero::Find(int x){
	Nodo* iter=radice;
	while(iter!=NULL && x!=iter->val){
		if(x<iter->val) iter=iter->left;
		else iter=iter->right;
	}
	return iter;
}

int main(){
	albero tree;
	/*tree.Insert(6);
	tree.stampa();
	tree.Insert(5);
	tree.stampa();
	tree.Insert(7);
	tree.stampa();
	tree.Insert(2);
	tree.stampa();
	tree.Insert(8);
	tree.stampa();
	tree.Insert(5);
	tree.stampa();*/
	tree.Insert(26);
	tree.Insert(15);
	tree.Insert(37);
	tree.Insert(2);
	tree.Insert(48);
	tree.Insert(19);
	tree.Insert(16);
	tree.Insert(17);
	tree.stampa();
	Nodo* elem=tree.Find(15);
	if(elem==NULL) cout << "Elemento non trovato!\n" << endl;
	else{
		cout << "Elemento da cancellare: " << elem->val << endl;
		tree.Cancella(elem);
		tree.stampa();
	}
	return 0;
}