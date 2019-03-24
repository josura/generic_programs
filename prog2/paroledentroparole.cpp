#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
	unsigned counter,j,indiceprec;
	string parola,parolone;
	bool candidato;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>parola>>parolone;
		vector<unsigned> indici;
		counter=0;
		for(unsigned i=0;i<parolone.size();i++){
			if(!candidato) indiceprec=i;
			candidato=false;
			for( j=0;j<parola.size() && !candidato ;j++){
				if(parola[j]==parolone[i] && parola[i-indiceprec]==parolone[j+indiceprec]) {
					candidato=true;
					cout<<i-indiceprec<<" i="<<i<<endl<<parola[j]<<parolone[i]<<" altro "<<parola[i-indiceprec]<<parolone[j+indiceprec]<<endl;}
			}
			if(!candidato){
				counter=0;
				i=indiceprec;
			} else  counter++;//if(parola[i-indiceprec]==parolone[j]) counter++;
			if(counter==parola.size()) {indici.push_back(i-parola.size()+1);
				cout<<i-parola.size()+1<<")   ";
				for(unsigned k=i-parola.size()+1;k<i+1;k++){
					cout<<parolone[k]<<" ";
				}
				i=indiceprec;
				cout<<endl;
			}
		}
		for(unsigned i=0;i<indici.size();i++){
			cout<<indici[i]<<" ";
			output<<indici[i]<<" ";
		}
		cout<<endl;
		output<<endl;
	}
	
}
