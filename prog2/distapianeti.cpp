#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int main(){
	unsigned numpian,distmin;
	int posxro,posyro,pox,poy,posverax,posveray;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numpian;
		input>>posxro;
		input>>posyro;
		input>>pox;
		input>>poy;
		distmin=abs((pox-posxro)*(pox-posxro))+abs((poy-posyro)*(poy-posyro));
		for(unsigned i =1;i<numpian;i++){
			input>>pox;
			input>>poy;
			if(abs((pox-posxro)*(pox-posxro))+abs((poy-posyro)*(poy-posyro))<distmin){
				distmin=abs((pox-posxro)*(pox-posxro))+abs((poy-posyro)*(poy-posyro));
				posverax=pox;
				posveray=poy;
			}
		}
		output<<posverax<<" "<<posveray<<endl;
	}
}
