#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
	unsigned numcop,minuti;
	int int1,int2,int3,minimo,risultato;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numcop>>minuti;
		vector<int> intervalli,cariche;
		for(unsigned i=0;i<numcop;i++){
			input>>int1>>int2;
			intervalli.push_back(int1);
			intervalli.push_back(int2);		
		}
		for(unsigned i=0;i<intervalli.size();i++){
			cout<<intervalli[i]<<" ";	
		}
		cout<<endl;
		int3=int2=1-intervalli[0];
		cariche.push_back(int3);
		//cout<<"int3 "<<int3<<endl;
		for(unsigned i=0;i<intervalli.size();i+=2){
			int1=intervalli[i+1]-intervalli[i]+1;
			//cout<<endl<<"int1 "<<int1<<endl;
			int3+=int1;
			//cout<<"int3 + int1 "<<int3<<endl;
			cariche.push_back(int3);
			if(i+2<intervalli.size()){
				int2=-(intervalli[i+2]-intervalli[i+1]-1);
				//cout<<"int2 "<<int2<<endl;
				int3+=int2;
				//cout<<"int3 + int2 "<<int3<<endl;
				cariche.push_back(int3);
			}
		}
		int2=-(minuti-intervalli[intervalli.size()-1]);
		//cout<<"int2 "<<int2<<endl;
		int3+=int2;
		//cout<<"int3 + int2 "<<int3<<endl;
		cariche.push_back(int3);
		minimo=cariche[0];
		for(unsigned i=1;i<cariche.size();i++){
			if(cariche[i]<minimo) minimo=cariche[i];		
		}
		if(minimo>=0) {risultato=1;}
		else {risultato=-minimo+1;}
		//cout<<endl<<risultato<<endl;
		output<<risultato<<endl;
	}
}
