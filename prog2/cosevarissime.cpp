#include <iostream>
#include <math.h>
#include<algorithm>
using namespace std;

#define W 0
#define G 1
#define Bla 2
#define inf len+1

enum color{White,Grey,Black};



/*template<class T>
void quicksort(int *arr, int left, int right){
    int min = (left+right)/2;
    cout<<"QS:"<<left<<","<<right<<"\n";

    int i = left;
    int j = right;
    int pivot = arr[min];

    while(left<j || i<right)
    {
        while(arr[i]<pivot)
        i++;
        while(arr[j]>pivot)
        j--;

        if(i<=j){
            swap(i,j,arr);
            i++;
            j--;
        }
        else{
            if(left<j)
                quicksort(arr, left, j);
            if(i<right)
                quicksort(arr,i,right);
            return;
        }
    }
}


template<class T>
void Quicksort(T* ar,int sin, int des){
	if(sin>= des)return;
	int i=sin,j=des;
	T pivot=ar[(sin+(des-sin))/2];
	while(i<=j){
		while(ar[i]<pivot)i++;
		while(ar[j]>pivot)j++;
		if(i<=j){swap(ar[i],ar[j]);
			i++;j--;}
	}
	if(sin<j)Quicksort(ar,sin,j);
	if(i<des)Quicksort(ar,i,des);
}*/

template<class T>
void print(T* arr,int size){
	for(unsigned i=0;i<size;i++)cout<<arr[i]<<" ";
	cout<<endl;
}

template<class T>
int partition(T *arr, const int left, const int right) {
    const int mid = left + (right - left) / 2;
    const int pivot = arr[mid];
    // move the mid point value to the front.
    std::swap(arr[mid],arr[left]);
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while(i <= j && arr[i] <= pivot) {
            i++;
        }

        while(i <= j && arr[j] > pivot) {
            j--;
        }

        if (i < j) {
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i - 1],arr[left]);
    return i - 1;
}

template<class T>
void quicksort(T *arr, const int left, const int right, const int sz){

    if (left >= right) {
        return;
    }


    int part = partition(arr, left, right);
    std::cout << "QSC:" << left << "," << right << " part=" << part << "\n";
    print (arr, sz);

    quicksort(arr, left, part - 1, sz);
    quicksort(arr, part + 1, right, sz);
}

template<class T>
void quicksort(T* ar, int n){
	quicksort(ar,0,n-1,6);
}

template<class T>
void Merge(T* ar,const int left,const int center, const int right,const int sz){
	int i=left,j=center+1,k=0;
	T B[sz];
	while(i<=center && j<=right){
		if(ar[i]<=ar[j])B[k++]=ar[i++];
		else B[k++]=ar[j++];
	}
	for(;i<=center;i++,k++)B[k]=ar[i];
	for(;j<=right;j++,k++)B[k]=ar[j];
	for(int o=left;o<=right;o++)ar[o]=B[o-left];
}

template<class T>
void Mergesort(T* ar, const int left,const int right,const unsigned sz){
	if(left<right){
		int mid=(left+right)/2;
		Mergesort(ar,left,mid,sz);
		Mergesort(ar,mid+1,right,sz);
		Merge(ar,left,mid,right,sz);
	}
}

template <class T>
class Node {
	public:
	    T value;
		unsigned distance;
    	Node *father;
	    Node *left;
    	Node *right;
		color pergrafo;

	    Node(T val) {
    	    this->value = val;
			right=left=father=NULL;
			this->pergrafo=White;
			this->distance=unsigned(-1);
	    }

    	Node(unsigned distance,Node<T>* right=NULL, Node<T>* left=NULL,Node<T>* father=NULL,T val=0,color c=White) {
        	this->value = val;
	        this->left = left;
    	    this->right = right;
			this->father=father;
			this->pergrafo=c;
			this->distance=distance;
	    }
};

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
		void insert(Node<T>* precedente,T val){
			Node<T>* nuovo=new Node<T>;
			if(precedente->right==tail){
				tail=nuovo;
			}
			nuovo->value=val;
			nuovo->right=precedente->right; //senza seguente nuovo->succ=precedente->succ; Bisogna controllare se precedente è un puntatore a NULL, perché sennò non potrei fare l'assegnamento
			precedente->right=nuovo;
			numel++;
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
class Stack{
	unsigned numele;
	Node<T>* Top;
	public:
		Stack():numele(0),Top(NULL){}
		~Stack(){
				Node<T>* current=Top;
				while(current){
					Top=current->right;
					delete current;
					current=Top;
				}
		}
		bool empty()const{return !numele;}
		Stack<T>* Push(T x){
			Node<T>* novo=new Node<T>;
			novo->value=x;
			novo->right=Top;
			Top=novo;
			numele++;
			return this;
		}
		T Pop(){
			T ele;
			Node<T>* pnodo;
			if (Top) {
				ele=Top->value;
				pnodo=Top;
				Top=Top->right;
				delete pnodo;
				numele--;
			}
			else exit(0);
			return ele;
		}
		ostream& put (ostream& stream)const{
			Node<T>* iter=Top;
			if(Top){
				stream<<" ___"<<endl;
				while(iter!=NULL){
					stream << " |" << iter->value <<"|"<< endl;
					iter=iter->right;
				}
				stream<< " |___|" << endl;
			}
			else stream<<"empty stack";	
			stream << endl;
			return stream;
		}	
};

template<class T>
ostream& operator<<(ostream& stream,const Stack<T>& rhs){
	return rhs.put(stream);
}

template<class T>
class Deque{
	private:
		T* arr_deq;
		int head,tail;
		unsigned numel;
		unsigned MAX;
	public:
		Deque(unsigned dim):MAX(dim),numel(0),head(-1),tail(-1){arr_deq=new T[dim];}
		~Deque(){delete [] arr_deq;}
		Deque<T>* enqueue(T el);
		T dequeue();
		int Testa(){return head;}
		bool Full()const{return numel==MAX;}
		bool Empty()const{return numel==0;}
		ostream& put(ostream& stream)const;

};

template<class T>
Deque<T>* Deque<T>::enqueue(T el){
	if(Full())
		cerr<<"deque full"<<endl;
	else{
		tail=(tail+1)%MAX;
		arr_deq[tail]=el;
		if(head==-1)head++;
		numel++;
	}
	return this;
}

template<class T>
T Deque<T>::dequeue(){
	if(Empty()) cerr<<"coda vuota";
	else{
		T out=arr_deq[head];
		head=(head+1)%MAX;
		numel--;
		if(Empty()) head=tail=-1;
		return out;
	}
}

template<class T>
ostream& Deque<T>::put(ostream& stream)const{
	if(Empty())stream<<"coda vuota"<<endl;
	else for(unsigned i=0;i<numel;i++){
		stream<<"Posizione"<<i<<":  "<<arr_deq[(head+i)%MAX]<<" "<<endl;
	}
	stream<<endl;
	return stream;
}

template<class T>
ostream& operator<<(ostream& stream,const Deque<T>& rhs){
	return rhs.put(stream);
}

template <class T>
class BST {
	private:
		Node<T>* root;
		unsigned altezza;
		void transplant(Node<T>* ,Node<T>* );
		void inorder_iterative_con_pila();
		void inorder_recursive(Node<T>* p);
		void post_order_elimination(Node<T>* p);
		
		Node<T>* _min(Node<T>* x);
		Node<T>* _max(Node<T>* x);
	public:
		BST():root(NULL),altezza(0){}
		~BST(){
			post_order_elimination(root);
		}
		Node<T>* search(T el);
		BST<T>* insert(T el);
		BST<T>* delet(T el);
		Node<T>* successor(Node<T>* p);
		Node<T>* predecessor(Node<T>* p);
		unsigned height(Node<T>* p);
		T minimo();
		void stampa(){
			inorder_recursive(root);
		}
};

template<class T>
Node<T>* BST<T>::_min(Node<T>* x){
	if(x)
	while(x->left)
		x=x->left;
	return x;	
}

template<class T>
Node<T>* BST<T>::_max(Node<T>* x){
	if(x)
	while(x->right)
		x=x->right;
	return x;	
}

template<class T>
void BST<T>::post_order_elimination(Node<T>* p){
	if(p){
		post_order_elimination(p->left);
		post_order_elimination(p->right);
		delete p;
	}
}

template<class T>
Node<T>* BST<T>::search(T el){
	Node<T>* x=root;
	while(x && el!=x->value){
		if(x->value<=el)
			x=x->right;
		else 	x=x->left;
	}	
	return x;	
}

template<class T>
unsigned BST<T>::height(Node<T>* p){
	if(!p) return -1;
	int sin=height(p->left);
	int des=height(p->right);
	return (1+max(sin,des));
}

template<class T>
Node<T>* BST<T>::successor(Node<T>* p){
	if(p->right) return _min(p->right);
	else{
		Node<T>* y=p->father;
		while(y && y->right==p){
			p=y;
			y=y->father;
		}
		return y;
	}
}

template<class T>
Node<T>* BST<T>::predecessor(Node<T>* p){
	if(p->left) return _max(p->left);
	else{
		Node<T>* y=p->father;
		while(y && y->left==p){
			p=y;
			y=y->father;
		}
		return y;
	}
}

template<class T>
BST<T>* BST<T>::insert(T el){
	Node<T>* x=root,*y=NULL,*nuov=new Node<T>(el);
	while(x){
		y=x;
		if(x->value<=el)
			x=x->right;
		else 	x=x->left;
	}
	nuov->father=y;
	if(!y)
		root=nuov;
	else if(el<y->value) y->left=nuov;
	else y->right=nuov;
	altezza=height(root);	
	return this;	
}

template<class T>
void BST<T>::transplant(Node<T>* u,Node<T>* v){
	if(!u->father)root=v;
	else if(u==u->father->left) u->father->left=v;
	else u->father->right=v;
	if(v) v->father=u->father;
}

template<class T>
BST<T>* BST<T>::delet(T el){
	Node<T>* x=root,*y=NULL,*elim=search(el);
	if(elim){
	if(!elim->left)
		transplant(elim,elim->right);
	else if(!elim->right)
		transplant(elim,elim->left);
	else{
		y=search(_min(elim->right));
		if(y->father!=elim){
			transplant(y,y->right);
			y->right=elim->right;
			y->right->father=y;
		}
		transplant(elim,y);
		y->left=elim->left;
		y->left->father=y;
	}}		
	delete elim;
	altezza=height(root);	
	return this;	
}

template<class T>
void BST<T>::inorder_iterative_con_pila(){
	Stack<Node<T>*> stack;
	Node<T>* current=root;
	bool done=0;
	while(!done){
		if (current!=NULL) {
			stack.pushback(current);
			current=current->left;
		}
		else if(stack.empty())	done=true;
		else{
			current=stack.popback();
			cout << current->value << "\t";
			current=current->right;
		}
	}
}

template<class T>
void BST<T>::inorder_recursive(Node<T>* p){
	if(p!=NULL){
		inorder_recursive(p->left);
		cout<<p->value<<" ";
		inorder_recursive(p->right);
	}
}

template<class T>
T BST<T>::minimo(){
	return _min(root)->el;	
}

template<class T>
class Lgraph{
	private:
		unsigned len,numver,numarc; 
		int *distanze, *predecessore;
		T **K;
		SList<T>** adj;
		int _findindex(T el){
			for(unsigned i=0;i<numver;i++){
				if(*K[i]==el)return i;
			}
			return -1;
		}
	public:
		Lgraph(unsigned l){
			len=l;
			numarc=numver=0;
			K=new T*[len];
			distanze=new int[len];
			predecessore=new int[len];
			for(unsigned i=0;i<len;i++) K[i]=NULL;
			adj=new SList<T>*[len];
			for(unsigned i=0;i<len;i++) adj[i]=new SList<T>();
		}
		~Lgraph(){
			for(unsigned i=0; i<len;i++){
				delete K[i];
				delete adj[i];
			}
			delete [] K;
			delete [] adj;
			delete [] distanze;
			delete [] predecessore;
		}
		Lgraph<T>* addNode(T k){
			if(numver==len)return this;
			if(_findindex(k)>=0)return this;
			K[numver]=new T(k);
			numver++;
			return this;
		}
		Lgraph<T>* addEdge(T u,T v){
			int i=_findindex(u);
			int j=_findindex(v);
			if(i<0 || j<0) return this;
			if(!adj[i]->search(v)){
				adj[i]->pushback(v);
				numarc++;
			}
			return this;
		}
		/*void BFS(Node<T>* p){
			Deque<Node<T>*> coda(len);
			for(unsigned i =0;i<numver;i++){
				color[i]=W;
				predecessore[i]=NULL;
				distanze[i]=inf;
			}
			coda.enqueue(p);
			while(!coda.Empty){
				Node<T>* u=coda.dequeue();
				for(Node<T>* v=adj[u]->getHead; v<adj[u]->getTail; v=v->right) {
					if(v->pergrafo==White) {
						v->pergrafo=Grey;
						v->distance=u->distance+1;
						v->father=u;
						coda.enqueue(v);
					} 
				}
				u->pergrafo=Black;
			}

		}*/
		void print(){
				for(int i=0; i<numver; i++){
					cout << "(" << i << ", " << *K[i] << ")" << " : "<<*adj[i];
				}
			}
};

void sorttop(int *a, int n, int *k) {
			for(int i=1; i<n; i++) {
				int j = i-1;
				while(j>=0 && k[a[j+1]]>k[a[j]]) {
					swap(a[j+1],a[j]);
					j--;
				}
			}
		}

template<class T>
class Mgraph{
	protected:
		T** K;
		short ** M;
		int len,numver,numarc,tim,current_root;
		int* predecessore,*distance,*discovered,*finished,*roots,*coloDFS;
		int _findindex(T el){
			for(int i=0;i<numver;i++){
				if(*K[i]==el)return i;
			}
			return -1;
		}
	public:
		Mgraph(unsigned l){
			len=l;
			numarc=numver=0;
			K=new T*[len];
			M=new short*[len];
			distance=new int[len];
			predecessore=new int[len];
			discovered=new int[len];
			finished=new int[len];
			roots=new int[len];
			coloDFS=new int[len];
			for(int i=0;i<len;i++){
				M[i]=new short[len];
				K[i]=NULL;
				for(int j=0;j<len;j++){
					M[i][j]=0;
				}
			}
		}
		~Mgraph(){
			for(int i=0; i<len;i++){
				delete K[i];
				delete [] M[i];
			}
			delete [] K;
			delete [] M;
			delete [] distance;
			delete [] predecessore;
			delete [] discovered;
			delete [] finished;
			delete [] coloDFS;
		}
		Mgraph<T>* addNode(T el){
			if(numver==len) return this;
			if(_findindex(el)>=0) return this;
			K[numver]=new T(el);
			numver++;
			return this;
		}
		Mgraph<T>* addEdge(T el1,T el2){
			int i=_findindex(el1),j=_findindex(el2);
			if(i<0||j<0)return this;
			if(!M[i][j]){
				M[i][j]=1;
				numarc++;
			}
			return this;
		}
		void BFS(int p){
			int colo[len];
			Deque<int> coda(len);
			for(unsigned i=0;i<numver;i++){
				colo[i]=W;
				predecessore[i]=-1;
				distance[i]=inf;
			}
			colo[p]=G;
			//predecessore[p]=p;
			distance[p]=0;
			coda.enqueue(p);
			while(!coda.Empty()){
				int u=coda.dequeue();
				for(unsigned i=0;i<numver;i++){
					if(M[u][i]){
						if(colo[i]==W){
							colo[i]=G;
							coda.enqueue(i);
							distance[i]=distance[u]+1;
							predecessore[i]=u;
						}
					}
				}
				colo[u]=Bla;
			}
			for(int i=0; i<numver; i++) {
				cout << "[" << i << "]->";
				if(distance[i]==inf) cout << "inf." << endl;
				else cout << distance[i] << endl;
			}
			cout << endl;
		}
		int DFSvisit(int p){
			int cycle=0;
			discovered[p]=++tim;
			coloDFS[p]=G;
			roots[p]=current_root;
			for(int i=0;i<numver;i++)
				if(M[p][i]){
					if(coloDFS[i]==W){
						predecessore[i]=p;
						cycle|=DFSvisit(i);
					}
					if(coloDFS[i]==G) cycle=1;
				}
			coloDFS[p]=Bla;
			finished[p]=tim++;	
			return cycle;	
		}
		int DFS(){
			tim=0;
			int cycle=0;
			for(int i=0;i<numver;i++){
				coloDFS[i]=W;
				predecessore[i]=-1;
			}
			for(int i=0;i<numver;i++){
				if(coloDFS[i]==W){
					current_root=i;
					cycle |= DFSvisit(i);
				}
			}
			return cycle;
		}
		void topsort(){
			int cycle=DFS();
			if(cycle){
				cout<<"il grafo contiene un ciclo";
				return;
			}
			int *arr=new int[numver];
			for(int i=0;i<numver;i++)arr[i]=i;
			sorttop(arr,numver,finished);
			for(int i=0;i<numver;i++){
				cout<<"("<<arr[i]<<","<<finished[arr[i]]<<")";
			}
			cout<<endl;
			delete [] arr;

		}
		void print(){
			for(int i=0; i<numver; i++){
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0;j<numver;j++)
					if(M[i][j]) cout<<*K[j]<<" ";
				cout<<endl;	
				}
		}	
		void printPath(int x) {
			if(distance[x]==0){ cout << *K[x];return;}				//caso base se si calcola la distanza tra il nodo e se stesso
			if(predecessore[x]==-1) cout << "no path";    //caso no path
			else {									//print del predecessore dopo aver richiamato printpath in modo da avere il percorso dal nodo in cui si sta calcolando la distanza e quello in cui si è invocata printpath
				printPath(predecessore[x]);
				cout << "->" << *K[x]; 
			}
		}
		void printPath(T el1,T el2) {
				if(_findindex(el1)<0 || _findindex(el2)<0) {cout<<"elementi non trovati";return;}
				BFS(_findindex(el1));
				printPath(_findindex(el2));
		}
};

template<class T>
void insertionSortPointers(T** arr,int numver){
	T* numb;
	for(int i=1;i<numver;i++){
		int j=i-1;
		numb=arr[i];
		while (j>= 0 && *arr[j] > *numb){
           	arr[j+1]=arr[j];
           	j--;
       	}
       	arr[j+1]=numb;
	}
}

template<class T>
class MgraphSorted:public Mgraph<T>{
	public:
		MgraphSorted(unsigned numv):Mgraph<T>(numv){}
		MgraphSorted<T>* addNode(T el){
			Mgraph<T>::addNode(el);
			insertionSortPointers(this->K,this->numver);
			return this;
		}
};

int main() {
	MgraphSorted<char> *Gr = new MgraphSorted<char>(9);
	Gr->addNode('0')->addNode('2')->addNode('6')->addNode('3');
	Gr->addNode('4')->addNode('5')->addNode('1')->addNode('7');
	Gr->addNode('8');
	Gr->addEdge('0','8')->addEdge('0','1');
	Gr->addEdge('1','8');
	Gr->addEdge('2','4');
	Gr->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3');//->addEdge('4','0');
	//Gr->addEdge('5','6')->addEdge('5','3');
	Gr->addEdge('6','5');
	Gr->addEdge('8','2');
	Gr->print();
	//Gr->BFS(1);
	//Gr->printPath('1','1');
	Gr->topsort();
	return 0;
	/*Lgraph<char> *Gr = new Lgraph<char>(9);
	Gr->addNode('1')->addNode('2')->addNode('3')->addNode('4')->addNode('5')->addNode('6')->addNode('7')->addNode('8');
	Gr->addEdge('0', '8')->addEdge('0','1')->addEdge('1','8')->addEdge('2','4')->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3')->addEdge('4','0')->addEdge('5','6')->addEdge('5','3')->addEdge('6','5')->addEdge('8','2');
	Gr->print();*/
	/*int arr[6]={2,3,1,5,1,8};
	for(int i=0;i<6;i++){cout<<arr[i]<<" ";}
	cout<<endl;
	Mergesort(arr,0,5,6);
	for(int i=0;i<6;i++){cout<<arr[i]<<" ";}
	cout<<endl;*/
	/*BST<int> tree;
	tree.insert(26)->insert(15);
	tree.insert(37);
	tree.insert(2);
	tree.insert(48);
	tree.insert(19);
	tree.insert(16);
	tree.insert(17);
	tree.stampa();
	Node<int>* elem=tree.search(15);
	if(elem==NULL) cout << "Elemento non trovato!\n" << endl;
	else{
		cout << "Elemento da cancellare: " << elem->value << endl;
		tree.delet(15);
		tree.stampa();
	}*/
	return 0;
}
