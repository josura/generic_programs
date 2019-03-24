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
        ~Node(){
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
	public:
		LList():head(0){}
		~LList(){
			Node<T>* iter=head;
			while(iter){
				iter=head->succ;
				delete head;
				head=iter;
			}
		}
		Node<T>* gethead(){return head;}
		void sethead(Node<T>* p){ head=p;}
		bool Vuota(){return !head;}
		LList<T>* insert(T el){
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
		LList<T>* canctesta(){
			if(!Vuota()){
				Node<T>* elim=head;
				head=head->succ;
				delete elim;
			}
			return this;
		}
		T* Peek(){
			return head;
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
			return this;
		}
		LList<T>* deletmezzo(Node<T>* prev){
			Node<T>* elim=prev->succ;
			prev->succ=elim->succ;
			delete elim;
			return this;
		}
		friend ostream& operator<<(ostream& str,LList<T>& dx){
    		Node<T>* iter=dx.head;
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
    			str<<*(iter->getPtrEl())<<" ";
    			iter=iter->succ;
			}
			str<<endl;
			return str;
		}
		
};

template<class T>
class BST{
	Node<T>* root;
	int height;
	int numel;
	void postorderel(Node<T>* p){
		//cout<<" sto per eliminare";
        if(p){
       		cout<<" sto eliminando "<<p->elem;
			postorderel(p->left);
			postorderel(p->right);
			delete p;
		}
		else return;
	}
	void destroy(Node<T>* p){
		if(p){
			destroy(p->left);
			p->left=NULL;
			destroy(p->right);
			p->right=NULL;
			delete p;
		}
	}
	Node<T>* _min(Node<T>* p){
		if(p){
			while(p->left){
				p=p->left;
			}
		}
		return p;
	}
	Node<T>* _max(Node<T>* p){
		if(p)
		while(p->right){
			p=p->right;
		}
		return p;
	}
	Node<T>* _succ(Node<T>* p){
		if(p){
			if(p->right)return _min(p->right);
			Node<T>* x=p->prec;
			while(x && p==x->right){
				p=x;
				x=x->prec;
			}
			return x;
		}
		return p;
	}
	Node<T>* _prec(Node<T>* p){
		if(p){
			if(p->left)return _max(p->left);
			Node<T>* x=p->prec;
			while(x && p==x->left){
				p=x;
				x=x->prec;
			}
			return x;
		}
		return p;
	}
	void transplant(Node<T>* x,Node<T>* y){
		if(!x->prec)root=y;
		else if(x->prec->right==x)x->prec->right=y;
		else if(x->prec->left==x)x->prec->left=y;
		if(y)y->prec=x->prec;
	}
	int altezza(Node<T>* p){
		if(!p)return -1;
		int sini=altezza(p->left),
			des=altezza(p->right);
		return (max(sini,des)+1);	
	}
	Node<T>* _search(T el){
		Node<T>* iter=root;
		while(iter && iter->elem!=el){
			if(iter->elem<el)iter=iter->right;
			else iter=iter->left;
		}
		return iter;
	}
	public:
		int getnumel(){return numel;}
		BST():root(NULL),height(0),numel(0){}
		/*~BST(){
			//postorderel(root);
			destroy(root);
		}*/
		BST<T>* ins(T el){
			if(!root){
				root=new Node<T>(el);
				numel++;
				return this ;
			}
			Node<T>* x=root,*y=NULL;
			while(x){
				y=x;
				if(el>x->elem){
					x=x->right;
				}
				else x=x->left;
			}
			x=new Node<T>(el);
			x->prec=y;
			if(!y)root=x;
			else if(y->elem<el)y->right=x;
			else y->left=x;
			numel++;
			height=altezza(root);
			return this ;
		}
		void remov(Node<T>* z){
			if(z){
                if(!z->left)transplant(z,z->right);
                else if(!z->right)transplant(z,z->left);
                else{
                    Node<T>* y=_min(z->right);
                    if(y!=z->right){
                        transplant(y,y->right);
                        y->right=z->right;
                        y->right->prec=y;
                    }
                    transplant(z,y);
                    y->left=z->left;
                    y->left->prec=y;
                }
                delete z;
                height=altezza(root);
            }
		}
		BST<T>* canc(T el){
			Node<T>* elim=_search(el);
			if(elim){
				remov(elim);
				numel--;
			}
			return this;
		}
		BST<T>* cancall(T el){
			Node<T>* iter=_search(el);
			while(iter){
				remov(iter);
				numel--;
				iter=_search(el);
			}
			return this;
		}
		void inorder(ostream& str,Node<T>* p)const{
            if(p){
                inorder(str,p->left);
                str<<p->elem<<" ";
                inorder(str,p->right);
            }
        }
        void inorder(ofstream& str,Node<T>* p)const{
            if(p){
                inorder(str,p->left);
                str<<p->elem<<" ";
                inorder(str,p->right);
            }
        }
        void preorder(ostream& str,Node<T>* p)const{
            if(p){
                
                str<<p->elem<<" ";
                preorder(str,p->left);
				preorder(str,p->right);
            }
        }
        void preorder(ofstream& str,Node<T>* p)const{
            if(p){
                str<<p->elem<<" ";
                preorder(str,p->left);
                preorder(str,p->right);
            }
        }
        void preinsert(Node<T>* p){
        	if(p){
    	    	this->ins(p->elem);
        		preinsert(p->left);
        		preinsert(p->right);
        	}
		}
        BST<T>& operator=(const BST<T>& dx){
        	preinsert(dx.root);
        	return *this;
		}
        friend ostream& operator<<(ostream& str,const BST<T>& dx){
    		dx.preorder(str,dx.root);
			str<<endl;
			return str;
		}
    	friend ofstream& operator<<(ofstream& str,const BST<T>& dx){
    		dx.preorder(str,dx.root);
			//str<<endl;
			return str;
		}
		friend bool operator>(const BST<T> &t1,const BST<T> &t2){
            if(t1.height()>t2.height())
                return true;
            if(t1.height()==t2.height() && *(t1.minimum()) > *(t2.minimum()))
                return true;
            return false;
        }
        friend bool operator<(const BST<T>&t1,const BST<T>&t2){
            return t2>t1;
        }
        friend bool operator==(const BST<T> &t1, const BST<T> &t2) {
            if(t1.height()==t2.height() && *(t1.minimum()) == *(t2.minimum()))
                return true;

            return false;
        }
};

template<class T>
class LOT:public LList<BST<T> >{
	int grado;
	public:
		LOT(int grad){grado=grad;}
		LOT<T>* ins(T el){
			if(this->head==NULL){
				BST<T> nuovo;
				nuovo.ins(el);
				this->head=new Node<BST<T> >(nuovo);
				return this;
			}
			if(this->head->elem.getnumel()==grado){
				BST<T> nuov;
				nuov.ins(el);
				Node<BST<T> >* nuovo=new Node<BST<T> >(nuov,this->head);
				this->head=nuovo;
				return this;
			}
			this->head->elem.ins(el);
			return this;
		}
		LOT<T>* canc(T el){
			Node<BST<T> >* iter=this->head,*prec=NULL;
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
				if(iter) iter=iter->succ;
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
    int maxalb;
    /*BST<int>* alberello=new BST<int>;
    alberello->ins(6)->ins(7)->ins(8)->ins(3)->ins(2)->ins(1);
    cout<<*alberello;
    //alberello->canc(2)->canc(7)->canc(8)->canc(1)->canc(3)->canc(10);
    cout<<*alberello;
    delete alberello;
    LList<int>* listarella=new LList<int>;
    listarella->insert(1)->insert(1)->insert(1)->insert(1)->insert(1)->insert(1);
    cout<<*listarella;
    listarella->delet(1)->delet(1)->delet(1)->delet(1)->delet(1);
    cout<<*listarella;*/
	while(!input.eof()){
        input>>tipo>>maxalb;
        cout<<tipo<<maxalb;
        operazione="";
        if(tipo=="int"){
            int aux;
            LOT<int> lot(maxalb);
            while(operazione!="#"){
                input>>operazione;
                //cout<<" "<<operazione;
                if(operazione=="ins"){
                    cout<<" sono all'interno";
                    input>>aux;
                    lot.ins(aux);
                }
                else if(operazione=="canc"){
                    input>>aux;
                    lot.canc(aux);
                }
                else if(operazione=="#"){cout<<"ciao";}
                cout<<" "<<aux;
            }
            output<<lot;
        }
        else if(tipo=="double"){
            double aux;
            LOT<double> lot(maxalb);
            while(operazione!="#"){
                input>>operazione;
                if(operazione=="ins"){
                    input>>aux;
                    lot.ins(aux);
                }
                else if(operazione=="canc"){
                    input>>aux;
                    lot.canc(aux);
                }
                else if(operazione=="#"){cout<<"ciao";}
            }
            output<<lot;
        }
        //output<<endl;
    }
    output.close();
    input.close();
	return 0;
}
