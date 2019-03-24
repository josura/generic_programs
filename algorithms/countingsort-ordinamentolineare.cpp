#include<iostream> 
#include<fstream>
#include<algorithm>
#include<climits> 
#include <ctime>
using namespace std;

// funzione ausiliaria utilizzata per stampare gli elementi di un array A di dimensione n
void print(int *A, int n) {
	for(int i=0; i<n; i++)
		cout << A[i] << " ";
	cout << endl;
}

/*int fakemin,fakemax;
	fakemin=fakemax=A[0];
	for(int i=1; i<n; i+=2) {
		if(A[i]>A[i+1]){
			fakemin=A[i+1];
			fakemax=A[i];
		}else {
			fakemin=A[i];
			fakemax=A[i+1];
		}
		if(max<fakemax) max=fakemax;
		if(min>fakemin) min=fakemin;
	}
	if(!(n%2)){
		if(max<A[n-1]) max=A[n-1];
		else if(min>A[n-1]) min=A[n-1];
	}*/

void CountingSort(int *A, int n,ofstream& str) {
	int max = A[0];
	int min = A[0];
	for(int i=1; i<n; i++) {
		if(max<A[i]) max=A[i];
		if(min>A[i]) min=A[i];
	}
	int range = max-min+1;
	int *B = new int[n];
	int *C = new int[range];
	for(int i=0; i<range; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[A[i]-min]++;
	for(int i=1; i<range; i++) C[i] += C[i-1];
	for(int i=n-1; i>=0; i--) {
		B[C[A[i]-min]-1] = A[i];
		C[A[i]-min]--;
	}
	for(int i=0; i<n; i++) A[i] = B[i];
	for(int i=0;i<range;i++) str<<C[i]<<" ";
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
    	input>>tipo>>numel;
    	cout<<tipo<<numel<<"  ";
    	if(tipo=="int"){
        	int* arr=new int[numel];
			for(int i=0; i<numel; i++){
				input >> arr[i];
				cout<<arr[i]<<" ";
			}
			cout<<endl;
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
				output << arr[i]<<" ";
			}
        	output<<endl;
    	}
    	else if(tipo=="double"){
        	int* arr=new int[numel];
        	double aux;
			for(int i=0; i<numel; i++){
				input >> aux;
				aux*=10;
				arr[i]=int(aux);
			}
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
			output << arr[i]/10.0<<" ";
			}
        	output<<endl;
    	}
    	else if(tipo=="char"){
        	int* arr=new int[numel];
        	char aux;
			for(int i=0; i<numel; i++){
				input >> aux;
				arr[i]=int(aux);
			}
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
			output <<char( arr[i])<<" ";
			}
        	output<<endl;
    	}
    	else if(tipo=="bool"){
        	int* arr=new int[numel];
			for(int i=0; i<numel; i++){
				input >> arr[i];
			}
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
			output << arr[i]<<" ";
			}
        	output<<endl;
    	}
    }
    output.close();
    input.close();
}
