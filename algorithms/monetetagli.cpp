#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

template<class T>
int partition_decr(T *arr, const int left, const int right) {
    const int mid = left + (right - left) / 2;
    const int pivot = arr[mid];
    // move the mid point value to the front.
    std::swap(arr[mid],arr[left]);
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while(i <= j && arr[i] > pivot) {
            i++;
        }

        while(i <= j && arr[j] <= pivot) {
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


    int part = partition_decr(arr, left, right);
    quicksort(arr, left, part - 1, sz);
    quicksort(arr, part + 1, right, sz);
}

template<class T>
void quicksort(T* ar, int n){
	quicksort(ar,0,n-1,n);
}

template<class T>
void print(T* arr,int size){
	for(unsigned i=0;i<size;i++)cout<<arr[i]<<" ";
	cout<<endl;
}


int resto_mon( int conto,int* tagli, int m) { 
   int* table=new int[conto+1]; 
    table[0] = 0; 
    for (int i=1; i<=conto; i++) 
        table[i] = INT_MAX; 
    for (int i=1; i<=conto; i++) 
    { 
        for (int j=0; j<m; j++) 
          if (tagli[j] <= i) 
          { 
              int sub_res = table[i-tagli[j]]; 
              if (sub_res != INT_MAX && sub_res + 1 < table[i]) 
                  table[i] = sub_res + 1; 
          } 
    } 
    return table[conto]; 
} 

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
    int conto,numtagli,aux,nummonete;
    while(!input.eof()){
    	cout<<"ciao ";
		input>>conto>>numtagli;
		int* tagli= new int[numtagli];
		for(int i=0;i<numtagli;i++){
			input>>aux;
			tagli[i]=aux;
		}
		//cout<<aux1<<aux1.size()<<" "<<aux2<<aux2.size()<<endl;
		nummonete=resto_mon(conto,tagli,numtagli);
		//cout<<longestcs<<endl;
		output<<nummonete<<endl;
	}
    output.close();
    input.close();
    return 0;
}
