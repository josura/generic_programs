#include<iostream>

using namespace std;

template <class H>
class Element 
{
    private:
        Element<H> *next;
        H key;
    public:
        Element(H k, Element<H>* n=0) : key(k), next(n) {}

        void setKey(H k) {key=k;}
        H getKey() {return key;}

        Element<H>* getNext() {return next;}
        void setNext(Element<H>* n){next =n;}

        H* getPtrKey() {return &key;}
};

template<class T>
class Node{
    public:
        Node<T>* right,*left,*prec,*succ;
        T elem;
        Node(T el,Node<T>* p=NULL){
            right=left=prec=NULL;
            succ=p;
            elem=el;
        }
        void setsucc(Node<T>* p){succ=p;}
        T* getPtrEl(){return &elem;}
};

/*class NodeLOT:public Node<BST<T> >{
	NodeLOT(T el,Node<T>* p=NULL){
            right=left=prec=NULL;
            succ=p;
            elem=el;
        }
};*/

template<class T>
class LListgiorgio{
	protected:
		Node<T> *head;
		Node<T>* _searchprec(T el){
			Node<T>* prec=head,*iter;
			while(iter && iter->elem!=el){
				prec=iter;
				iter=iter->succ;
			}
			if(!iter)return NULL;
			if(prec)return prec;
			return NULL;
		}
	public:
		LListgiorgio():head(0){}
		~LListgiorgio(){
			Node<T>* iter;
			while(iter){
				iter=head->succ;
				delete head;
				head=iter;
			}
		}
		Node<T>* gethead(){return head;}
		void sethead(Node<T>* p){ head=p;}
		bool Vuota(){return !head;}
		LListgiorgio<T>* insert(T el){
			if(!head){
				head=new Node<T>(el);
				return this;
			}
			Node<T>* nuovo=new Node<T>(el);
			cout<<nuovo->elem;
			nuovo->succ=head;
			head=nuovo;
			return this;
		}
		LListgiorgio<T>* canctesta(){
			if(!Vuota()){
				Node<T>* elim=head;
				head=head->succ;
				delete elim;
			}
			return this;
		}
		T* Peek(){
			if(head)
			return head->getPtrEl();
		}
		LListgiorgio<T>* delet(T el){
			Node<T>* prec=_searchprec(el),*elim;
			if(head->elem==el){
				canctesta();
				return this;
			}
			if(!prec){
				return this;
			}
			elim=prec->succ;
			prec=elim->succ;
			delete elim;
			return this;
		}
		friend ostream& operator<<(ostream& str,LListgiorgio<T>& dx){
    		Node<T>* iter=dx.head;
    		while(iter){
    			str<<iter->elem<<" ";
    			iter=iter->succ;
			}
			str<<endl;
			return str;
		}
		
};

template <class H>
class LListtutor {
    protected:
        Element<H>* head;
        Element<H>* _search(H x);
        void _removeHead();
        void _removeElement(Element<H> *el);
    public:
        LListtutor() : head(0) {}
        LListtutor<H>* insert(H x);
        LListtutor<H>* canc(H x);
        H* search(H x);
        void print();

        H minimum() const {if(head) return head->getKey(); else return -1;}
        int size() const;
        H sum() const;

        friend ostream& operator<<(ostream &str, const LListtutor<H> &l) {
            Element<H> *el = l.head;
            while (el!=0) {
                str << el->getKey() << " ";
                el = el->getNext();
            }

            return str;
        }
};

template<class H>
void LListtutor<H>::_removeHead() {
    if(head!=0) 
   {
        Element<H>* next = head->getNext();
        delete head;
        head=next;
    }
}

template<class H>
void LListtutor<H>::print() {
    Element<H>* aux=head;
    while(aux!=0) {
        
        cout << *(aux->getPtrKey()) << " ";
        aux=aux->getNext();
    }
    cout << endl;
}

template<class H>
H* LListtutor<H>::search(H x) {
    Element<H> *aux = _search(x);

    if(aux==0)
        return 0;

    return aux->getPtrKey();
}

template<class H>
Element<H>* LListtutor<H>::_search(H x) {
    if(head==0)
        return 0;

    Element<H> *aux=head;

    while(aux!=0 && aux->getKey()<x)
        aux=aux->getNext();
    
    if(aux==0 || aux->getKey()!=x)
        return 0;

    return aux;
}



template<class H>
void LListtutor<H>::_removeElement(Element<H> *node) {
    if(head==0)
        return ;

    if(node==0)
        return ;

    if(node==head) {
        head=node->getNext();
        delete node;
        return ;
    }

    Element<H> *pred = head;

    while(pred->getNext()!=node)
        pred=pred->getNext();

    pred->setNext(node->getNext());
    delete node;
}

template<class H>
LListtutor<H>* LListtutor<H>::canc(H x) {
    if(head==0)
        return this;

    Element<H> *node=_search(x);

    if(node==0)
        return this;

    if(node==head) {
        head=node->getNext();
        delete node;
        return this;
    }


    Element<H> *pred = head;

    while(pred->getNext()!=node)
        pred=pred->getNext();

    pred->setNext(node->getNext());
    delete node;

    return this;
}

template<class H>
LListtutor<H>* LListtutor<H>::insert(H x) {
    if(head==0){
        head=new Element<H>(x);
        return this;
    }

    if(x<head->getKey()) {
        head=new Element<H>(x,head);
        return this;
    }


    Element<H>* aux=head;
    Element<H>* prev;

    while(aux!=0 && aux->getKey()<x){
        prev=aux;
        aux=aux->getNext();
    }

    Element<H>* node = new Element<H>(x,aux);
    prev->setNext(node);

    return this;
}

template<class H>
int LListtutor<H>::size() const {
    Element<H>* aux=head;

    int size=0;
    while(aux!=0){
        size++;
        aux=aux->getNext();
    }

    return size;
}

template<class H>
H LListtutor<H>::sum() const {
    Element<H>* aux=head;

    H sum=0;

    while(aux!=0){
        sum+=aux->getKey();
        aux=aux->getNext();
    }

    return sum;
}

template<class T>
class SList{
	private:
		Node<T>* head,*tail;
		unsigned numel;
	public:
		SList():head(NULL),tail(NULL),numel(0){}
		~SList(){
			Node<T>* current=head,* temp;
			while(current!=NULL){
				temp=current->right;
				delete current;
				current=temp;
			}
		}
		Node<T>* getHead() const{return head;}
		Node<T>* getTail() const{return tail;}
		bool empty(){return !numel;}
		SList<T>* pushback(T elem){
			Node<T>* novo=new Node<T>(elem);
			novo->right=head;
			head=novo;
			if(empty()){
				tail=novo;
			}
			numel++;
			return this;
		}
		/*template <class T> void Lista <T>:: insert(T val){
			Nodo<T>* nuovo=new Nodo<T>;
			nuovo->valore=val;
			nuovo->succ=testa;
			testa=nuovo;
		}*/
		T   popback(){
			if(head){
				T ele=head->value;
				Node<T>* next=head->right;
				delete head;
				head=next;
				numel--;
				if(empty())tail=NULL;
				return ele;
			}
			exit(0);
		}
		SList<T>* insert(Node<T>* precedente,T val){
			Node<T>* nuovo=new Node<T>;
			if(precedente->right==tail){
				tail=nuovo;
			}
			nuovo->value=val;
			nuovo->right=precedente->right; //senza seguente nuovo->succ=precedente->succ; Bisogna controllare se precedente è un puntatore a NULL, perché sennò non potrei fare l'assegnamento
			precedente->right=nuovo;
			numel++;
			return this;
		}	
		SList<T>* canc(){
			if(head){
				Node<T>* elim=head;
				head=head->succ;
				delete elim;
			}
			return this;
		}
		void list_delet(Node<T>* precedente){
			if(precedente ){
				Node<T>* elim=precedente->right;
				if(precedente->right==tail){
					tail=NULL;
				}
				precedente->right=elim->right;
				delete elim;
			}
			else {
				cout<<"elemento non in lista";
			}
		}
		Node<T>* search(T el){
			Node<T>* sear=head;
			while(sear && sear->value!=el){
				sear=sear->right;
			}
			return sear;
		}
		void list_delet(T el){
			list_delet(search(el));
		}
		ostream& put (ostream& stream)const{
			Node<T>* iter=head;
			while(iter!=NULL){
				stream << " " << iter->value;
				iter=iter->right;
			}
			stream << endl;
			return stream;
		}		
};

template<class T>
ostream& operator<<(ostream& stream,const SList<T>& rhs){
	return rhs.put(stream);
}

template<class T>
class LList{
	protected:
		Node<T> *head;
		int numel;
		Node<T>* _searchprec(T el){
			Node<T>* prec=NULL,*iter=head;
			while(iter && iter->elem!=el){
				prec=iter;
				iter=iter->succ;
			}
			if(!iter)return NULL;
			if(prec)return prec;
			return NULL;
		}
		Node<T>* _search(T el){
			Node<T> *iter=head;
			while(iter && iter->elem!=el){
				iter=iter->succ;
			}
			return iter;
		}
	public:
		LList():head(NULL),numel(0){}
		/*~LList(){
			Node<T>* iter=head;
			while(iter){
				iter=head->succ;
				delete head;
				head=iter;
			}
		}*/
		Node<T>* gethead(){return head;}
		int getnumel(){return numel;}
		void sethead(Node<T>* p){ head=p;}
		bool Vuota(){return !head;}
		virtual LList<T>* insert(T el){
			//cout<<" sta inserendo nella lista normale";
			Node<T>* nuovo=new Node<T>(el,head);
			head=nuovo;
			numel++;
			//cout<<" crea un nodo e lo mette in testa";
			return this;
		}
		LList<T>* canctesta(){
			if(!Vuota()){
				Node<T>* elim=head;
				head=head->succ;
				numel--;
				delete elim;
			}
			return this;
		}
		T* Peek(){
			return head->getPtrEl();
		}
		LList<T>* delet(T el){
			Node<T>* prec=_searchprec(el),*elim;
			if(head->elem==el){
				canctesta();
				return this;
			}
			if(!prec){
				return this;
			}
			elim=prec->succ;
			prec->succ=elim->succ;
			delete elim;
			numel--;
			return this;
		}
		LList<T>* cancall(T el){
			Node<T>*elim=_search(el);
			while(elim){
				this->delet(el);
				elim=_search(el);
			}
			return this;
		}
		LList<T>* deletmezzo(Node<T>* prev){
			Node<T>* elim=prev->succ;
			prev->succ=elim->succ;
			delete elim;
			numel--;
			return this;
		}
		friend ostream& operator<<(ostream& str,LList<T>& dx){
    		Node<T>* iter=dx.head;
    		str<<"numel"<<dx.numel<<" ";
    		while(iter){
    			str<<iter->elem<<" ";
    			iter=iter->succ;
			}
			str<<endl;
			return str;
		}
    	friend ofstream& operator<<(ofstream& str,LList<T>& dx){
    		Node<T>* iter=dx.head;
    		while(iter){
    			cout<<iter->elem<<" ";
    			str<<iter->elem<<" ";
    			iter=iter->succ;
			}
			cout<<endl;
			//str<<endl;
			return str;
		}
		
};

int main(){
	int pene;
    LList<int>* listarella=new LList<int>;
    listarella->insert(1)->insert(1)->insert(1)->insert(1)->insert(1)->insert(1);
    cout<<*listarella;
    listarella->delet(1)->delet(1)->delet(1)->delet(1)->delet(1);
    cout<<*listarella;
    cin>>pene;
	return 0;
}
