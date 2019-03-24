#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>


using namespace std;

main(){
	unsigned numcase,perqu;
	int diffmax,auxcivico;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numcase>>perqu;
		vector<int> civico;
		for(unsigned i=0;i<numcase;i++){
			input>>auxcivico;
			civico.push_back(auxcivico);		
		}
		sort(civico.begin(),civico.end());
		for(unsigned i=0;i<civico.size();i++){
			cout<<civico[i]<<" ";		
		}
		cout<<endl;
		diffmax=civico[civico.size()-1]-civico[0];
		for(unsigned i=0;i<civico.size()-perqu+1;i++){
				auxcivico=civico[i+perqu-1]-civico[i];
				if(diffmax>auxcivico) diffmax=auxcivico;
		}
		output<<diffmax<<endl;
	}
	
}
