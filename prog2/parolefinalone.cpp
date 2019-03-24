#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
	unsigned counter,counter2,j,indiceprec;
	string parola,parolone,parolascomposta;
	bool candidato;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>parola>>parolone;
		vector<unsigned> indici;
		counter=counter2=0;
		for(unsigned i=0;i<parolone.size();i++){
			if(!candidato) indiceprec=i;
			parolascomposta=parola;
			candidato=false;
			for( j=0;j<parolascomposta.size() && (i-indiceprec)<parolascomposta.size() && (j+indiceprec)<parolone.size() && !candidato ;j++){
				if(parolascomposta[j]==parolone[i] && parolascomposta[i-indiceprec]==parolone[j+indiceprec]) {
					cout<<parolascomposta;
					candidato=true;
				}
			}
			if(!candidato){
				parolascomposta=parola;
				counter=0;
				i=indiceprec;
			} else counter++; /*{
				for(unsigned d=0;d<parolascomposta.size();d++){
					if(parolascomposta[d]=='$')
						counter++;
				}
			}*/if(parola[i-indiceprec]==parolone[j]) counter++;
			if(counter==parola.size()) {indici.push_back(i-parola.size()+1); 
				i=indiceprec;
			}
		}
		for(unsigned i=0;i<indici.size();i++){
			cout<<indici[i]<<endl;
			output<<indici[i]<<" ";
		}
		output<<endl;
	}
	
}
