#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(){
	int numele;
    string aux;
    char c;
	ifstream input("input.txt");              //input (1).txt
	ofstream output("output.txt");              //output.txt
	while(!input.eof()){
		input>>numele;
		input>>aux;
        for(unsigned i=0; i<aux.size(); i++){
			if(aux[i]=='a') c='x';
			else if(aux[i]=='b') c='y';
			else if(aux[i]=='c') c='z';
			else c=aux[i]-3;
			output << c;
		}
        output<<endl;
		
	}
	
}