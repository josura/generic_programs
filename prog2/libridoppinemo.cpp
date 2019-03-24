#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

main(){
	int numfum,auxnum,numdopp;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		vector<int> numeri;
		numdopp=0;
		input>>numfum;
		for(int i =0;i<numfum;i++){
			input>>auxnum;
			numeri.push_back(auxnum);		
		}
		for(int i =0;i<numeri.size()-1 ;i++){
			for(int j=i+1;j<numeri.size();j++)
				if(numeri[i]==numeri[j] && numeri[i]!=0){
					numeri[j]=0;
					numdopp++;
				}		
		}
		output<<numdopp<<endl;
	}
	
}
