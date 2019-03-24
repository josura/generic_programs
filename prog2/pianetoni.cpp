#include<fstream>
#include<iostream>
#include<sstream>

using namespace std;

int main(){
	unsigned numpian;
	string auxnum,numbig;
	bool uguali=true;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		numbig="0";
		uguali=true;
		input>>numpian;
		for(unsigned i =0;i<numpian;i++){
			uguali=true;
			cout<<"whela"<<numpian<<endl<<numbig<<endl; 
			input>>auxnum;
			if(auxnum.size()>numbig.size()){
				numbig=auxnum;
				cout<<"ciao"<<numbig<<endl;
			}
			else if(auxnum.size()==numbig.size()){
				
				for(unsigned j=0;j<auxnum.size() && uguali==true;j++){
					cout<<"wawawa"<<auxnum[j]<<numbig[j]<<endl;
					if(auxnum[j]==numbig[j]){
						cout<<"wawawa"<<endl;
						uguali=true;
					}	else 	if(auxnum[j]>numbig[j]){
							cout<<"non ciao"<<auxnum[j]<<numbig[j]<<endl;
							numbig=auxnum;
							cout<<"haaaaa"<<numbig<<endl;
							uguali=false;
					}	else 	if((auxnum[j])<(numbig[j])){
							uguali=false;
					}	
				}
			}				
		}
		output<<numbig<<endl;
	}
	
}
