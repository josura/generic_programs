/*
Generalizzazione degli alberi. Nodi uniti a due a due da degli archi. G=(V,E), vertex(nodi) ed edges(archi). Questi ultimi sono indicati da
una coppia di nodi. Se G è direzionato un arco ha una sola direzione, è uscente da un nodo ed entrante da un altro. La proprietà di
adiacenza è simmetrica se il grafo non è diretto/direzionato. Grado di un nodo: nel caso di un grafo diretto, il grado è il numero di archi
entranti più il numero di quelli uscenti, se non è direzionato è solo il numero di archi entranti. Il modo per collegare un nodo u ad un nodo v è un cammino. Cammino con vertici v0...vk e archi (v0,v1),(v1,v2)...(vk-1,vk). Il cammino è semplice se non ci sono ripetizioni.
Sottocmmino: sequenza di vertici vi...vj con 0<=i<=j<=k
Ciclo: cammino v0...vk con v0=vk. Ciclo semplice se tutti i nodi sono distinti. Un grafo senza cicli è aciclico.
Grafo connesso (per i grafi indiretti): ogni coppia di nodi è collegata da un cammino, ogni nodo è raggiungibile. Le componenti connesse rappresentano le classi di equivalenza determinate dalla relazione "è raggiungibile da".
Grafo(direzionato) fortemente connesso: per ogni coppia di vertici esiste un cammino che li unisce sia da u a v che da v ad u.
Componenti fortemente connesse: classi di equivalenza, relazione "sono mutualmente raggiungibili".
Sottografo: G'(V',E') con V' sottoinsieme di V e E' sottoinsieme di E. Grafo completo: dati due nodi qualsiasi c'è un arco che li collega.
Per rappresentare un grafo ci sono due modi, le liste di adiacenza e le matrici di adiacenza. Liste di adiacenza: utile quando abbiamo
pochi archi, un grafo sparso; si associa una lista concatenata ad ogni nodo. Matrici di adiacenza: mettiamo 1 nella posizione i,j se il
nodo i e j sono collegati. Lista di adiacenza, grafi non direzionati: una lista per ogni elemento, lista che contiene gli elementi a lui
adiacenti. Lo spazio necessario è al massimo 2|E|, perché considerando l'arco (u,v) c'è anche l'arco (v,u), però noi siamo fighi e togliamo la costante. Grafi direzionati: la somma delle lunghezze di tutte le liste è |E|.
Ricerca:
*/

#include <iostream>

using namespace std;

template<class T>
struct Nodo{
	T valore;
	Nodo<T>* succ;
};

template <class T>
class Lista{
	public:
		Lista(){testa=NULL;}
		~Lista();
		void print();
		void insert(T val);
		Nodo<T>* RivelaTesta() {return testa;}
		Nodo<T>* search(int val);
	private:
		Nodo<T>* testa;
};

template <class T> Lista <T> :: ~Lista() {
	Nodo<T>* iter=testa;
	while(iter!=NULL){
		Nodo<T>* temp=iter->succ;
		delete iter;
		iter=temp;
	}
}

template <class T> void Lista <T>:: print(){
	Nodo<T>* iter=testa;
	while(iter!=NULL){
		cout << "  " << iter->valore << "\t";
		iter=iter->succ;
	}
}

template <class T> void Lista <T>:: insert(T val){
	Nodo<T>* nuovo=new Nodo<T>;
	nuovo->valore=val;
	nuovo->succ=testa;
	testa=nuovo;
}

template <class T> Nodo<T>* Lista <T>:: search(int indice){
	Nodo<T>* p;
	for(p=testa; p!=NULL; p=p->succ){
		if(p->valore==indice) return p;
	}
	return NULL;
}

template <class H>
class LGraph{
	private:
		int len, n, m; //n numero di nodi effettivo, len numero massimo di nodi, m numero di archi effettivo
		int t;
		H **K;        //array di nodi allocati dinamicamente
		Lista<int> **Adj;				//array di liste allocate dinamicamente
		int findIndex(H x){             //trova l'elemento che cerca e restituisce l'indice 
			for(int i=0; i<n; i++){     //scorri tutto l'array di nodi 
				if(*K[i]==x) return i;	//se il valore del nodo *K[i] è uguale a quello che si sta cercando, ritorna;
			}
			return -1;   				//altrimenti il nodo non è nella lista
		}
	public:
		LGraph(int len){				//costruttore che inizializza il grafo(con il numero di nodi massimo effetivo)
			this->len=len;				//si poteva fare pure con la lista di inizializzazione
			n=m=0;						//nodi inizili e archi 0
			K=new H*[len];				//incomincia la costruzione dell'array di nodi 
			for(int i=0; i<len; i++) K[i] = NULL;		//inizializzali tutti a NULL
			Adj=new Lista<int>*[len];	//costruzione dell'array di adiacenza
			for(int i=0; i<len; i++){
				Adj[i]=new Lista<int>();		//inizializzali facendo liste vuote
			}
		}
		LGraph<H>* addNode(H k){            //aggiungi un nodo al grafo tenendo conto che non deve superare il numero di nodi
			if(n==len) return this;			//non è possibile più aggiungere nodi
			if(findIndex(k)>=0) return this;		//è stato trovato già il nodo che si voleva aggiungere
			K[n]=new H(k);					//finalmente e possibile aggiungerlo se non sono accadute le cose descritte sopra
			n++;							//aumenta il numero di nodi
			return this;
		}
		LGraph<H>* addEdge(H x, H y){      //aggiungi un arco dal nodo x al nodo y
			int i=findIndex(x);				//trova x nell'array di puntatori a nodi 
			int j=findIndex(y);				//trova y
			if(i<0 || j<0) return this;		//non li ha trovati
			if(!Adj[i]->search(j)){ //controllo se l'elemento in questione non c'è già chiamando search di LList
				Adj[i]->insert(j);    //lo inserisco nella lista
				m++;			//aumento i nodi
			}
			return this;
			}
			void print(){
				for(int i=0; i<n; i++){
					cout << "(" << i << ", " << *K[i] << ")" << " : ";
					Adj[i]->print();
					cout << endl;
				}
			}
};

template <class H> class MGraph{
	private:
		int len, n, m;     //solito per l'altro
		int **M;		//matrice per gli archi
		H **K;			//vertici
		int findIndex(H x){			//per trovare l'indice(n questo caso la riga della matrice)
			for(int i=0; i<n; i++){
				if(*K[i]==x) return i;
			}
			return -1;
		}
	public:
		MGraph(int len){
			this->len=len;
			n=m=0;
			M=new int*[len];
			for(int i=0; i<len; i++){
				M[i] = new int [len];
				for(int j=0; j<len; j++)
					M[i][j]=0;
			}
			K=new H*[len];
			for(int i=0; i<len; i++) K[i]=NULL;
		}
		MGraph<H>* addNode(H k){
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n]=new H(k);
			n++;
			return this;
		}
		MGraph<H>* addEdge(H x, H y){
			int i=findIndex(x);
			int j=findIndex(y);
			if(i<0 || j<0) return this;
			if(!M[i][j]){
				M[i][j]=1;
				m++;
			}
			return this;
		}
		void print(){
			for(int i=0; i<n; i++){
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0; j<n; j++){
					if(M[i][j]) cout << *K[j] << " ";
				}
				cout << endl;
			}
		}
};

int main(){
	/*LGraph<char> *Gr = new LGraph<char>(9);
	Gr->addNode('1')->addNode('2')->addNode('3')->addNode('4')->addNode('5')->addNode('6')->addNode('7')->addNode('8');
	Gr->addEdge('0', '8')->addEdge('0','1')->addEdge('1','8')->addEdge('2','4')->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3')->addEdge('4','0')->addEdge('5','6')->addEdge('5','3')->addEdge('6','5')->addEdge('8','2');
	Gr->print();*/
	MGraph<char> *Gr = new MGraph<char>(9);
	Gr->addNode('1')->addNode('2')->addNode('3')->addNode('4')->addNode('5')->addNode('6')->addNode('7')->addNode('8');
	Gr->addEdge('0', '8')->addEdge('0','1')->addEdge('1','8')->addEdge('2','4')->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3')->addEdge('4','0')->addEdge('5','6')->addEdge('5','3')->addEdge('6','5')->addEdge('8','2');
	Gr->print();
	return 0;
}