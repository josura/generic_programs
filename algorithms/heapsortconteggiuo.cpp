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
public:  
	int getchiamate(){return conteggioheap;}
    MaxBinaryHeap(int _cap):capacity(_cap),heap_size(0),conteggioheap(-1){
		harr=new T[_cap];    
	}
	MaxBinaryHeap(T* arr,int _cap):capacity(_cap),heap_size(_cap),conteggioheap(-1){
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
  		for(int i=(capacity)/2;i>=0;i--)
			MaxHeapify(i);
	}
    
    T extractMax(){
    	if(!heap_size)return(0);
    	swap(harr[0],harr[heap_size-1]);
    	heap_size--;
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
		for(int i=0;i<dx.capacity;i++)
			stream<<dx.harr[i]<<" ";
		return stream;	
	}
	friend ofstream& operator<<(ofstream& stream, MaxBinaryHeap<T> dx){
		for(int i=0;i<dx.capacity;i++)
			stream<<dx.harr[i]<<" ";
		//stream<<endl;
		return stream;	
	}
	void flusherino(){
		for(int i=0;i<capacity;i++)
			extractMax();
	}
	void heapsort(){
		for(int i=capacity-1;i>=0;i--){
			extractMax();
		}
	}
}; 

template<class T>
 void MaxHeapify(T* arr,int i,int n,int& cont){
 		cont++;
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
        	MaxHeapify(arr,largest,n,cont); 
    	}
}

template<class T>
T extractMax(T* arr,int n,int &cont){
    	n--;
		swap(arr[0],arr[n]);
		if(n>1)
    	MaxHeapify(arr,0,n,cont);
    	return arr[n+1];
	} 

template<class T>
void heap_sort_cont(T* arr,int n,int& cont){
	for(int i=(n-1)/2;i>=0;i--)
		MaxHeapify(arr,i,n,cont);
	for(int i=n;i>0;i--){
		extractMax(arr,i,cont);
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
			MaxBinaryHeap<int> heap(arr,numel);
			heap.heapsort();
			//heap_sort_cont(arr,numel,conteggio);
			output<<heap.getchiamate()<<" "<<heap;
        }
        else if(tipo=="double"){
            double* arr=new double[numel];
			for(int i=0; i<numel; i++){
				input >> arr[i];
			}
			//heap_sort_cont(arr,numel,conteggio);
			MaxBinaryHeap<double> heap(arr,numel);
			heap.heapsort();
			output<<heap.getchiamate()<<" "<<heap;
        }
        else if(tipo=="char"){
            char* arr=new char[numel];
            for(int i=0; i<numel; i++){
				input >> arr[i];
			}
			MaxBinaryHeap<char> heap(arr,numel);
			heap.heapsort();
			//heap_sort_cont(arr,numel,conteggio);
			output<<heap.getchiamate()<<" "<<heap;
        }
        else if(tipo=="bool"){
            bool* arr=new bool[numel];
            for(int i=0; i<numel; i++){
				input >> arr[i];
			}
			MaxBinaryHeap<bool> heap(arr,numel);
			heap.heapsort();
			//heap_sort_cont(arr,numel,conteggio);
			output<<heap.getchiamate()<<" "<<heap;
        }
        output<<endl;
    }
    output.close();
    input.close();
}
