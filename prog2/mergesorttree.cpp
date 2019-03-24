#include<iostream>
#include<algorithm>
#include<fstream>

using namespace std;

template<class T>
class Node{
    public:
        T* in;
        int nin;
        T* out;
        int nout;
        Node<T>*prec,*left,*right;
        Node(T* _in=NULL,int _nin=0,T* _out=NULL,int _nout=0,Node<T>*_prec=NULL,Node<T>*_left=NULL,Node<T>*_right=NULL){
            in=_in;
            nin=_nin;
            out=_out;
            nout=_nout;
            prec=_prec;
            left=_left;
            right=_right;
        }
        ~Node(){delete in;delete out;}
        Node<T>* getParent() {return prec;}
        Node<T>* getLeft() {return left;}
        Node<T>* getRight() {return right;}

        T* getIn() {return in;}
        T* getOut() {return out;}

        int getNIn() {return nin;}
        int getNOut() {return nout;}

        //Metodi setter
        void setParent(Node<T>* p) {prec=p;}
        void setLeft(Node<T>* l) {left=l;}
        void setRight(Node<T>* r) {right=r;}

        void setIn(T* i, int n_in) {in=i; nin=n_in;}
        void setOut(T* o, int n_out) {out=o; nout=n_out;}
};

template<class T>
class mergeBST{
    Node<T>* root;
    int numel;
    void split(T* A, int na, T* &B, int &nb, T* &C, int &nc){
        //if(na>1){
            int center=na/2;
            nb=center;
            nc=na-center;
            B=new T[nb];
            //T* despacitodestrout=new T[center];
            C=new T[nc];
            //T* despacitosinistrout=new T[na-center];
            for(int i=0;i<nb;i++){
                B[i]=A[i];
            }
            for(int i=0;i<nc;i++){
                C[i]=A[center+i];
            }
           /* p->left=new Node<T>(despacitosinistro,center,despacitosinistrout,center);
            p->right=new Node<T>(despacitodestro,na-center,despacitodestrout,na-center);
            split(despacitodestro,center,p->right);
            split(despacitosinistro,na-center,p->left);*/
        //}
    }
    void merge(T* A, int na, T* B, int nb, T* &C, int &nc){

        nc=na+nb;
	    C=new T[nc];	
	    int ia=0,ib=0,ic=0;
	    while((ia<na) && (ib<nb)){
		    if(A[ia]<B[ib])
			    C[ic++]=A[ia++];
    		else
	    		C[ic++]=B[ib++];
	        }
	    if (ia<na){   
	    	while(ia<na)
		    	C[ic++]=A[ia++];
	    }
	    else{
		    while(ib<nb)
			    C[ic++]=B[ib++];
	    }
    }
    Node<T> * buildInputTree(T* A, int na){
        if(na>1){
		T *B, *C;
		int nb,  nc;
		split(A, na, B, nb, C, nc);
		Node<T>* left_subtree=buildInputTree(B,nb);
		Node<T>* right_subtree=buildInputTree(C,nc);
		Node<T> *r= new Node<T>(A,na,0,0,0,left_subtree,right_subtree);
		numel++;
		left_subtree->setParent(r);
		right_subtree->setParent(r);
		return r;	
	    }
	    else{
		    return new Node<T>(A,na);
	    }
    }
    void fillOutputs(Node<T> *r){
        if(r!=0){
	        if(r->getLeft() && r-> getRight()){
    			fillOutputs(r->getLeft());
	    		fillOutputs(r->getRight());	
    			T *A= r->getLeft()->getOut();
	    		int na=r->getLeft()->getNOut();			
    			T *B=r->getRight()->getOut();
	    		int nb=r->getRight()->getNOut();			
    			T* C;
	    		int nc;
		    	merge(A, na, B, nb, C, nc);
			    r->setOut(C,nc);
    		}
	    	else{
			    r->setOut(r->getIn(),r->getNIn());
	    	}
	    }
    }
    int _height(Node<T>* p){
        if(!p)return -1;
        int sini=_height(p->left);
        int des=_height(p->right);
        return (sini>des)?sini:des;
    }
    void postorderel(Node<T>* p){
    	if(p){
    		postorderel(p->left);
    		postorderel(p->right);
    		delete p;
		}
	}
	void preorder(ofstream& str,Node<T>* p)const{
		if(p){
			str<<"[ ";
			for(int i=0;i<p->nin;i++){
				str<<(p->in)[i]<<" ";
			}
			str<<": ";
			for(int i=0;i<p->nout;i++){
				str<<(p->out)[i]<<" ";
			}
			str<<"] ";
			preorder(str,p->left);
			preorder(str,p->right);
		}
	}
    public:
        mergeBST(T* arr,int na){
            root=buildInputTree(arr,na);
            fillOutputs(root);
        }
        /*~mergeBST(){
        	postorderel(root);
		}*/
		friend ofstream& operator<<(ofstream& str,const mergeBST<T>& dx){
    		dx.preorder(str,dx.root);
			//str<<endl;
			return str;
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
    string tipo;
    int size;
	while(!input.eof()){
        input>>tipo>>size;
        //cout<<tipo<<size;
        //operazione="";
        if(tipo=="int"){
            int *aux=new int[size];
            for(int i=0;i<size;i++){
            	input>>aux[i];
			}
            mergeBST<int> albero(aux,size);
            output<<albero;
        }
        else if(tipo=="double"){
            double *aux=new double[size];
            for(int i=0;i<size;i++){
            	input>>aux[i];
			}
            mergeBST<double> albero(aux,size);
            output<<albero;
        }
        else if(tipo=="char"){
            char *aux=new char[size];
            for(int i=0;i<size;i++){
            	input>>aux[i];
			}
            mergeBST<char> albero(aux,size);
            output<<albero;
        }
        else if(tipo=="bool"){
            bool *aux=new bool[size];
            for(int  i=0;i<size;i++){
            	input>>aux[i];
			}
            mergeBST<bool> albero(aux,size);
            output<<albero;
        }
        output<<endl;
    }
    output.close();
    input.close();
	return 0;
}
