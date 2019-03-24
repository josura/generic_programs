#include<iostream> 
#include<fstream>
#include<algorithm>
#include<climits> 
using namespace std; 

int parent(int i) {return  floor( (i-1)>>1); } 
int left(int i) { return ((i<<1) + 1); }   
int right(int i) { return (((i<<1)|1) +1); }
  
template<class T>
class MaxBinaryHeap 
{ 
    T* harr;  
    int capacity;  
    int heap_size; 
    int parent(int i) {return  ( (i-1)>>1); } 
	int left(int i) { return ((i<<1) + 1); }   
	int right(int i) { return (((i<<1)|1 )+1); }
public:  
    MaxBinaryHeap(int _cap):capacity(_cap),heap_size(0){
		harr=new T[_cap];    
	}
	MaxBinaryHeap(T* arr,int _cap):capacity(_cap),heap_size(_cap){
		harr=new T[_cap];
		for(int i=0;i<_cap;i++)
			harr[i]=arr[i];
		BuildMaxHeap();    
	}
    void MaxHeapify(int i){
    	int l = left(i); 
    	int r = right(i); 
    	int largest = i; 
    	if (l < heap_size && harr[l] > harr[i]) 
        	largest = l; 
    	if (r < heap_size && harr[r] > harr[largest]) 
        	largest = r; 
    	if (largest != i) 
    	{ 
        	swap(harr[i],harr[largest]); 
        	MaxHeapify(largest); 
    	}	 
	} 
  	void BuildMaxHeap(){
  		for(int i=floor((capacity)/2);i>=0;i--)
			MaxHeapify(i);
	}
    
    T extractMax(){
    	if(!heap_size)exit(0);
    	swap(harr[0],harr[heap_size-1]);
    	heap_size--;
    	MaxHeapify(0);
    	return harr[heap_size+1];
	} 
  
    // Decreases key value of key at index i to new_val 
    void increaseKey(int i, T new_val){
    	harr[i]=new_val;
    	while(i>0 && harr[parent(i)]<harr[i]){
    		swap(harr[parent(i)],harr[i]);
    		i=parent(i);
		}
	}
  
    // Returns the minimum key (key at root) from min heap 
    int getMax() { return harr[0]; } 
  
    // Deletes a key stored at index i 
    void deleteKey(int i){
    	swap(harr[i],harr[heap_size-1]);
    	heap_size--;
    	MaxHeapify(i);
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
	friend ostream& operator<<(ostream& stream, MaxBinaryHeap<T> dx){
		for(int i=0;i<dx.heap_size;i++)
			stream<<dx.harr[i]<<" ";
		stream<<endl;
		return stream;	
	}
	friend ofstream& operator<<(ofstream& stream, MaxBinaryHeap<T> dx){
		for(int i=0;i<dx.heap_size;i++)
			stream<<dx.harr[i]<<" ";
		//stream<<endl;
		return stream;	
	}
	
	void heapsort(){
		
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
    	int largest = i; 
    	if (l < heap_size && harr[l] < harr[i]) 
        	largest = l; 
    	if (r < heap_size && harr[r] < harr[largest]) 
        	largest = r; 
    	if (largest != i) 
    	{ 
        	swap(harr[i],harr[largest]); 
        	MinHeapify(largest); 
    	}		 
	} 
  	void BuildMinHeap(){
  		for(int i=floor((capacity)/2);i>=0;i--)
			MinHeapify(i);
	}
    
    T extractMin(){
    	if(!heap_size)exit(0);
    	swap(harr[0],harr[heap_size-1]);
    	heap_size--;
    	MinHeapify(0);
    	return harr[heap_size+1];
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
    	while (i != 0 && harr[parent(i)] > harr[i]){ 
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
		
	}
};

template<class T>
 void MaxHeapify(T* arr,int i,int n){
    	int l = left(i); 
    	int r = right(i); 
    	int largest = i; 
    	if (l < n && arr[l] > arr[i]) 
        largest = l; 
    	if (r < n && arr[r] > arr[largest]) 
        	largest = r; 
    	if (largest != i) 
    	{ 
        	swap(arr[i],arr[largest]); 
        	MaxHeapify(arr,largest,n); 
    	}	 
}


template<class T>
void heap_sort(T* arr,int n){
	for(int i=floor((n-1)/2);i>=0;i--)
		MaxHeapify(arr,i,n);
	for(unsigned i=0;i<n;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
	for(int i=n-1;i>=0;i--){
		swap(arr[i],arr[0]);
		MaxHeapify(arr,0,i);
	}
}

/*template <class T> class PriorityQueue {
public:
    virtual T* extract() = 0;
    virtual PriorityQueue<T>* enqueue(T x) = 0;
    virtual int size() = 0;
};


template <class H> class BinaryHeap : public PriorityQueue<H>{
private:
    //I metodi e le variabile presenti in questa sezione devono rimanere primati e non devono essere visibili all'esterno. Vengono utilizzati solo per la gestione interna della struttura dati.
    H **A;
    int heapsize;   // dimensione effettiva dello Heap
    int len;        // numero massimo di elementi del vettore
    int current;    // indice per l'implementazione dell'iteratore
    int left(int i) { return i<<1; }
    int right(int i) { return (i<<1)|1; }
    int parent(int i) { return i>>1; }
    void scambia(int i, int j);
    void heapify(int i);
    
public:
    //I metodi presenti in questa sezione della classe rappresentano l'interfaccia disponibile agli utenti esterni
    virtual int compare(H *a, H *b)=0;
    BinaryHeap(int size);
    BinaryHeap(H** V, int size);
    void buildHeap();
    H* extract();
    void modify(int i, H k);
    BinaryHeap<H>* enqueue(H x);
    int size();
    //metodi per l'implementazione dell'iteratore
    void begin();
    H* next();
    int has_next();
};



template <class H> class MaxBinaryHeap : public BinaryHeap<H> {
private:
public:
    int compare(H* a, H *b) {
        return (*a>*b);														//faro Ë un genio che con i double fa le sottrazioni dove non sono necessarie e distrugge tutto
    }
    MaxBinaryHeap(int size) : BinaryHeap<H>(size) {}
    MaxBinaryHeap(H **A, int size) : BinaryHeap<H>(A, size) {}
    H* extractMax() { return BinaryHeap<H>::extract(); }
    void increaseKey(int i, H k) { return BinaryHeap<H>::modify(i,k); }
};


template <class H> class MinBinaryHeap : public BinaryHeap<H> {
private:
public:
    int compare(H* a, H *b) {
        return (*a<*b);
    }
    MinBinaryHeap(int size) : BinaryHeap<H>(size) {}
    MinBinaryHeap(H **A, int size) : BinaryHeap<H>(A, size) {}
    H* extractMin() { return BinaryHeap<H>::extract(); }
    void decreaseKey(int i, H k) { return BinaryHeap<H>::modify(i,k); }
};

//overloading dell'peratore di stampa per il MinBinaryHeap
template <class H> ostream& operator<<(ostream& out, const MinBinaryHeap<H>& h) {
    MinBinaryHeap<H> q = h; // copia difensiva per mantenere h costante
    q.begin(); // inizializzazione dell'iteratore
    while(q.has_next()) { //iterazione sugli elementi della struttura
        out << *q.next() << " ";
    }
    return out;
}

//overloading dell'peratore di stampa per il MaxBinaryHeap
template <class H> ostream& operator<<(ostream& out, const MaxBinaryHeap<H>& h) {
    MaxBinaryHeap<H> q = h; // copia difensiva per mantenere h costante
    q.begin(); // inizializzazione dell'iteratore
    while(q.has_next()) { //iterazione sugli elementi della struttura
        out << *q.next() << " ";
    }
    return out;
}

//overloading dell'peratore di stampa per il MinBinaryHeap
template <class H> ofstream& operator<<(ofstream& out, const MinBinaryHeap<H>& h) {
    MinBinaryHeap<H> q = h; // copia difensiva per mantenere h costante
    q.begin(); // inizializzazione dell'iteratore
    while(q.has_next()) { //iterazione sugli elementi della struttura
        out << *q.next() << " ";
    }
    return out;
}

//overloading dell'peratore di stampa per il MaxBinaryHeap
template <class H> ofstream& operator<<(ofstream& out, const MaxBinaryHeap<H>& h) {
    MaxBinaryHeap<H> q = h; // copia difensiva per mantenere h costante
    q.begin(); // inizializzazione dell'iteratore
    while(q.has_next()) { //iterazione sugli elementi della struttura
        out << *q.next() << " ";
    }
    return out;
}*/

int main(){
	ifstream input("input.txt");
    ofstream output("output.txt");
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
    string tipo;
    int numel;
    while(!input.eof()){
        input>>tipo;
		input>>numel;
        if(tipo=="int"){
            int* arr=new int[numel];
			for(int i=0; i<numel; i++){
				input >> arr[i];
			}
			MinBinaryHeap<int> heap(arr,numel);
			output<<heap;
        }
        else if(tipo=="double"){
            double* arr=new double[numel];
            for(int i=0; i<numel; i++){
				input >> arr[i];
			}
			MinBinaryHeap<double> heap(arr,numel);
			output<<heap;
        }
        else if(tipo=="char"){
            char* arr=new char[numel];
            for(int i=0; i<numel; i++){
				input >> arr[i];
			}
			MinBinaryHeap<char> heap(arr,numel);
			output<<heap;
        }
        else if(tipo=="bool"){
            bool* arr=new bool[numel];
			for(int i=0; i<numel; i++){
				input >> arr[i];
			}
			MinBinaryHeap<bool> heap(arr,numel);
			output<<heap;
        }
        output<<endl;
    }
    output.close();
    input.close();
}

/*template <class H> void BinaryHeap<H>::scambia(int i, int j) {
    H* tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

//La funzione heapify utilizza il metodo virtuale compare() che permette di definire la priorit√  tra le chiavi contenute all'interno della struttura dati. Le classi Min-Heap e Max-Heap conterranno l'implementazione di questo metodo.
template <class H> void BinaryHeap<H>::heapify(int i) {
    if(i>heapsize) return;
    int l = left(i);
    int r = right(i);
    int v = i;
    if(l<=heapsize && compare(A[v], A[l])<0) v=l;
    if(r<=heapsize && compare(A[v], A[r])<0) v=r;
    if(v==i) return;
    scambia(i,v);
    heapify(v);
}

template <class H> BinaryHeap<H>::BinaryHeap(int size) {
    A = new H*[size+1];
    len = size+1;
    heapsize = 0;
}

//costruttore che crea uno a partire da un vettore di input V, di dimensione size
template <class H> BinaryHeap<H>::BinaryHeap(H** V, int size) {
    A = V;
    len = size+1;
    heapsize = size;
}

template <class H> void BinaryHeap<H>::buildHeap() {
    for(int i=heapsize/2; i>0; i--)
        heapify(i);
}

template <class H> H* BinaryHeap<H>::extract() {
    if(heapsize==0) return NULL;
    scambia(1, heapsize);
    heapsize--;
    heapify(1);
    return A[heapsize+1];
}


//la funzione modify permette di modificare una chiave contenuta all'interno della struttura. Nella specifico modifica la chiave in posizione i con il valore k. Corrisponder√  a Decrease-Key in un Min-Heap o a Increase-Key i un Max-Heap
template <class H> void BinaryHeap<H>::modify(int i, H k) {
    if(i<1 || i>heapsize) return;
    if( compare(A[i],&k)>=0 ) return;
    A[i] = new H(k);
    while(i>1 && compare(A[i],A[parent(i)])>0) {
        scambia(i,parent(i));
        i = parent(i);
    }
    return;
}

template <class H> BinaryHeap<H>* BinaryHeap<H>::enqueue(H x) {
    if(heapsize==len-1) return this;
    heapsize += 1;
    A[heapsize] = new H(x);
    int i = heapsize;
    while(i>1 && compare(A[i],A[parent(i)])>0) {
        scambia(i, parent(i));
        i = parent(i);
    }
    return this;
}

template <class H> int BinaryHeap<H>::size() {
    return heapsize;
}


// metodo utilizzato per inizializzare l'iteratore
template <class H> void BinaryHeap<H>::begin() {
    current = 1; //il primo elemento della struttura √® alla posizione 1
}

// metodo che restituisce il successivo elemento nell'iterazione
template <class H> H* BinaryHeap<H>::next() {
    if(current>=0 && current<=heapsize) {
        H* tmp = A[current];
        current++;
        return tmp;
    }
    return NULL;
}

// metodo che restituisce true solo se l'iterazione non √® terminata
template <class H> int BinaryHeap<H>::has_next() {
    if(current>=0 && current<=heapsize) return 1;
    return 0;
}*/
