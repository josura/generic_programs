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
        virtual void transplant(Node<T>* p,Node<T>* y){
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
        BST():root(NULL){}
        Node<T>* getroot(){return root;}
        bool Vuoto()const{return !root;}
        ~BST(){postorderel(root);}
        int getalt(){return altezza(root)+1;}
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
        void inorder(ofstream& str,Node<T>* p)const{
            if(p){
                inorder(str,p->left);
                str<<p->elem<<" ";
                inorder(str,p->right);
            }
        }
        void postorder(ofstream& str,Node<T>* p)const{
            if(p){
                postorder(str,p->left);
                postorder(str,p->right);
                str<<p->elem<<" ";
            }
        }
        void preorder(ofstream& str,Node<T>* p)const{
            if(p){
                str<<p->elem<<" ";
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
        void stampa(ofstream &str)const{
            inorder(str,root);
        }
        void stampapre(ofstream &str)const{
            preorder(str,root);
        }
        void stampa_post(ofstream &str)const{
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
			/*if(!y)return this;
			Node<T> *x = y->getLeft();
			Node<T> *z = y->getParent();
			if(y)
			y->setLeft(x->right);
			x->setRight(y);
			if(z!=NULL) {
				if(y==z->getLeft()) z->setLeft(x);
				else z->setRight(x);
			}
			else root = x;
			x->setParent(z);
			y->setParent(x);
			if(y->getLeft()) y->getLeft()->setParent(y);*/
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
			/*Node<T> *x = y->getRight();
			Node<T> *z = y->getParent();
			y->setRight(x->getLeft());
			x->setLeft(y);
			if(z!=NULL) {
				if(y==z->getRight()) z->setRight(x);
				else z->setLeft(x);
			}
			else root = x;
			x->setParent(z);
			y->setParent(x);
			if(y->getRight()) y->getRight()->setParent(y);*/
			return this;
		}
		void ruotadx(T el){
			//cout<<"hey";
			Node<T>* x=_search(el);
			//if(x)cout<<" ci sono "<<x->elem;
			if(x)rightRotate(x);
		}
		
		void ruotasx(T el){
			Node<T>* x=_search(el);
			//if(x)cout<<" ci sono "<<x->elem;
			if(x)leftRotate(x);
		}
};

template<class T>
class RB_BST:public BST<T>{
	static const short int BLACK = 0;
	static const short int RED = 1;
	static const short int BLACKBLACK = 2;
	void RBInsertFixup(Node<T> *z) {
			if(z->getParent()!=NULL && z->getParent()->getColor()==BLACK) return;
			if(z == this->getRoot()) {
				z->setColor(BLACK);
				return;
			}
			Node<T> *padre = z->getParent();
			Node<T> *nonno = padre->getParent();
			Node<T> *zio = nonno->getRight();
			if(padre == nonno->getRight()) zio = nonno->getLeft();
			if(zio!=NULL && zio->getColor() == RED) {
				// caso 1
				zio->setColor(BLACK);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				RBInsertFixup(nonno);
				return;
			}
			if(padre == nonno->getLeft()) {
				if(z == padre->getRight()) {
					// caso 3
					this->leftRotate(padre);
					padre = z;
					z = padre->getLeft();
				}
				// caso 2
				this->rightRotate(nonno);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				return;
			}
			else { // casi simmetrici ai precedenti
				if(z == padre->getLeft()) {
					// caso 3
					this->rightRotate(padre);
					padre = z;
					z = padre->getRight();
				}
				// caso 2
				padre->setColor(BLACK);
				nonno->setColor(RED);
				this->leftRotate(nonno);
				}
			}
	void swapColor(Node<T> *x, Node<T> *y){
			int tmp = x->getColor();
			x->setColor(y->getColor());
			y->setColor(tmp);
		}
	public:
		BST<T>* ins(T el) override{
            Node<T>* y=NULL,*x=this->getroot();
            if(!x){
                this->root=new Node<T>(el,0);
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
            x->color=RED;
            if(!y)this->root;
            else if(el<y->elem)y->left=x;
            else y->right=x;
            RBInsertFixup(x);
            return this;
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
    string tipo,tutto,operazione;
    int numel,numrot;
    while(!input.eof()){
    	cout<<"ciao ";
        input>>tipo;
		input>>numel>>numrot;
		input>>operazione;
        if(tipo=="int"){
            int elem;
			BST<int> albero;
			for(int i=0; i<numel; i++){
				input >> tutto;
				if(tutto[0]=='i'){
					elem=atoi((tutto.substr(4)).c_str());
					albero.ins(elem);
				}
				else if(tutto[0]=='c'){
					elem=atoi((tutto.substr(5)).c_str());
					albero.delet(elem);
				}
			}
			for(int i=0;i<numrot;i++){
				string rotazione;
				input>>rotazione;
				//cout<<rotazione<<' ';
				if(rotazione[0]=='r'){
					elem=atoi((rotazione.substr(6)).c_str());
					albero.ruotadx(elem);
				}
				else if(rotazione[0]=='l'){
					elem=atoi((rotazione.substr(5)).c_str());
					albero.ruotasx(elem);
				}
			}
            Node<int>* testa=albero.getroot();
			if(operazione=="postorder"){
				albero.postorder(output,testa);
			}
			else if(operazione=="preorder"){
				albero.preorder(output,testa);
			}
			else if(operazione=="inorder"){
				albero.inorder(output,testa);
			}
        }
        else if(tipo=="double"){
            double elem;
			BST<double> albero;
			for(int i=0; i<numel; i++){
				input >> tutto;
				if(tutto[0]=='i'){
					elem=atof((tutto.substr(4)).c_str());
					albero.ins(elem);
				}
				else if(tutto[0]=='c'){
					elem=atof((tutto.substr(5)).c_str());
					albero.delet(elem);
				}
			}
			for(int i=0;i<numrot;i++){
				string rotazione;
				input>>rotazione;
				if(rotazione[0]=='r'){
					elem=atof((rotazione.substr(6)).c_str());
					albero.ruotadx(elem);
				}
				else if(rotazione[0]=='l'){
					elem=atof((rotazione.substr(5)).c_str());
					albero.ruotasx(elem);
				}
			}
            Node<double>* testa=albero.getroot();
			if(operazione=="postorder"){
				albero.postorder(output,testa);
			}
			else if(operazione=="preorder"){
				albero.preorder(output,testa );
			}
			else if(operazione=="inorder"){
				albero.inorder(output,testa );
			}
        }
        else if(tipo=="char"){
            char elem;
			BST<char> albero;
			for(int i=0; i<numel; i++){
				input >> tutto;
				if(tutto[0]=='i'){
					elem=tutto[4];
					albero.ins(elem);
				}
				else if(tutto[0]=='c'){
					elem=tutto[5];
					albero.delet(elem);
				}
			}
			for(int i=0;i<numrot;i++){
				string rotazione;
				input>>rotazione;
				if(rotazione[1]=='r'){
					albero.ruotadx(rotazione[6]);
				}
				else if(rotazione[1]=='l'){
					albero.ruotasx(rotazione[5]);
				}
			}
            Node<char>* testa=albero.getroot();
			if(operazione=="postorder"){
				albero.postorder(output,testa);
			}
			else if(operazione=="preorder"){
				albero.preorder(output,testa);
			}
			else if(operazione=="inorder"){
				albero.inorder(output,testa);
			}
        }
        else if(tipo=="bool"){
            bool elem;
			BST<bool> albero;
			for(int i=0; i<numel; i++){
				input >> tutto;
				if(tutto[0]=='i'){
					elem=atoi((tutto.substr(4)).c_str());
					albero.ins(elem);
				}
				else if(tutto[0]=='c'){
					elem=atoi((tutto.substr(5)).c_str());
					albero.delet(elem);
				}
			}
			for(int i=0;i<numrot;i++){
				string rotazione;
				input>>rotazione;
				if(rotazione[1]=='r'){
					elem=atoi((rotazione.substr(6)).c_str());
					albero.ruotadx(elem);
				}
				else if(rotazione[1]=='l'){
					elem=bool(atoi((rotazione.substr(5)).c_str()));
					albero.ruotasx(elem);
				}
			}
            Node<bool>* testa=albero.getroot();
			if(operazione=="postorder"){
				albero.postorder(output,testa);
			}
			else if(operazione=="preorder"){
				albero.preorder(output,testa);
			}
			else if(operazione=="inorder"){
				albero.inorder(output,testa);
			}
        }
        output<<endl;
    }
    output.close();
    input.close();
    return 0;
}
