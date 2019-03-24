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
        short color;
        int level,blacklevel;
        Node(T el,int lev=-1,int blackl=-1,Node<T>* p=NULL):level(lev),blacklevel(blackl){
            right=left=prec=NULL;
            succ=p;
            color=1;
            elem=el;
        }
        void setRight(Node<T>* p){right=p;}
        void setLeft(Node<T>* p){left=p;}
        void setParent(Node<T>* p){prec=p;}
        void setColor(short t){color=t;}
        void setsucc(Node<T>* p){succ=p;}
        Node<T>* getRight(){return right;}
        Node<T>* getLeft(){return left;}
        Node<T>* getParent(){return prec;}
        short getColor(){return color;}
};

template<class T>
class BST{
    protected:
        Node<T>* root;
        string tipostampa;
        void postorderel(Node<T>* p){
        	if(p){
            	postorderel(p->left);
        	    postorderel(p->right);
            	delete p;
        	}
        }
        void resetlevel(Node<T>* p, int lev=-1){
        	if(p){
    	    	p->level=lev+1;
        		resetlevel(p->left,lev+1);
        		resetlevel(p->right,lev+1);
			}
		}
        void transplant(Node<T>* p,Node<T>* y){
            if(!p->prec){
				root=y;
			}
            else if(p->prec->right==p){
				p->prec->right=y;
			}
            else if(p->prec->left==p){
				p->prec->left=y;
			}
            if(y)y->prec=p->prec;
        }
        Node<T>* _min(Node<T>* p){
            while(p->left){
                p=p->left;
            }
            return p;
        }
        Node<T>* _max(Node<T>* p){
            while(p->right){
                p=p->right;
            }
            return p;
        }
        Node<T>* _search(T el){
            Node<T>* iter=root;
            while(iter && iter->elem!=el){
                if(el<iter->elem)iter=iter->left;
                else iter=iter->right;
            }
            return iter;
        }
        Node<T>* _succ(Node<T>* p){
        	if(!p)return NULL;
            if(p->right)return _min(p->right);
            Node<T>* iter=p->prec;
            while(iter && iter->right==p){
                p=iter;
                iter=iter->prec;
            }
            return iter;
        }
        Node<T>* _prec(Node<T>* p){
        	if(!p)return NULL;
            if(p->left)return _max(p->left);
            Node<T>* iter=p->prec;
            while(iter && iter->left==p){
            	p=iter;
                iter=iter->prec;
            }
            return iter;
        }
        int altezza(Node<T>* p){
            if(!p)return -1;
            int sini,des;
            sini=altezza(p->left);
            des=altezza(p->right);
            return (1+max(sini,des));
        }
    public:
        BST(string tip):root(NULL),tipostampa(tip){}
        void setstampa(string tip){tipostampa=tip;}
        string getstampa()const{return tipostampa;}
        Node<T>* getroot()const{return root;}
        bool Vuoto()const{return !root;}
        //~BST(){postorderel(root);}
        int getalt()const{return altezza(root)+1;}
        int getlevel(T el){
        	Node<T>* p=_search(el);
        	if(p)
        		return p->level;
        	else return -1;	
		}
		T getprec(T el){
			Node<T>* element=_search(el),*pre;
			if(element){
				pre=_prec(element);
				if(pre)return pre->elem;
			}
			return -1;
		}
		T getsucc(T el){
			Node<T>* element=_search(el),*suc;
			if(element){
				suc=_succ(element);
				if(suc)return suc->elem;
			}
			return -1;
		}
        virtual BST<T>* ins(T el){
            Node<T>* y=NULL,*x=root;
            if(!root){
                root=new Node<T>(el,0);
                return this;
            }
            while(x){
                y=x;
                if(el<x->elem)x=x->left;               //<=?
                else x=x->right;
            }
            x=new Node<T>(el);
            x->prec=y;
            x->level=y->level+1;
            if(!y)root=x;
            else if(el<y->elem)y->left=x;
            else y->right=x;
            return this;
        }
        virtual void remove(Node<T>* z){
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
                resetlevel(root);
                delete z;
            }
        }  
        virtual BST<T>* delet(T el){
            Node<T>* z=_search(el);
            remove(z);
            return this;
        }  
        T* search(T el)const{
            Node<T>* t=_search(el);
            if(t)
                return t->getPtrEl;
            else return NULL;
        }
        T* minimum()const{
            Node<T>* t=_min(root);
                if(t){
                    return t->getPtrEl;
                }
        }
        void inorder(Node<T>* p)const{
            if(p){
                inorder(p->left);
                cout<<p->elem<<" ";
                inorder(p->right);
            }
        }
        virtual void inorder(ofstream& str,Node<T>* p)const{
            if(p){
                inorder(str,p->left);
                string colore;
                if(p->color==1){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
                inorder(str,p->right);
            }
        }
        virtual void postorder(ofstream& str,Node<T>* p)const{
            if(p){
                postorder(str,p->left);
                postorder(str,p->right);
                string colore;
                if(p->color==1){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
            }
        }
        virtual void preorder(ofstream& str,Node<T>* p)const{
            if(p){
            	string colore;
                if(p->color==1){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
                preorder(str,p->left);
                preorder(str,p->right);
            }
        }
        BST<T>* cancall(T el){
            Node<T>* p;
            while(p=_search(el)){
                remove(p);
            }
            return this;
        }
        void natural_fill(T* arr,int size){
        	Node<T>* current=_min(root);
        	for(int i=0;i<size;i++){
        		if(current)
        			current->elem=arr[i];
        		current=_succ(current);	
			}
		}
        void stampa()const{
            inorder(root);
        }
        virtual void stampa(ofstream &str)const{
            inorder(str,root);
        }
        virtual void stampapre(ofstream &str)const{
            preorder(str,root);
        }
        virtual void stampapost(ofstream &str)const{
            postorder(str,root);
        }
        BST<T> *rightRotate(Node<T> *y) {
        	Node<T> *x=y->left;
        	if(!x)return this;                             //con nodi che sono foglie cazo
			y->left=x->right;
			if(x->right!=NULL)x->right->prec=y;
			x->prec=y->prec;
			if(y->prec==NULL)root=x;
			else if(y==y->prec->left)y->prec->left=x;
			else y->prec->right=x;
			x->right=y;
			y->prec=x;
			return this;
		}

		BST<T> *leftRotate(Node<T> *x) {
			Node<T> *y=x->right;
			if(!y)return this;
			x->right=y->left;
			if(y->left!=NULL)y->left->prec=x;
			y->prec=x->prec;
			if(x->prec==NULL)root=y;
			else if(x==x->prec->left)x->prec->left=y;
			else x->prec->right=y;
			y->left=x;
			x->prec=y;
			return this;
		}
		void ruotadx(T el){
			Node<T>* x=_search(el);
			if(x)rightRotate(x);
		}
		
		void ruotasx(T el){
			Node<T>* x=_search(el);
			if(x)leftRotate(x);
		}
		friend ostream& operator<<(ostream& stream, BST<T> dx){
			if(dx.getstampa()=="postorder"){
				dx.stampapost(stream);
			}
			else if(dx.getstampa()=="preorder"){
				dx.stampapre(stream);
			}
			else if(dx.getstampa()=="inorder"){
				dx.stampa(stream);
			}
			return stream;	
		}
		friend ofstream& operator<<(ofstream& stream, BST<T> dx){
			if(dx.getstampa()=="postorder"){
				dx.stampapost(stream);
			}
			else if(dx.getstampa()=="preorder"){
				dx.stampapre(stream);
			}
			else if(dx.getstampa()=="inorder"){
				dx.stampa(stream);
			}
			return stream;	
		}
};

template<class T>
class RB_BST{
	static const short int BLACK = 0;
	static const short int RED = 1;
	static const short int BLACKBLACK = 2;
	Node<T>* nullo;
	Node<T>* root;
    string tipostampa;
    void postorderel(Node<T>* p){
        	if(p!=nullo){
            	postorderel(p->left);
        	    postorderel(p->right);
            	delete p;
        	}
    }
    void transplant(Node<T>* p,Node<T>* y){
            if(p->prec==nullo){
				root=y;
			}
            else if(p->prec->right==p){
				p->prec->right=y;
			}
            else if(p->prec->left==p){
				p->prec->left=y;
			}
            y->prec=p->prec;
        }
        Node<T>* _min(Node<T>* p){
            while(p->left!=nullo){
                p=p->left;
            }
            return p;
        }
        Node<T>* _max(Node<T>* p){
            while(p->right!=nullo){
                p=p->right;
            }
            return p;
        }
        Node<T>* _search(T el){
            Node<T>* iter=root;
            while(iter!=nullo && iter->elem!=el){
                if(el<iter->elem)iter=iter->left;
                else iter=iter->right;
            }
            return iter;
        }
        Node<T>* _succ(Node<T>* p){
        	if(p==nullo)return nullo;
            if(p->right!=nullo)return _min(p->right);
            Node<T>* iter=p->prec;
            while(iter!=nullo && iter->right==p){
                p=iter;
                iter=iter->prec;
            }
            return iter;
        }
        Node<T>* _prec(Node<T>* p){
        	if(p==nullo)return NULL;
            if(p->left!=nullo)return _max(p->left);
            Node<T>* iter=p->prec;
            while(iter!=nullo && iter->left==p){
            	p=iter;
                iter=iter->prec;
            }
            return iter;
        }
        void inorder(ostream& str,Node<T>* p)const{
            if(p!=nullo){
                this->inorder(str,p->left);
                string colore;
                if(p->color==RED){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
                this->inorder(str,p->right);
            }
        }
        void postorder(ostream& str,Node<T>* p)const{
            if(p!=nullo){
                this->postorder(str,p->left);
                this->postorder(str,p->right);
                string colore;
                if(p->color==RED){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
            }
        }
        void preorder(ostream& str,Node<T>* p)const{
            if(p!=nullo){
            	string colore;
                if(p->color==RED){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
                this->preorder(str,p->left);
                this->preorder(str,p->right);
            }
        }
	void inorder(ofstream& str,Node<T>* p)const{
            if(p!=nullo){
                this->inorder(str,p->left);
                string colore;
                if(p->color==RED){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
                this->inorder(str,p->right);
            }
        }
        void postorder(ofstream& str,Node<T>* p)const{
            if(p!=nullo){
                this->postorder(str,p->left);
                this->postorder(str,p->right);
                string colore;
                if(p->color==RED){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
            }
        }
        void preorder(ofstream& str,Node<T>* p)const{
            if(p!=nullo){
            	string colore;
                if(p->color==RED){
                	colore="R";
				}
				else colore="B";
                str<<"("<<p->elem<<","<<colore<<") ";
                this->preorder(str,p->left);
                this->preorder(str,p->right);
            }
        }
        int altezza(Node<T>* p){
            if(p==nullo)return -1;
            int sini,des;
            sini=altezza(p->left);
            des=altezza(p->right);
            return (1+max(sini,des));
        }
	void RBInsertFixup(Node<T> *z) {
		Node<T>* y=nullo;
		while(z->prec->color==RED){
			//cout<<z->elem<<((z->color==RED)?'R':'B')<<" figlio di "<<z->prec->elem<<((z->prec->color==RED)?'R':'B');
			if(z->prec==z->prec->prec->left){
				//cout<<"entrato";
				y=z->prec->prec->right;
				if(y->color==RED){
					//cout<<"caso 1\n";
					z->prec->color=BLACK;
					y->color=BLACK;
					z->prec->prec->color=RED;
					z=z->prec->prec;

				}
				else{
				 	if(z==z->prec->right){
				 		//cout<<"caso 2 \n";
						z=z->prec;
						leftRotate(z);
					}
					//cout<<"caso 3\n";
					z->prec->color=BLACK;
					z->prec->prec->color=RED;
					rightRotate(z->prec->prec);
				}
			}
			else if(z->prec==z->prec->prec->right){
				//cout<<"entrato2";
				y=z->prec->prec->left;
				if(y->color==RED){
					//cout<<"caso 1 spec\n";
					z->prec->color=BLACK;
					y->color=BLACK;
					z->prec->prec->color=RED;
					z=z->prec->prec;
				}
				else{
				 	if(z==z->prec->left){
				 		//cout<<"caso 2 spec\n";
						z=z->prec;
						rightRotate(z);
					}
					//cout<<"caso 3 spec\n";
					z->prec->color=BLACK;
					z->prec->prec->color=RED;
					leftRotate(z->prec->prec);
				}
			}
		}
		root->color=BLACK;
	}
	public:
		RB_BST(string tip):root(nullo),tipostampa(tip){
			nullo=new Node<T>(0);
			nullo->color=BLACK;
			this->root=nullo;
		}
        void setstampa(string tip){tipostampa=tip;}
        string getstampa()const{return tipostampa;}
        Node<T>* getroot()const{return root;}
        bool Vuoto()const{return !root;}
        //~RB_BST(){postorderel(root);delete nullo;}
        int getalt(){return (altezza(this->root)+1);}
        int getlevel(T el){
        	Node<T>* p=_search(el);
        	if(p!=nullo)
        		return p->level;
        	else return -1;	
		}
		T getprec(T el){
			Node<T>* element=_search(el),*pre;
			if(element!=nullo){
				pre=_prec(element);
				if(pre!=nullo)return pre->elem;
			}
			return -1;
		}
		T getsucc(T el){
			Node<T>* element=_search(el),*suc;
			if(element!=nullo){
				suc=_succ(element);
				if(suc!=nullo)return suc->elem;
			}
			return -1;
		}
		RB_BST<T> *rightRotate(Node<T> *y) {
        	Node<T> *x=y->left;
        	//cout<<"ruotod "<<x->elem<<" con "<<y->elem;
        	if(x==nullo)return this;                             //con nodi che sono foglie cazo
			y->left=x->right;
			if(x->right!=nullo)x->right->prec=y;
			x->prec=y->prec;
			if(y->prec==nullo)root=x;
			else{
				if(y==y->prec->left)y->prec->left=x;
				else y->prec->right=x;
			}
			x->right=y;
			y->prec=x;
			return this;
		}

		RB_BST<T> *leftRotate(Node<T> *x) {
			Node<T> *y=x->right;
			//cout<<"ruotos "<<y->elem<<" con "<<x->elem;
			if(y==nullo)return this;
			x->right=y->left;
			if(y->left!=nullo)y->left->prec=x;
			
			y->prec=x->prec;
			if(x->prec==nullo)root=y;
			else {
				if(x==x->prec->left)x->prec->left=y;
				else x->prec->right=y;
			}
			y->left=x;
			x->prec=y;
			return this;
		}
		RB_BST<T>* ins(T el) {
            Node<T>* y=nullo,*x=root;
            //cout<<" elemento inserito "<<el;
            if(x==nullo){
            	//cout<<" ALBERO VUOTO ";
                root=new Node<T>(el,0);
                root->prec=root->right=root->left=nullo;
                root->color=BLACK;
                return this;
            }
            while(x!=nullo ){
                y=x;
                //cout<<" comparazione "<<el;
                if(el<x->elem){
					//cout<<" < "<<x->elem;
					x=x->left;
				}               
                else {
                	//cout<<" >= "<<x->elem;
					x=x->right;
				}
            }
            x=new Node<T>(el);
            x->prec=y;
            x->level=y->level+1;
            if(y==nullo)root=x;
            else {
				if(el<y->elem)y->left=x;
            	else y->right=x;
			}
            x->left=x->right=nullo;
            x->color=RED;
            RBInsertFixup(x);
            return this;
        }
		void stampa(ostream &str)const{
            this->inorder(str,root);
        }
        void stampapre(ostream &str)const{
            this->preorder(str,root);
        }
    	void stampapost(ostream &str)const{
            this->postorder(str,root);
        }	
        void stampa(ofstream &str)const{
            this->inorder(str,root);
        }
        void stampapre(ofstream &str)const{
            this->preorder(str,root);
        }
    	void stampapost(ofstream &str)const{
            this->postorder(str,root);
        }
        friend ostream& operator<<(ostream& stream, RB_BST<T> dx){
			if(dx.getstampa()=="postorder"){
				dx.stampapost(stream);
			}
			else if(dx.getstampa()=="preorder"){
				dx.stampapre(stream);
			}
			else if(dx.getstampa()=="inorder"){
				dx.stampa(stream);
			}
			return stream;	
		}
		friend ofstream& operator<<(ofstream& stream, RB_BST<T> dx){
			if(dx.getstampa()=="postorder"){
				dx.stampapost(stream);
			}
			else if(dx.getstampa()=="preorder"){
				dx.stampapre(stream);
			}
			else if(dx.getstampa()=="inorder"){
				dx.stampa(stream);
			}
			return stream;	
		}
};



int main()
{
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
    string tipo,operazione,bih;
    int numel;
    while(!input.eof()){
    	cout<<"ciao \n";
    	//cin>>tipo;
        input>>tipo;
		input>>numel;
		//input>>operazione;
        if(tipo=="int"){
            int elem;
			RB_BST<int> albero(operazione);
			for(int i=0; i<numel; i++){
				input >> elem;
				albero.ins(elem);
				//cout<<"inserisco "<<elem<<" ";
			}
			cout<<albero;
            output<<albero.getalt();
        }
        else if(tipo=="double"){
            double elem;
			RB_BST<double> albero(operazione);
			for(int i=0; i<numel; i++){
				input >> elem;
				albero.ins(elem);
			}
            output<<albero.getalt();
        }
        else if(tipo=="char"){
            char elem;
			RB_BST<char> albero(operazione);
			for(int i=0; i<numel; i++){
				input >> elem;
				albero.ins(elem);
			}
            output<<albero.getalt();
        }
        else if(tipo=="bool"){
            bool elem;
			RB_BST<bool> albero(operazione);
			for(int i=0; i<numel; i++){
				input >> elem;
				albero.ins(elem);
			}
            output<<albero.getalt();
        }
        output<<endl;
        //cin>>bih;
        //system("CLS");
    }
    output.close();
    input.close();
    return 0;
}
