#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

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
    		//str<<"numel"<<dx.numel<<" ";
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
    			//cout<<iter->elem<<" ";
    			str<<iter->elem<<" ";
    			iter=iter->succ;
			}
			//cout<<endl;
			//str<<endl;
			return str;
		}
		
};

template<class T>
class ordcreLList: public LList<T>{
    public:
        ordcreLList():LList<T>(){}
        ordcreLList<T>* insert(T el)override{
        	//cout<<" sta inserendo "<<el<<" nella lista ordinata";
            if(!this->head){
                this->head=new Node<T>(el);
                this->numel++;
                //cout<<" crea un nodo e lo mette in testa"<<el;
                //cout<<*this;
                return this;
            }
            if(el<this->head->elem){
                Node<T>* nuovo=new Node<T>(el);
                nuovo->succ=this->head;
                this->head=nuovo;
                this->numel++;
                //cout<<" crea un nodo e lo mette in testa con succ"<< el;
                //cout<<*this;
                return this;
            }
            //cout<<" deve mettere "<<el<<" da qualche parte";
            Node<T>* aux=this->head,*prev=NULL;
            while(aux && aux->elem<el){
                prev=aux;
                aux=aux->succ;
            }
            Node<T>* nuovo=new Node<T>(el);
            if(prev)nuovo->succ=prev->succ;
            prev->setsucc(nuovo);
            this->numel++;
            //cout<<" crea un nodo e lo mette da qualche parte\n";
            //cout<<*this;
            return this;
        }
};

template<class T>
class KBlist:public LList<ordcreLList<T> >{
	int grade;
	public:
		KBlist(int k):grade(k){LList<ordcreLList<T> >();}
		KBlist<T>* insert(T el){
			int h;
			//cout<<" sono dentro l'inserimento";
			if(this->head)
				h=LList< ordcreLList<T>>::head->elem.getnumel();	
			if(h==grade || !this->head)
			{
				//cout<<" sta creando una nuova lista";
				ordcreLList<T> aux;
				aux.insert(el);
				LList<ordcreLList<T> >::insert(aux);
				//this->numel++;
				//cout<<" ehi ci 6";
			}
			else
			{
				this->head->elem.insert(el);
			}
			//cout<<" ha finito di inserire l'elemento in KBlist";
			return this;
		}
		KBlist<T>* canc(T el){
			Node<ordcreLList<T> >* iter=this->head,*prec=NULL;
			while(iter){
				iter->elem.cancall(el);
				if(iter->elem.getnumel()==0){
					if(prec==NULL){
						this->head=iter->succ;
						delete iter;
						iter=this->head;
					}
					else{
						iter=prec;
						this->deletmezzo(prec);
					}
				}
				prec=iter;
				if(iter)iter=iter->succ;
			}
			return this;
		}
};

int main(){
	ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    if (input.fail())
	{
		cout<< "Apertura input.txt fallita!\n";
		exit(1);
	}
	if(output.fail())
	{
		cout << "Non sono riuscito a scrivere l'output.txt!'\n";
		exit(1);
	}
    cout<<"ciao ";
    string tipo,operazione;
    int maxgrade;
	while(!input.eof()){
        input>>tipo>>maxgrade;
        operazione="";
        if(tipo=="int"){
            int aux;
            KBlist<int> KB(maxgrade);
            while(operazione!="#"){
                input>>operazione;
                //cout<<" "<<operazione;
                if(operazione=="ins"){
                	//cout<<" inserisco";
                    input>>aux;
                    KB.insert(aux);
                }
                else if(operazione=="canc"){
                    input>>aux;
                    KB.canc(aux);
                }
                //else if(operazione=="#"){}
                //cout<<" "<<aux;
            }
            output<<KB;
        }
        else if(tipo=="double"){
            double aux;
            KBlist<double> KB(maxgrade);
            while(operazione!="#"){
                input>>operazione;
                if(operazione=="ins"){
                    input>>aux;
                    KB.insert(aux);
                }
                else if(operazione=="canc"){
                    input>>aux;
                    KB.canc(aux);
                }
                //else if(operazione=="#"){}
            }
            output<<KB;
        }
        output<<endl;
    }
    output.close();
    input.close();
	return 0;
}
