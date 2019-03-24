#include<iostream>
/* 
Corso di Programmazione II - Prof. Dario Catalano.
Soluzione della prova d'esame del 24/06/2014. 
Il compito è svolto facendo uso di templates. 
Come per la precedente versione,
la delete non aggiorna il campo depth
(aggiungere tale modifica è banale).
*/
using namespace std;

template <class T> class BST	{
public: 
	virtual BST<T>* insert(T* x) =0; 
	virtual BST<T>* del(T* x) =0;
	virtual int search(T* x) =0;
	virtual void naturalFill(T* v)=0; 
	virtual void postorderPrint()=0;
	virtual void printLevel(int l)=0;
};

template <class T> class Nodo	{
private:
	Nodo<T>* padre, *left, *right; 
	T* chiave; 
	int depth; 
public:
	Nodo(T* val) {			
		chiave=val; 
		padre=left=right=NULL; 
		depth=0; }
	T* getChiave() {return chiave;}	
	int getDepth() {return depth;} 
	void setDepth(int p) {depth=p;} 
	void setPadre(Nodo<T>* p) {padre=p;}
	Nodo<T>* getPadre() {return padre;}
	Nodo<T>* getDestro() {return right;}
	void setDestro(Nodo<T>* p) {right=p;}
	Nodo<T>* getSinistro() {return left;}
	void setSinistro(Nodo<T>* p) {left=p;}
	void setChiave(T* p) {chiave=p;}
};


template <class T> class albero : public BST<T> {
private:
	Nodo<T>* radice; 
	int size; 
public:
	albero() {radice=NULL; size=0;}
	Nodo<T>* getRoot() {return radice;}
	int getSize() {return size;}
	void setRoot(Nodo<T>* p) {radice=p;}
	void setSize(int p)	{size=p;}
	bool isEmpty() {return (size==0);}
	BST<T>* insert(T* x); 
	void postorder(Nodo<T>* p, int level); 
	void postorderPrint();
	Nodo<T>* searchPointer (T* p); // restituisce il nodo 
			// dove si trova p
	int search (T* p);  
	Nodo<T>* searchInt(T p); // come searchPointer 
			// ma prende in input un elemento di tipo T piuttosto 
			// che un puntatore. Usata nel main per testare la 
			// delete
	void Trapianta(Nodo<T>* u, Nodo<T>* v); 
	Nodo<T>* Minimo(Nodo<T>* p);
	BST<T>* del(T* p);
	void printLevel(int l);
	void naturalFill(T* v);
	Nodo<T>* successore(Nodo<T>* p);
};


template <class T> BST<T>* albero <T>:: insert (T* key)
//BST* albero :: insert (int* key)	
{	 
	Nodo<T> *x=radice, *y=NULL;
	
	while (x!=NULL) {
		y=x; 
		if (*key < *(x->getChiave())) x=x->getSinistro(); 
		else x=x->getDestro(); 
		}
	Nodo<T>* nuovo=new Nodo<T>(key);
	nuovo->setPadre(y); 
	nuovo->setDestro(NULL); 
	nuovo->setSinistro(NULL);
	if (y==NULL) {
		radice=nuovo; 
		nuovo->setDepth(0);
		}
	else if (*key < *(y->getChiave())) y->setSinistro(nuovo); 
	else y->setDestro(nuovo);
	size++;
	if (y!=NULL) 
		nuovo->setDepth((nuovo->getPadre()->getDepth())+1);
	return this; 
}


template <class T> void albero <T> :: postorderPrint () 
{
 	cout << endl; 
	postorder(radice,-1);
	cout << endl; 
		
}

template <class T> void albero <T> :: postorder (Nodo<T>* p, int level) {
	if (p!=NULL) {
 		postorder(p->getSinistro(),level); 
 		postorder(p->getDestro(),level);
 		if ((level==-1) || (p->getDepth()==level))
 			cout << *(p->getChiave()) << "\t";  
 	}
}

template <class T> int albero <T> :: search (T* p) {
	Nodo<T> *temp=radice; 
	
	while ((temp!=NULL) && (*(temp->getChiave())!=*p)) 
		if  (*(temp->getChiave()) >= *p) temp=temp->getSinistro(); 
		else temp=temp->getDestro();
	if (temp!=NULL) return 1;
	else return 0; 
}

template <class T> Nodo<T>* albero <T> :: searchInt (T p) {
	Nodo<T> *temp=radice; 
	
	while ((temp!=NULL) && (*(temp->getChiave())!=p)) 
		if  (*(temp->getChiave()) >= p) temp=temp->getSinistro(); 
		else temp=temp->getDestro();
	return temp; 
}

template <class T> Nodo<T>* albero <T> :: searchPointer (T* p) {
	Nodo<T> *temp=radice; 
	
	while ((temp!=NULL) && (*(temp->getChiave())!=*p)) 
		if  (*(temp->getChiave()) >= *p) temp=temp->getSinistro(); 
		else temp=temp->getDestro();
	return temp; 
}

template <class T> void albero <T>:: Trapianta(Nodo<T>* u, Nodo<T>* v)	{
	if (u->getPadre()==NULL) radice=v; 			
	else if (u==u->getPadre()->getSinistro()) 			
       u->getPadre()->setSinistro(v); 
	else 
		u->getPadre()->setDestro(v);
	if (v!=NULL) 						
 		v->setPadre(u->getPadre()); 
}

template <class T> Nodo<T>* albero <T> ::Minimo(Nodo<T>* x)	{
	Nodo<T>* min=x; 
	
	while(min->getSinistro() != NULL) min=min->getSinistro(); 
	return min; 
}
	

template <class T> BST<T>* albero <T>:: del (T* p) {
	Nodo<T>* y; 
		
	Nodo<T>* z=searchPointer(p); 
	if (z->getSinistro()==NULL) Trapianta(z, z->getDestro()); 
	else if (z->getDestro()==NULL)
		Trapianta(z, z->getSinistro());
	else {
		y=Minimo(z->getDestro()); 
		if (y->getPadre()!=z)	{
			Trapianta(y,y->getDestro()); 
			y->setDestro(z->getDestro()); 
			y->getDestro()->setPadre(y);
			}
		Trapianta(z,y); 
		y->setSinistro(z->getSinistro()); 
		y->getSinistro()->setPadre(y); 	
	}
	delete z;
	size--;
	return this;
}

template <class T> void albero <T>::printLevel(int l)	{
	cout << endl; 
	postorder(radice,l);
	cout << endl; 		
}

template <class T> Nodo<T>* albero <T>:: successore(Nodo<T>* x)	{
	if (x==NULL) return NULL; 
	if (x->getDestro()!=NULL) return Minimo(x->getDestro()); 
	Nodo<T>* y=x->getPadre(); 
	while ((y!=NULL) && (*(y->getChiave()) < *(x->getChiave())) )
		y=y->getPadre();
	return y; 
}

template <class T> void albero <T> ::naturalFill(T* v)
{	Nodo<T>* current=Minimo(radice); 
	Nodo<T>* temp; 
	
	for (int i=0; i<size; i++) {
		if (current!=NULL) 
			current->setChiave(v+i);
		current=successore(current);
		}
}

int main()
{	
	albero <int> Tree; 
	int vettore[]={1,2,3,4,5,6,7,8,9,10,11,12,13};
	int input[]={23,4,6,8,12,21,5,9,7,3,16,2,24};

	for(int i=0; i<13; i++)
		Tree.insert(input+i);	
	Tree.postorderPrint(); 
	Tree.printLevel(3); 
	Nodo<int>* elemento=Tree.searchInt(21);
	if (elemento!=NULL) 
		Tree.del(elemento->getChiave()); 
	Tree.postorderPrint(); 	
	Tree.naturalFill(vettore); 
	
	Tree.postorderPrint();
	Tree.printLevel(3);
	
	return 0;	
}