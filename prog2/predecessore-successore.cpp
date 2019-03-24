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
        int level;
        Node(T el,int lev=-1,Node<T>* p=NULL):level(lev){
            right=left=prec=NULL;
            succ=p;
            elem=el;
        }
        void setsucc(Node<T>* p){succ=p;}
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
            if(p->right)return _min(p->right);
            Node<T>* iter=p->prec;
            while(iter && iter->right==p){
                p=iter;
                iter=iter->prec;
            }
            return iter;
        }
        Node<T>* _prec(Node<T>* p){
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
        BST<T>* ins(T el){
            Node<T>* y=NULL,*x=root;
            if(!root){
                root=new Node<T>(el,0);
                return this;
            }
            while(x){
                y=x;
                if(el<=x->elem)x=x->left;
                else x=x->right;
            }
            x=new Node<T>(el);
            x->prec=y;
            x->level=y->level+1;
            if(!y)root=x;
            else if(el<=y->elem)y->left=x;
            else y->right=x;
            return this;
        }
        void remove(Node<T>* z){
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
        BST<T>* delet(T el){
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
        void stampa()const{
            inorder(root);
        }
        void stampa(ofstream &str)const{
            inorder(str,root);
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
    string tipo,tutto;
    int numel,numchiavi;
    while(!input.eof()){
    	cout<<"ciao ";
        input>>tipo;
		input>>numel>>numchiavi;
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
			for(int i=0;i<numchiavi;i++){
				input >>elem;
				//output<<albero.getprec(elem)<<" ";
				output<<albero.getsucc(elem)<<" ";
			}output<<endl;
			//albero.stampa();
			//cout<<endl;
            
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
			for(int i=0;i<numchiavi;i++){
				input >>elem;
				//output<<albero.getprec(elem)<<" ";
				output<<albero.getsucc(elem)<<" ";
			}output<<endl;
        }
    }
    output.close();
    input.close();
    return 0;
}
