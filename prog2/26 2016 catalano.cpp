#include <iostream>
#include<algorithm>

using namespace std;

template <class T>
class vBST {
public:
virtual vBST<T>* insert(T *x) = 0;
virtual vBST<T>* del(T *x) = 0;
virtual int search(T *x) = 0;
virtual void naturalFill(T* v) = 0;
virtual void postorderPrint() = 0;
virtual void printLevel(int l) = 0;
};

template<class T>
class Node{
    Node<T>* prec,*des,*sini;
    T* elem;
    int depth;
    public:
    Node(T el):elem(el),prec(NULL),des(NULL),sini(NULL),depth(0){}
    int getDepth() {return depth;} 
	void setDepth(int p) {depth=p;} 
    Node<T>* get_prec(){return prec;}
    Node<T>* get_des(){return des;}
    Node<T>* get_sin(){return sini;}
    T* get_el(){return elem;}
    void set_el(T* el){elem=el;}
    void set_prec(Node<T>* pr){prec=pr;}
    void set_des(Node<T>* pr){des=pr;}
    void set_sini(Node<T>* pr){sini=pr;}
};

template<class T>
class BST::public vBST<T>{
    private:
        Node<T>* root;
        int size;
        void transplant(Node<T>* u,Node<T>* v){
            if(!u->get_prec)root=v;
            else if(u->get_prec->get_des)u->get_prec->set_des(v);
            else u->get_prec->set_sini(v);
            if(v)v->set_prec(u->get_prec);

        }
        Node<T>* _min(Node<T>* x){
            while(x->get_sin){
                x=x->get_sin;
            }
            return x;
        }
        Node<T>* _max(Node<T>* x){
            while(x->get_des){
                x=x->get_des;
            }
            return x;
        }
        void inorder(Node<T>* p){
            if(p){
                inorder(p->get_sin);
                cout<<*p->get_el<<" ";
                inorder(p->get_des);
            }
        }
        void postorder(Node<T>* p){
            if(p){
                postorder(p->get_sin);
                postorder(p->get_des);
                cout<<*p->get_el<<" ";
            }
        }
    public:
        BST():root(NULL){}
        Node<T>* _search(T* el){
            Node<T>* x=root;
            while(x && *x->get_el!=*el){
                if(*x->get_el<*el)x=x->get_sin;
                else x=x->get_des;
            }
            return x;
        }    
        BST<T>* insert(T* el){
            Node<T>* x=root,*y=NULL;
            while(x){
                y=x;
                if(*x->get_el<*el)x=x->get_sin;
                else x=x->get_des;
            }
            x=new Node<T>(el);
            x->set_prec(y);
            if(!y)root=x;
            else if(*el<*y->get_el){y->set_sini(x);x->setDepth(y->getDepth+1);}
            else {y->set_des(x);x->setDepth(y->getDepth+1);}
            size++;
            return *this;
        }
        BST<T>* delet(T* el){
            elim=search(el);
            if(elim){
                if(!elim->get_des && !elim->get_sini){
                    
                    if(elim->get_prec){
                        if(elim->get_prec->get_des==elim)elim->get_prec->set_des(NULL);
                        else if(elim->get_prec->get_sini==elim)elim->get_prec->set_sini(NULL);
                    }
                    delete elim;
                }
                else if(!elim->get_des && elim->get_sini){
                    transplant(elim,elim->get_sini);
                    delete elim;
                }
                else if(elim->get_des && !elim->get_sini){
                    transplant(elim,elim->get_des);
                    delete elim;
                }
                else{
                    Node<T>* y=_min(elim);
                    if(y->get_prec!=elim){
                        transplant(y,y->get_des);
                        y->set_des(elim->get_des);
                        y->get_des->set_prec(y);
                    }
                    transplant(elim,y);
                    y->set_sini(elim->get_sini);
                    y->get_sini->set_prec(y);
                    delete elim;
                }
            }
            return *this;
        }
        void postorderPrint(){postorder(root);}
        int search(T* x){Node<T>* i=_search(x);
            if(i)return 1;
            else return 0;
        }
};