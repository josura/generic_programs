#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

unsigned matrioska(unsigned lung, unsigned larg,unsigned alt,vector<unsigned>& lunghezze,vector<unsigned>& larghezze,vector<unsigned>& altezze){
	unsigned short sadcof=1,maxcof=1;	
	for(unsigned i=0;i<lunghezze.size() ;i++){	
		if(lung<lunghezze[i] && larg<larghezze[i] && alt<altezze[i]){
			sadcof+=matrioska(lunghezze[i], larghezze[i], altezze[i],lunghezze,larghezze,altezze);
		}
		if(sadcof>maxcof) maxcof=sadcof;
		sadcof=1;
	}
	return maxcof;
}

int main(){
	unsigned numele,auxcof,maxi;
	unsigned auxlung,auxlarg,auxprof;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numele;
		maxi=1;
		vector<unsigned> lunghezze,larghezze,altezze;
		vector<unsigned short> cofanetti;
		for(unsigned i=0;i<numele;i++){
			input>>auxlung>>auxlarg>>auxprof;
			lunghezze.push_back(auxlung);
			larghezze.push_back(auxlarg);
			altezze.push_back(auxprof);
		}
		for(unsigned i=0;i<numele;i++){
			auxcof=matrioska(lunghezze[i],larghezze[i],altezze[i],lunghezze,larghezze,altezze);//cout<<auxcof<<endl;
			if(auxcof>maxi) maxi=auxcof;
		}
		cout<<endl<<maxi<<endl;
		output<<maxi<<endl;
	}
	
}
