#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

unsigned matrioska(unsigned lung, unsigned larg,unsigned alt,vector<unsigned>& lunghezze,vector<unsigned>& larghezze,vector<unsigned>& altezze){
	unsigned sadcof=1,maxcof=1,k=0;
	vector<unsigned short> coffin;
	for(unsigned i=0;i<lunghezze.size();i++){
		coffin.push_back(1);
		}	
	cout<<" nuova matrioska"<<endl;
	for(unsigned i=0;i<lunghezze.size() ;i++){	
		if(lung<lunghezze[i] && larg<larghezze[i] && alt<altezze[i]){
			cout<<lung<<"<"<<lunghezze[i] <<" largezze "<< larg<<" < "<<larghezze[i] <<" altezze " <<alt<<" < "<<altezze[i]<<" cazzofo "<<sadcof<<endl;
			sadcof+=matrioska(lunghezze[i], larghezze[i], altezze[i],lunghezze,larghezze,altezze);
			cout<<"after "<<lung<<"<"<<lunghezze[i] <<" largezze "<< larg<<" < "<<larghezze[i] <<" altezze " <<alt<<" < "<<altezze[i]<<" cazzofo "<<sadcof<<endl;
		}
		
		if(sadcof>maxcof) maxcof=sadcof;
		sadcof=1;
	}
	/*for(unsigned i=0;i<coffin.size();i++){
		cout<<" coffin "<<coffin[i];
		}
	cout<<"fine matrioska"<<maxcof<<" altra ";*/
	/*for(unsigned i=0;i<coffin.size();i++)
		if(coffin[i]>maxcof) maxcof=coffin[i];*/
	//cout<<maxcof<<endl;	
	return maxcof;
}

int main(){
	unsigned numele,auxcof,maxi;
	unsigned auxlung,auxlarg,auxprof;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		maxi=1;
		input>>numele;
		vector<unsigned> lunghezze,larghezze,altezze;
		vector<unsigned short> cofanetti;
		for(unsigned i=0;i<numele;i++){
			input>>auxlung>>auxlarg>>auxprof;
			lunghezze.push_back(auxlung);
			larghezze.push_back(auxlarg);
			altezze.push_back(auxprof);
		}
		for(unsigned i=0;i<numele;i++){
			cout<<"nuovoooo"<<endl;
			auxcof=matrioska(lunghezze[i],larghezze[i],altezze[i],lunghezze,larghezze,altezze);//cout<<auxcof<<endl;
			cofanetti.push_back(auxcof);
		}
		
		
		for(unsigned i=0;i<cofanetti.size();i++){
				cout<<cofanetti[i]<<" ";
		}
		for(unsigned i=0;i<cofanetti.size();i++){
			if(maxi<cofanetti[i])
				maxi=cofanetti[i];
		}
		cout<<endl;	
		cout<<endl;
		cout<<endl<<maxi<<endl;
		//output<<cofanetti<<endl;
	}
	
}
