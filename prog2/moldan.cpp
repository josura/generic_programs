#include<fstream>
#include<cstdlib>
#include<iostream>
#include <string>
#include <sstream>

using namespace std;

int main(){
	ifstream read;
	ofstream write;
	int n, m, p;
	int prodotto;
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
		prodotto=0;
		read >> n;
		read >> m;
		read >> p;
		int a[n][m], b[m][p];
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				read >> a[i][j];
			}
		}
		for(int i=0; i<m; i++){
			for(int j=0; j<p; j++){
				read >> b[i][j];
			}
		}
		for(int i=0; i<n; i++){
			for(int k=0; k<p; k++){
				prodotto=0;
				for(int j=0; j<m; j++){
					prodotto+=a[i][j]*b[j][k];
				}
				write << prodotto << " ";
			}
		}
		write << endl;
	}
	read.close();
	write.close();
	return 0;
}