#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

int counter=0;

using namespace std;

main(){
	unsigned numcasse,numdef;
	double maxpeso,auxpeso,sommapeso;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		counter++;
		sommapeso=0;
		numdef=0;
		input>>maxpeso>>numcasse;
		vector<double> casse;
		for(unsigned i=0;i<numcasse;i++){
			input>>auxpeso;
			casse.push_back(auxpeso);		
		}
		sort(casse.begin(),casse.end());                                     // per ordinare il vector in ordine crescente
		/*float temp;
		for (unsigned i = 0, min_idx; i < casse.size()-1; i++){
        	min_idx = i;
        	for (unsigned j = i+1; j < casse.size(); j++)					//sempre per ordinare il vector in ordine crescente ma tramite selection sort,
          		if (casse[j] < casse[min_idx])
            		min_idx = j;
            temp=casse[min_idx];
			casse[min_idx]=casse[i];
			casse[i]=temp;	
    	}*/
		for(unsigned i=0;i<casse.size() && sommapeso+casse[i]<=maxpeso;i++){
			numdef++;
			sommapeso+=casse[i];
		}
		output<<numdef<<" "<<sommapeso<<endl;
	}	
}
