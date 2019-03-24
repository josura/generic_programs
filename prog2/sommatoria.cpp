#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
	int numele;
    double aux,somma;
	ifstream input("input.txt");              //input (1).txt
	ofstream output("output.txt");              //output.txt
	while(!input.eof()){
        somma=0;
		input>>numele;
		for(unsigned i=0;i<numele;i++){
			input>>aux;
            somma+=aux;
		}
        output<<somma<<endl;
		
	}
	
}