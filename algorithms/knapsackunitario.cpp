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
			Node<T>* nuovo=new Node<T>(el,head);
			head=nuovo;
			numel++;
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
class orddecreLList: public LList<T>{
    public:
        orddecreLList():LList<T>(){}
        orddecreLList<T>* insert(T el)override{
            if(!this->head){
                this->head=new Node<T>(el);
                this->numel++;
                return this;
            }
            if(el>=this->head->elem){
                Node<T>* nuovo=new Node<T>(el);
                nuovo->succ=this->head;
                this->head=nuovo;
                this->numel++;
                return this;
            }
            Node<T>* aux=this->head,*prev=NULL;
            while(aux && aux->elem>=el){
                prev=aux;
                aux=aux->succ;
            }
            Node<T>* nuovo=new Node<T>(el);
            if(prev){
				nuovo->succ=prev->succ;
            	prev->setsucc(nuovo);
        	}
			this->numel++;
            return this;
        }
        int sommanum(int nume){
			Node<T>* iter=this->head;
			int somma=0,counter=0;
    		while(iter && counter<nume){
    			somma+=iter->elem;
    			counter++;
    			iter=iter->succ;
			}
			return somma;
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
    int numel,pesotot;
    while(!input.eof()){
    	//cout<<"ciao ";
		input>>numel>>pesotot;
		orddecreLList<int> listavalori;
		int aux;
		for(int i=0;i < numel;i++){
			input>>aux;
			listavalori.insert(aux);
		}
		cout<<listavalori;
		aux=listavalori.sommanum(pesotot);
		output<<aux<<endl;
	}
    output.close();
    input.close();
    return 0;
}
