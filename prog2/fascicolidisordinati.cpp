#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

unsigned flips(vector<unsigned>& fascicoliord,vector<unsigned>& fascicolidiso){
	unsigned contatoreswitch=0,k,indi;
	bool esci;
	for(unsigned i=0;i<fascicoliord.size();i++){
		esci=false;
		if(fascicoliord[i]!=fascicolidiso[i]){
			for(unsigned j=i;j<fascicoliord.size() &&  !esci;j++){
				if(fascicoliord[j]==fascicolidiso[i]){
					indi=j;
					k=0;
					while(k<(j-i)/2 ){	
						swap(fascicoliord[indi],fascicoliord[indi-2]);
						//cout<<"scambio"<<fascicoliord[indi]<<" <-> "<<fascicoliord[indi-2];
						//cout<<endl;
						contatoreswitch++;
						k++;
						indi+=-2;
						if(fascicolidiso[i]!=fascicoliord[i]){
							esci=true;
						}
					}
					
				}
			}
		}
	}
	return contatoreswitch;
}

int main(){
	unsigned numele,auxnum;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		
		input>>numele;
		vector<unsigned> fascicolidiso,fascicoli;
		vector<unsigned short> cofanetti;
		for(unsigned i=0;i<numele;i++){
			input>>auxnum;
			fascicolidiso.push_back(auxnum);
		}
		fascicoli=fascicolidiso;
		sort(fascicoli.begin(),fascicoli.end());
		/*for(unsigned i=0;i<numele;i++){
			cout<<fascicolidiso[i]<<" ";
		}
		cout<<endl;
		for(unsigned i=0;i<numele;i++){
			cout<<fascicoli[i]<<" ";
		}
		cout<<endl;*/
		output<<flips(fascicoli,fascicolidiso);
		output<<endl;
		
		
		//cout<<endl<<maxi<<endl;
		//output<<cofanetti<<endl;
	}
	
}
