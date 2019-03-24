#include<iostream> 
#include<algorithm>
#include<climits> 
using namespace std; 

int parent(int i) {return  floor( (i-1)>>1); } 
int left(int i) { return ((i<<1) + 1); }   
int right(int i) { return (((i<<1)|1) +1); }
  
template<class T>
class MaxHeap 
{ 
    T* harr;  
    int capacity;  
    int heap_size; 
    int parent(int i) {return  ( (i-1)>>1); } 
	int left(int i) { return ((i<<1) + 1); }   
	int right(int i) { return (((i<<1)|1 )+1); }
public:  
    MaxHeap(int _cap):capacity(_cap),heap_size(0){
		harr=new T[_cap];    
	}
	MaxHeap(int _cap,T* arr):capacity(_cap),heap_size(0){
		harr=new T[_cap];
		for(unsigned i=0;i<7;i++)
			insertKey(arr[i]);    
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
    void insertKey(T k){
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
	friend ostream& operator<<(ostream& stream, MaxHeap<T> dx){
		for(int i=0;i<dx.heap_size;i++)
			stream<<dx.harr[i]<<" ";
		stream<<endl;
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

int main(){
	//MaxHeap<int> heap(8);
	int arr[7]={2,3,1,0,-1,7,8};
	MaxHeap<int> heap(8 ,arr);
	cout<<heap;
	heap.extractMax();
	cout<<heap;
	heap.extractMax();
	cout<<heap;
	heap.extractMax();
	cout<<heap;
	/*for(unsigned i=0;i<7;i++)
		cout<<arr[i]<<" ";
	cout<<endl;	
	heap_sort(arr,7);
	for(unsigned i=0;i<7;i++)
		cout<<arr[i]<<" ";*/
}
