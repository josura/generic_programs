#include<fstream>
#include<cstdlib>
#include<iostream>
#include <string>
#include <sstream>

using namespace std;

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
	while(!read.eof()){
		int n=0;
		int doppioni=0;
		read >> n;
		int a[n];
		for(int i=0; i<n; i++){
			read >> a[i];
		}
		int min, tmp;
		for(int i=0; i<n-1; i++){
			min = i;
			for(int j=i+1; j<n; j++){
				if(a[j]<a[min]) min = j;
			}
			tmp = a[i];
			a[i]=a[min];
			a[min]=tmp;
		}
		for(int i=1; i<n; i++){
			if(a[i]==a[i-1]) {
				doppioni++;
				cout << a[i] << endl;
			}	
		}
		write << doppioni << endl;
	}
	read.close();
	write.close();
	return 0;
}
