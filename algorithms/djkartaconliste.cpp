#include<fstream>
#include<cstdlib>
#include<iostream>
#include <string>
#include<algorithm>

#define inf INT_MAX-1
#define negcycle INT_MAX

using namespace std;

class Distanza{
	public:
		int dist;
		int index;
		bool operator<(Distanza &d){
			return (this->dist<d.dist);
		}
		bool operator>(Distanza &d){
			return (this->dist>d.dist);
		}
		Distanza(int ind=-1,int dis=inf):index(ind),dist(dis){}
};

template<class T>
class Node{
    public:
        Node<T>* right,*left,*prec,*succ;
        int weight;
        T elem;
        Node(T el,Node<T>* p=NULL){
            right=left=prec=NULL;
            succ=p;
            elem=el;
        }
        Node(T el,int w,Node<T>* p=NULL){
            right=left=prec=NULL;
            weight=w;
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
		~LList(){
			Node<T>* iter=head;
			while(iter){
				iter=head->succ;
				delete head;
				head=iter;
			}
		}
		Node<T>* gethead(){return head;}
		int getnumel(){return numel;}
		void sethead(Node<T>* p){ head=p;}
		bool Vuota(){return !head;}
		Node<T>* search(T el){
			return _search(el);
		}
		virtual LList<T>* insert(T el){
			Node<T>* nuovo=new Node<T>(el,head);
			head=nuovo;
			numel++;
			return this;
		}
		virtual LList<T>* insert(T el,int w){
			Node<T>* nuovo=new Node<T>(el,w,head);
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
    			str<<iter->elem<<" ";
    			iter=iter->succ;
			}
			return str;
		}
		
};

template<class T>
class MinBinaryHeap 
{ 
    T* harr;  
    int capacity;  
    int heap_size; 
    int parent(int i) {return  ( (i-1)>>1); } 
	int left(int i) { return ((i<<1) + 1); }   
	int right(int i) { return (((i<<1)|1 )+1); }
public:  
	bool Vuoto(){return !heap_size;}
	bool Pieno(){return heap_size==capacity;}
    MinBinaryHeap(int _cap):capacity(_cap),heap_size(0){
		harr=new T[_cap];    
	}
	MinBinaryHeap(T* arr,int _cap):capacity(_cap),heap_size(_cap){
		harr=new T[_cap];
		for(int i=0;i<_cap;i++)
			harr[i]=arr[i];
		BuildMinHeap();    
	}
    void MinHeapify(int i){
    	int l = left(i); 
    	int r = right(i); 
    	int min = i; 
    	if (l < heap_size && harr[l] < harr[i]) 
        	min = l; 
    	if (r < heap_size && harr[r] < harr[min]) 
        	min = r; 
    	if (min != i) 
    	{ 
        	swap(harr[i],harr[min]); 
        	MinHeapify(min); 
    	}		 
	} 
  	void BuildMinHeap(){
  		for(int i=capacity/2;i>=0;i--)
			MinHeapify(i);
	}
    
    T extractMin(){
    	if(!heap_size)exit(0);
    	T min=harr[0];
    	swap(harr[0],harr[heap_size-1]);
    	heap_size--;
    	if(heap_size)
    		MinHeapify(0);
    	return min;
	} 
  
    // Decreases key value of key at index i to new_val 
    void increaseKey(int i, T new_val){
    	harr[i]=new_val;
    	while(i>0 && harr[parent(i)]>harr[i]){
    		swap(harr[parent(i)],harr[i]);
    		i=parent(i);
		}
	}
  
    // Returns the minimum key (key at root) from min heap 
    int getMin() { return harr[0]; } 
  
    // Deletes a key stored at index i 
    void deleteKey(int i){
    	swap(harr[i],harr[heap_size-1]);
    	heap_size--;
    	MinHeapify(i);
	}
  
    // Inserts a new key 'k' 
    void enqueue(T k){
    	if (heap_size == capacity){ 
        	cout << "\nOverflow: Could not insertKey\n"; 
        	return; 
    	} 
    // First insert the new key at the end 
    	heap_size++; 
    	int i = heap_size - 1; 
    	harr[i] = k; 
    // Fix the min heap property if it is violated 
    	while (i != 0 && harr[parent(i)] < harr[i]){ 
       		swap(harr[i], harr[parent(i)]); 
       		i = parent(i); 
    	} 
	}
	friend ostream& operator<<(ostream& stream, MinBinaryHeap<T> dx){
		for(int i=0;i<dx.heap_size;i++)
			stream<<dx.harr[i]<<" ";
		stream<<endl;
		return stream;	
	}
	friend ofstream& operator<<(ofstream& stream, MinBinaryHeap<T> dx){
		for(int i=0;i<dx.heap_size;i++)
			stream<<dx.harr[i]<<" ";
		//stream<<endl;
		return stream;	
	}
	
	void heapsort(){
		for(int i=(capacity-1)/2;i>=0;i--)
			MinHeapify(harr,i,capacity);
		for(int i=capacity-1;i>=0;i--){
			swap(harr[i],harr[0]);
			MinHeapify(harr,0,i);
		}
	}
};

template <class T> class LGraph {
	private:
		int *c, *predecessori, *distance, *harr;
		int len, numver, numarc;
		int t;
		Distanza *d;
		T **K;
		LList<int> **Adj;
		int findIndex(T x) {
			for(int i=0; i<numver; i++)
				if(*K[i] == x) return i;
			return -1;
		}
		
		void Initialize_Single_Source(T sorgente){
    	for(int i=0; i<numver; i++){
    			distance[i]=inf;
    			predecessori[i]=-1;
			}
			distance[findIndex(sorgente)]=0;
		}
		void Initialize_Single_Source_dijkstra(int sorgente){
    	for(int i=0; i<numver; i++){
    		d[i].dist=inf;
    		d[i].index=i;
    		predecessori[i]=-1;
		}
		d[findIndex(sorgente)].dist=0;
		}
		void Relax(int u, int v,int w){
			if(distance[u]!=inf && distance[u]+w < distance[v]){
				distance[v]=distance[u]+w;
				predecessori[v]=u;
			}
		}
		void Relax(int u, int v,int w, MinBinaryHeap<Distanza>& Q){
		if(d[u].dist!=inf && d[u].dist+w < d[v].dist){
			d[v].dist=d[u].dist+w;
			predecessori[v]=u;
			Q.enqueue(d[v]);
		}
		}
		bool Relaxcycle(int u, int v,int w){
			if(distance[u]!=inf && distance[u]+w < distance[v]){
				return false;
			}
			return true;
		}
	
	public:
		LGraph(int len) {
			this->len = len;
			numver = numarc = 0;
			K = new T*[len];
			c = new int[len];
			predecessori = new int[len];
			distance = new int[len];
			d=new Distanza[len];
			for(int i=0; i<len; i++) K[i] = NULL;
			Adj = new LList<int>*[len];
			for(int i=0; i<len; i++) 
				Adj[i] = new LList<int>();
		}
		~LGraph() {
			delete [] K;
			delete [] c;
			delete [] predecessori;
			delete [] distance;
			delete [] harr;
			delete [] d;
			for(int i=0; i<len; i++) 
				delete Adj[i];
			delete [] Adj;	
		}

		LGraph<T>* addNode(T k) {
			if(numver==len) return this;
			if(findIndex(k)>=0) return this;
			K[numver] = new T(k);
			numver++;
			return this;
		}
		
		LGraph<T>* addEdge(T x, T y,int w) {
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!Adj[i]->search(j)) {
				Adj[i]->insert(j,w);
				numarc++;
			}
			return this;
		}
	int Bellman_Ford(T s, T dest){
		Initialize_Single_Source(s);
		for(int i=0; i<numver-1; i++){
			for(int j=0;j<numver;j++){
				Node<int>* iter=Adj[j]->gethead();
				while(iter){
					Relax(j,iter->elem,iter->weight);
					iter=iter->succ;
				}
			}
		}
		for(int i=0;i<numver;i++){
				Node<int>* iter=Adj[i]->gethead();
				while(iter){
					if(!Relaxcycle(i,iter->elem,iter->weight))return negcycle;
					iter=iter->succ;
				}
			}
			return distance[findIndex(dest)];
		}
		int Djkharta(T s,T dest){
			Initialize_Single_Source_dijkstra(s);
			MinBinaryHeap<Distanza> Q(numver);
			int dio=findIndex(s);
			Q.enqueue(d[dio]);
			cout<<findIndex(s);
			while(!Q.Vuoto()){
				Distanza u=Q.extractMin();
				for(int i=0; i<numver; i++){
					Node<int>* iter=Adj[u.index]->gethead();
					while(iter){
						Relax(u.index, iter->elem,iter->weight, Q);
						iter=iter->succ;
					}					
				}
			}
			return d[findIndex(dest)].dist;
		}
		void print(ostream& str) {
			for(int i=0; i<numver; i++) {
				str << "(" << i << ", " << *K[i] << ")" << " : ";
				//str<<*Adj[i];
				Node<int>* iter=Adj[i]->gethead();
				while(iter){
					str<<"("<<iter->elem<<","<<iter->weight<<") ";
					iter=iter->succ;
				}
				str << endl;
			}
		}	
		friend ostream& operator<<(ostream& str,LGraph<T>& dx){
			dx.print(str);
			return str;
		}	
		

};

int main(){
	ifstream read;
	ofstream write;
	read.open("input.txt");
	if (read.fail())
	{
		cout<< "Apertura input.txt fallita!\n";
		exit(1);
	}
	write.open("output.txt");
	if(write.fail())
	{
		cout << "Non sono riuscito a scrivere l'output.txt!'\n";
		exit(1);
	}
	int n, m;
	string tipodato;
	string nodo1, peso;
	while(!read.eof()){
		read >> n >> m;
		read >> tipodato;
		if(tipodato=="int"){
			int elem;
			int nodo2;
			int sorgente, destinazione;
			LGraph<int> grafo(n);
			for(int i=0; i<m; i++){
				read >> nodo1 >> nodo2 >> peso;
				grafo.addNode(atoi(nodo1.substr(1).c_str()));
				grafo.addNode(nodo2);
				grafo.addEdge(atoi(nodo1.substr(1).c_str()), nodo2, atoi((peso.substr(0, peso.length()-1)).c_str()));
			}
			read >> sorgente >> destinazione;
			int mindist=grafo.Djkharta(sorgente, destinazione);
			//int mindist=grafo.Bellman_Ford(sorgente,destinazione);
			if(mindist==inf) write << "inf.";
			else write << mindist;
			write << endl;
		}
		else if(tipodato=="double"){
			double elem;
			double nodo2;
			double sorgente, destinazione;
			LGraph<double> grafo(n);
			for(int i=0; i<m; i++){
				read >> nodo1 >> nodo2 >> peso;
				grafo.addNode(atof(nodo1.substr(1).c_str()));
				grafo.addNode(nodo2);
				grafo.addEdge(atof(nodo1.substr(1).c_str()), nodo2, atoi((peso.substr(0, peso.length()-1)).c_str()));
			}
			read >> sorgente >> destinazione;
			int mindist=grafo.Djkharta(sorgente, destinazione);
			//int mindist=grafo.Bellman_Ford(sorgente,destinazione);
			if(mindist==inf) write << "inf.";
			else write << mindist;
			write << endl;
		}
	}
	read.close();
	write.close();
	return 0;
}
