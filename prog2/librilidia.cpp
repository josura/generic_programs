#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

main(){
	int numfum,numlidia,auxnum,numlib=0,numcercato;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		numcercato=0;
		numlib=0;
		input>>numfum;
		input>>numlidia;
		for(int i =0;i<numfum;i++){
			numlib++;
			input>>auxnum;
			if(auxnum==numlidia)
				numcercato=numlib;			
		}
		output<<numcercato<<endl;
	}
	
}
