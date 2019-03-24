#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>


using namespace std;

main(){
	unsigned numgiorni;
	double diffmax,auxgamb;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numgiorni;
		vector<double> giorno;
		for(unsigned i=0;i<numgiorni;i++){
			input>>auxgamb;
			giorno.push_back(auxgamb);		
		}
		diffmax=0;
		for(unsigned i=0;i<giorno.size()-1;i++){
			for(unsigned j=i+1;j<giorno.size();j++){
				auxgamb=giorno[j]-giorno[i];
				if(diffmax<auxgamb) diffmax=auxgamb;
			}
		}
		output<<diffmax<<endl;
	}
	
}
