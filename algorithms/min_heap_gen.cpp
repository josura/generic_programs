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
    int heap_size,conteggioheap; 
    int parent(int i) {return  ( (i-1)>>1); } 
	int left(int i) { return ((i<<1) + 1); }   
	int right(int i) { return (((i<<1)|1 )+1); }
public:  
	int getchiamate(){return conteggioheap;}
    MaxBinaryHeap(int _cap):capacity(_cap),heap_size(0),conteggioheap(0){
		harr=new T[_cap];    
	}
	MaxBinaryHeap(T* arr,int _cap):capacity(_cap),heap_size(_cap),conteggioheap(0){
		harr=new T[_cap];
		for(int i=0;i<_cap;i++)
			harr[i]=arr[i];
		BuildMaxHeap();    
	}
    void MaxHeapify(int i){
    	conteggioheap++;
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
		//for(int i=0;i<heap_size;i++)
		//	cout<<harr[i]<<" ";
		//cout<<endl<<endl;	 
	} 
  	void BuildMaxHeap(){
  		for(int i=floor((capacity)/2);i>=0;i--)
			MaxHeapify(i);
	}
    
    T extractMax(){
    	if(!heap_size)exit(0);
    	swap(harr[0],harr[heap_size-1]);
    	heap_size--;
    	//for(int i=0;i<heap_size;i++)
		//	cout<<harr[i]<<" ";
		//cout<<endl;
    	if(heap_size)
    		MaxHeapify(0);
    	return harr[heap_size+1];
	} 
    void decreasekey(int i, T new_val){
    	harr[i]=new_val;
    	while(i>0 && harr[parent(i)]<harr[i]){
    		swap(harr[parent(i)],harr[i]);
    		i=parent(i);
		}
	}
    int getMax() { return harr[0]; } 
    void deleteKey(int i){
    	swap(harr[i],harr[heap_size-1]);
    	heap_size--;
    	MaxHeapify(i);
	}
    void enqueue(T k){
    	if (heap_size == capacity){ 
        	cout << "\nOverflow: Could not insertKey\n"; 
        	return; 
    	} 
    	heap_size++; 
    	int i = heap_size - 1; 
    	harr[i] = k; 
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
		for(int i=floor((capacity-1)/2);i>=0;i--)
			MaxHeapify(harr,i,capacity);
		for(int i=capacity-1;i>=0;i--){
			swap(harr[i],harr[0]);
			MaxHeapify(harr,0,i);
		}
	}
}; 

template<class T>
class MinBinaryHeap 
{ 
    T* harr;  
    int capacity;  
    int heap_size,conteggioheapify; 
    int parent(int i) {return  ( (i-1)>>1); } 
	int left(int i) { return ((i<<1) + 1); }   
	int right(int i) { return (((i<<1)|1 )+1); }
public:  
	int getchiamate(){return conteggioheapify;}
    MinBinaryHeap(int _cap):capacity(_cap),heap_size(0),conteggioheapify(0){
		harr=new T[_cap];    
	}
	MinBinaryHeap(T* arr,int _cap):capacity(_cap),heap_size(_cap),conteggioheapify(0){
		harr=new T[_cap];
		for(int i=0;i<_cap;i++)
			harr[i]=arr[i];
		BuildMinHeap();    
	}
    void MinHeapify(int i){
    	conteggioheapify++;
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
    	if(heap_size)
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
		for(int i=floor((capacity-1)/2);i>=0;i--)
			MinHeapify(harr,i,capacity);
		for(int i=capacity-1;i>=0;i--){
			swap(harr[i],harr[0]);
			MinHeapify(harr,0,i);
		}
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
    string tipo,operazione;
    int numel;
    while(!input.eof()){
        input>>tipo;
		input>>numel;
        if(tipo=="int"){
            //int* arr=new int[numel];
            int aux;
			MinBinaryHeap<int> heap(numel);
			for(int i=0; i<numel; i++){
				input >> operazione;
				if(operazione[1]==':'){
					aux=atoi((operazione.substr(2)).c_str());
					heap.enqueue(aux);
				}
				else {
					heap.extractMin();
				}
			}
			output<<heap.getchiamate()<<" ";
			output<<heap;
        }
        else if(tipo=="double"){
            //double* arr=new double[numel];
            MinBinaryHeap<double> heap(numel);
            double aux;
			for(int i=0; i<numel; i++){
				input >> operazione;
				if(operazione[1]==':'){
					aux=atof((operazione.substr(2)).c_str());
					heap.enqueue(aux);
				}
				else {
					heap.extractMin();
				}
			}
			output<<heap.getchiamate()<<" ";
			output<<heap;
        }
        else if(tipo=="char"){
            //char* arr=new char[numel];
            MinBinaryHeap<char> heap(numel);
            char aux;
			for(int i=0; i<numel; i++){
				input >> operazione;
				if(operazione[1]==':'){
					aux=operazione[2];
					heap.enqueue(aux);
				}
				else {
					heap.extractMin();
				}
			}
			output<<heap.getchiamate()<<" ";
			output<<heap;
        }
        else if(tipo=="bool"){
            //bool* arr=new bool[numel];
			MinBinaryHeap<bool> heap(numel);
            bool aux;
			for(int i=0; i<numel; i++){
				input >> operazione;
				if(operazione[1]==':'){
					aux=atoi((operazione.substr(2)).c_str());
					heap.enqueue(aux);
				}
				else {
					heap.extractMin();
				}
			}
			output<<heap.getchiamate()<<" ";
			output<<heap;
        }
        output<<endl;
    }
    output.close();
    input.close();
}

