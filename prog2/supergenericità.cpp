#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>
#define W 0
#define G 1
#define Bla 2

using namespace std;

template<class T>
class Node{
    public:
        T elem;
        Node<T>* prec,*right,*left,*succ;
        Node(T el,Node<T>* suc=0){
            elem=el;
            succ=suc;
            prec=right=left=0;
        }
};

template <class T>
class LList{
    protected:
        Node<T>* head;
        Node<T>* _search(T el){
            Node<T>* iter=head;
            while(iter && iter->elem!=el){
                iter=iter->succ;
            }
            return iter;
        }
        Node<T>* _searchprec(T el){
            Node<T>* iter=head,*prec=0;
            while(iter && iter->elem!=el){
                prec=iter;
                iter=iter->succ;
            }
            if(!iter)return NULL;
            return prec;
        }
    public:
        Node<T>* gethead(){return head;}
        bool Vuoto(){return !head;}
        LList():head(0){}
        virtual void insert(T el){
            Node<T>* nuovo=new Node<T>(el,head);
            head=nuovo;
        }
        void cancellatesta(){
            Node<T>* elim=head;
            head=head->succ;
            delete elim;
        }
        void canc(T el){
            Node<T>* precelim=_searchprec(el);
            if(head->elem==el){cancellatesta();}
            else if(precelim){
                Node<T>* elim=precelim->succ;
                precelim->succ=elim->succ;
                delete elim;
            }
        }
        friend ostream& operator <<(ostream& str,const LList<T>& dx){
            Node<T>* iter=dx.head;
            while(iter){
                str<<iter->elem<<" ";
                iter=iter->succ;
            }
            str<<endl;
        }
};

template<class T>
class Deque{
    T* arr;
    int head,tail,numel,MAX;
    public:
    int gethead()const{return head;}
    int gettail()const{return tail;}
    int getnumel()const{return numel;}
    bool Vuoto()const{return !numel;}
    bool Pieno()const{return numel==MAX;}
    Deque(unsigned size){
        head=tail=numel=0;
        MAX=size;
        arr=new T[size];
    }
    ~Deque(){
        delete [] arr;
    }
    Deque<T>* enqueue(T el){
        if(Pieno())return this;
        arr[tail]=el;
        tail=(tail+1)%MAX;
        numel++;
        return this;
    }
    T dequeue(){
        if(Vuoto())exit(0);
        T out=arr[head];
        head=(head+1)%MAX;
        numel--;
        return out;
    }
    friend ostream& operator <<(ostream& str,const Deque<T>& dx){
            for(int i=0;i<dx.getnumel();i++){
                str<<dx.arr[(i+dx.head)%dx.MAX]<<" ";
            }
            str<<endl;
            return str;
        }
};

template<class T>
class Stack{
    Node<T>* top;
    public:
        bool Vuoto(){return !top;}
        Node<T>* getop(){return top;}
        Stack():top(0){}
        ~Stack(){
            Node<T>* iter=top;
            while(iter){
                top=top->succ;
                delete iter;
                iter=top;
            }
        }
        void push(T el){
            Node<T>* nuovo=new Node<T>(el,top);
            top=nuovo;
        }
        T pop(){
            if(Vuoto())exit(0);
            T out=top->elem;
            Node<T>* elim=top;
            top=top->succ;
            delete elim;
            return out;
        }
        friend ostream& operator <<(ostream& str,const Stack<T>& dx){
            Node<T>* iter=dx.top;
            while(iter){
                str<<iter->elem<<" ";
                iter=iter->succ;
            }
            str<<endl;
        }
};

template<class T>
class ordCreList: public LList<T>{
    public:
    void push(T el){
        if(!this->head){
            this->head=new Node<T>(el);
        }
        else if(el<=this->head->elem){
            Node<T>* nuovo=new Node<T>(el,this->head);
            this->head=nuovo;
        }
        else{
            Node<T>* prec=0,*iter=this->head;
            while(iter && el>iter->elem){
                prec=iter;
                iter=iter->succ;
            }
            Node<T>* nuovo=new Node<T>(el,prec->succ);
            prec->succ=nuovo;
        }
    }
};

template<class T>
class BST{
    Node<T>* root;
    int height;
    Node<T>* _min(Node<T>* p){
        while(p && p->left){
            p=p->left;
        }
        return p;
    }
    Node<T>* _max(Node<T>* p){
        while(p && p->right){
            p=p->right;
        }
        return p;
    }
    Node<T>* _succ(Node<T>* p){
        if(p && p->right){
            return _min(p->right);
        }
        Node<T>* y=p->prec;
        while(y && y->right=p){
            p=y;
            y=y->prec;
        }
        return y;
    }
    Node<T>* _prec(Node<T>* p){
        if(p && p->left){
            return _min(p->left);
        }
        Node<T>* y=p->prec;
        while(y && y->left=p){
            p=y;
            y=y->prec;
        }
        return y;
    }
    Node<T>* _search(T el){
        Node<T>* iter=root;
        while(iter && iter->elem!=el){
            if(el>iter->elem)iter=iter->right;
            else iter=iter->left;
        }
    }
    void transplant(Node<T>*z,Node<T>*y){
        if(!z->prec)root=y;
        else if(z->prec->right==z)z->prec->right=y;
        else if(z->prec->left==z)z->prec->left=y;
        if(y)y->prec=z->prec;
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
        friend ofstream& operator<<(ofstream& str,const BST<T>& dx){
            dx.stampa(str);
            return str;
        }
};

void sorttop(int *arr,int numver,int *f){
    int j;
    for(unsigned i=1;i<numver;i++){
        j=i-1;
        while(j>=0 && f[arr[j+1]]>f[arr[j]]){
            swap(arr[j],arr[j+1]);
            j--;
        }
    }
}

template<class  T>
class Mgraph{
    int numver,numarc,tim,maxver,current_root;
    int* color,*predec,*distance,*roots,*discovered,*finished;
    T** K;
    short** M;
    int _findvertex(T el){
        for(unsigned i=0;i<numver;i++){
            if(*K[i]==el)return i;
        }
        return -1;
    }
    public:
        Mgraph(max){
            K=new T*[max];
            maxver=max;
            numarc=numver=0;
            M=new short*[max];
            for(unsigned i=0;i<max;i++){
                M[i]=new short[max];
            }
            color=new int[max];
            distance=new int[max];
            predecessore=new int[max];
            roots=new int[max];
            discovered=new int[max];
            finished=new int[max];
        }
        bool Piena(){return numver==maxver;}
        void Addnode(T el){
            if(Piena())return;
            if(_findvertex(el)>=0)return;
            K[numver]=new T(el);
            numver++;
        }
        void Addedge(T el1,T el2){
            int i=_findvertex(el1);
            int j=_findvertex(el2);
            if(i<0 || j<0)return;
            if(!M[i][j]){
                M[i][j]=1;
                numarc++;
            }
            return;
        }
        void BFS(int p){
            for(unsigned i=0;i<numver;i++){
                color[i]=W;
                distance[i]=W;
                predec[i]=-1;
            }
            Deque<int> coda(numver);
            color[p]=G;
            coda.enqueue(p);
            distance[p]=0;
            while(!coda.Vuoto()){
                int u=coda.dequeue();
                for(unsigned i=0;i<numver;i++){
                    if(M[u][i])
                        if(color[i]==W){
                            predec[i]=u;
                            color[i]=G;
                            coda.enqueue(i);
                        }
                }
                color[u]=Bla;
            }

        }
        void printpath(int v){
            if(distance[v]==0)cout<<*K[v];return;
            if(predec[v]==-1)cout<<" non esiste path";
            else{
                printpath(predec[v]);
                cout<<"->"<<*K[v];
            }
        }
        void printpath(T el1,T 1l2){
            if(_findvertex(el1)<0||_findvertex(el2)<0)return;
            BFS(_findvertex(el1));
            printpath(_findvertex(el2));
        }
        int DFSvisit(int p){
            int cycle=0;
            discovered[p]=++tim;
            color[p]=G;
            for(unsigned i=0;i<numver;i++){
                if(M[p][i]){
                    if(color[i]==W){
                        roots[i]=p;
                        cycle|=DFSvisit(i);
                    }
                    if(color[i]==G) cycle=1;
                }
            }
            color[p]=Bla;
            finished[p]=tim++;
            return cycle;
        }
        int DFS(){
            for(unsigned i=0;i<numver;i++){
                color[i]=W;
                predec[i]=-1
            }
            tim=0;
            int cycle=0;
            for(unsigned i=0;i<numver;i++){
                if(color[i]==W){
                    current_root=i;
                    cycle|=DFSvisit(i);
                }
            }
            return cycle;

        }
        void topsort(){
            int cycle=DFS();
            if(cycle)return;
            int arr[numver];
            for(unsigned i=0;i<numver;i++){
                arr[i]=i;
            }
            sorttop(arr,numver,finished);
            for(unsigned i=0;i<numver;i++){
                cout<<arr[i]<<" ";
            }
        }
        friend ostream& operator<<(ostream& str,const Mgraph& dx)
};

int main(){
    ordCreList<int> ordina;
    ordina.push(3);ordina.push(2);ordina.push(4);ordina.push(8);
    cout<<ordina;
    ordina.canc(4);
    cout<<ordina;
    return 0;
}

