#include<algorithm>
#include<iostream>
#include<string>
#include<cctype>
#include<fstream>
#include<vector>

using namespace std;

unsigned factorial(unsigned n){
	unsigned factor=1;
	for(unsigned short i =1; i <=n; i++)
    {
        factor*=i;
    }
    return factor;
}

main(){
	unsigned cifrecomb;
	bool entraalf;
	string wildcard,final;
	char auxchar;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>cifrecomb;
		vector<char> alfabeto,alfabetodellawild;
		vector<unsigned short> indice;
		vector<string> combinazioni;
		for(unsigned i=0;i<cifrecomb;i++){
			input>>auxchar;
			alfabeto.push_back(auxchar);		
		}
		input>>wildcard;
		final=wildcard;
		cout<<wildcard<<"\n\n";
		for(unsigned i=0;i<wildcard.size();i++){
			if(!isdigit(wildcard[i])) indice.push_back(i);
		}
		for(unsigned j=0;j<alfabeto.size() ;j++){
			entraalf=true;
			for(unsigned k=0;k<wildcard.size() && entraalf;k++){
				if(wildcard[k]==alfabeto[j]) entraalf=false;
			}
			if(entraalf) alfabetodellawild.push_back(alfabeto[j]);
		}
		sort(alfabetodellawild.begin(),alfabetodellawild.end());
		for(unsigned i=0;i<indice.size();i++){
			final[indice[i]]=alfabetodellawild[i];
		}
		combinazioni.push_back(final);
		output<<final<<" ";
		for(unsigned i=0;i<factorial(indice.size())-1;i++){
			next_permutation(alfabetodellawild.begin(),alfabetodellawild.end());
			for(unsigned j=0;j<indice.size();j++){
				final[indice[j]]=alfabetodellawild[j];
			}
			//combinazioni.push_back(final);
			output<<final<<" ";
		}
		output<<endl;
		
	}	
}
