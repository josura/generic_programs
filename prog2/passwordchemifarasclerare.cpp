#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

string puliziaztringa(string parolona){
	unsigned counter=0;
	string finallad="";
	for(unsigned i=0;i<parolona.size();i++){
		counter=0;
		for(unsigned j=0;j<parolona.size();j++){
			if(parolona[i]==parolona[j] && i!= j){
				counter++;
			}
		}
		
		if(counter>=1){
			finallad+=parolona[i];
		}	
	}
	return finallad;
}

string stringabeast(string parolona,int range){
	string aux,auxinterna,finalona;
		for(int i=0;i>parolona.size()-range;i++){
			for(unsigned j=0;j<4;j++){
				for(unsigned k=0;k<4-j && j+i+k+2<parolona.size() && j+i+k+range<parolona.size();k++){
					aux=parolona.substr(i,i+j)+parolona.substr(j+i+1,j+i+k+1)+parolona.substr(j+i+k+2,j+i+k+range+2)
					for(int l=j+i+k+range+2;l>parolona.size()-range;l++){
						for(unsigned f=0;f<4;f++){
							for(unsigned x=0;x<4-f && f+l+x+2<parolona.size() && f+l+x+range<parolona.size();x++){
								auxinterna=parolona.substr(l,l+f)+parolona.substr(f+l+1,f+l+x+1)+parolona.substr(f+l+x+2,f+l+x+range+2)
								if(aux==auxinterna) finalona=aux;
							}
						}
					}
				}
			}
		}
	return finalona;	
}

string parole(string parolona, unsigned shit,unsigned& occorrenze){
	unsigned counter,countermax=1;
	string madlad,finallad="";
	for(unsigned i=0;i<parolona.size()-shit;i++){
		counter=1;
		madlad=parolona.substr(i,shit);
		for(unsigned j=i+shit;j<parolona.size()-shit;j++){
			if(madlad==parolona.substr(j,shit)){
				counter++;
			}
		}
		if(counter>countermax){
			countermax=counter;
			finallad=madlad;
		}	
	}
	occorrenze=countermax;
	return finallad;
}

string parolerange(string parolona, int range,unsigned shit){
	unsigned counter,auxcounter=0,countermax=1,indice;
	vector<unsigned> occorrenze;
	string madlad,finallad="",veraparola=parolona;
	cout<<endl<<parolona;
	for(unsigned i=1;i<parolona.size()-range && shit-i>1 ;i++){
		madlad=parole(parolona,shit-i,counter);
		occorrenze.push_back(counter);
			
	}
	for(unsigned i=0;i<occorrenze.size()-1;i++){
		counter=0;
		for(unsigned j=i;j<occorrenze.size() && occorrenze[i]>1;j++){
			if(occorrenze[i]==occorrenze[j]) counter++;
		}
		if (counter>auxcounter) {
			auxcounter=counter;
			countermax=occorrenze[i];
		}	
		}
		cout<<countermax<<endl;
	for(unsigned i=1;i<parolona.size()-range && shit-i>1 ;i++){
		madlad=parole(parolona,shit-i,counter);
		cout<<madlad;
		if(madlad!="" && counter>=countermax){
			countermax=counter;
			range+=-madlad.size();
			indice=parolona.find(madlad);
			cout<<"\n\n ciao"<<finallad<<"\n\n";
			parolona.erase(indice,madlad.size());
			if(range>=0)
				finallad+=madlad;
			i+=-1;
		}
			
	}
	parolona=veraparola;
	/*if(range>0){
			for(unsigned i=0;i<parolona.size()-(shit+1) ;i++){
				indice=parolona.find()
			}
		}
	}*/
	cout<<" ciao "<<parolona<<endl;
	return finallad;
}


int main(){
	unsigned numinu,numpass,ciao;
	string paroli,password,aux;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		unsigned l=1;
		input>>numinu>>numpass;
		input>>paroli;
		password=parole(paroli,numpass,ciao);
		//aux=puliziaztringa(paroli);
		//cout<<paroli<<endl<<aux<<endl;
		if(password.size()<numpass ){
			//cout<<parolerange(paroli,numpass,numpass)<<endl;
			if(password.size()<parolerange(paroli,numpass,numpass).size())
				password=parolerange(paroli,numpass,numpass);
			l++;
		}
		if(password.size()<numpass ){
			//cout<<parolerange(paroli,numpass,numpass)<<endl;
			if(password.size()<parolerange(paroli,numpass,numpass).size())
				password=parolerange(paroli,numpass,numpass);
			l++;
		}
		cout<<password<<endl<<endl;
		/*for(unsigned i=0;i<numele;i++){
			cout<<fascicolidiso[i]<<" ";
		}
		cout<<endl;
		for(unsigned i=0;i<numele;i++){
			cout<<fascicoli[i]<<" ";
		}
		cout<<endl;*/
		
		
		//cout<<endl<<maxi<<endl;
		//output<<cofanetti<<endl;
	}
	
}
