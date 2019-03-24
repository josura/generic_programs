#include <iostream>

using namespace std;

int sottmax(int a[], int n){
int max = a[0];
for(int i=0; i<n; i++){
	for(int j=i; j<n; j++){
		int somma = 0;
		for(int k=i; k<=j; k++){
			somma+=a[k];
		}
		if(somma>max) max=somma;
	}
}
return max;
}

int main(){
	int linea[12]={13,-5,12,1,-4,16,12,7,19,2,27,-21};
	int massimo;
	massimo = sottmax(linea, 12);
	cout << massimo;
	return 0;
}