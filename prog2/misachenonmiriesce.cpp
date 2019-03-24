#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


string cercapassword(string parolona,unsigned range){
	string aux,finalona;
	bool uscita=false;
	unsigned space1,space2,counter,ind1,ind2;
	cout<<parolona<<endl;
		for(unsigned i=0;i<parolona.size()-range && !uscita;i++){
			//indicefuori=i;
			for(unsigned j=i+1;j<parolona.size() && !uscita;j++){
				space1=space2=0;
				counter=0;
				if(parolona[i]==parolona[j]){ind1=i+1;
					aux=parolona[i];
					cout<<i<<parolona[i]<<" =O= "<<j<<parolona[j]<<" | ";
					while(!uscita && space1<=4){
						space2=space1;
						ind2=j+1;
						while(space2<=4 && aux.size()<range){
							cout<<ind1<<parolona[ind1]<<" == "<<ind2<<parolona[ind2]<<" | ";
							if(parolona[ind1]==parolona[ind2]){
								cout<<space2<<space1<<aux<<" -> ";
								aux+=parolona[ind2];ind1++;ind2++;
								cout<<aux<<" | ";
							}
							else if(parolona[ind1]!=parolona[ind2]){
								ind2++;space2++;
							}		
						}
						if(counter<=4 && aux.size()!=range){
							counter++;
							finalona=parolona[i];
							ind1=i+counter;
							space1=space2=counter;
						}else if(aux.size()==range){
						finalona=aux;
						uscita=true;
						} else finalona="";
						//if(finalona.size()!=range)
							//finalona=parolona[];
					}	
				}
			}
		}
	return finalona;	
}

string stringabeast(string parolona,int range){
	string aux,auxinterna,finalona;
	
	cout<<parolona<<endl;
		for(unsigned i=0;i<parolona.size()-range-4;i++){
			for(unsigned j=0;j<range;j++){
				for(unsigned k=1;k<4 ;k++){
					if(i!=0 && j!=0) aux=parolona.substr(i,i+j)+parolona.substr(j+i+1,j+i+k+1)+parolona.substr(j+i+k+2,j+i+range-2);
					else aux=parolona[0]+parolona.substr(j+i+1,i+k+1)+parolona.substr(j+i+k+2,j+i+range-2);
					cout<<aux<<" ";
					for(unsigned l=j+i+k+range-1;l<parolona.size()-range;l++){
						for(unsigned f=0;f<4;f++){
							for(unsigned x=0;x<4-f && f+l+x+2<parolona.size() && f+l+x+range-2<parolona.size();x++){
								auxinterna=parolona.substr(l,l+f)+parolona.substr(f+l+1,f+l+x+1)+parolona.substr(f+l+x+2,f+l+x+range-2);
								if(aux==auxinterna) finalona=aux;
							}
						}
					}
				}
			}
		}
	return finalona;	
}

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

/*string stringaragno(string parolona,int range, string final){
	int indice=parolona.find(final.substr(0,1));
	string aux,littleword=final.substr(0,1);
		for(int i=indice;i>indice-4 && indice-i>=0;i--){
			if(indice-i>=0){
				aux=parolona[indice-i]+final;
			}
			for()
		}
}*/

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

/*string parolerange(string parolona, int range,unsigned shit){
	unsigned counter,auxcounter=0,countermax=1,indice;
	vector<unsigned> occorrenze;
	string madlad,finallad="",veraparola=parolona;
	//cout<<endl<<parolona;
	for(unsigned i=1;i<parolona.size()-range && shit-i>1 ;i++){
		madlad=parole(parolona,shit-i,counter);
		occorrenze.push_back(counter);
		cout<<counter<<" ";	
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
		cout<<"ci"<<countermax<<endl;
	for(unsigned i=2; shit-i>1 ;i++){
		madlad=parole(parolona,i,counter);
		if(madlad!="")
		cout<<madlad<<counter<<"perchè"<<countermax<<endl;
		if(madlad!="" && counter==countermax || counter==countermax+1){
			
			
			indice=parolona.find(madlad);
			cout<<"\n\n ciao"<<finallad<<"\n\n";
			cout<<endl<<parolona<<endl;
			parolona.erase(indice,madlad.size());
			cout<<parolona<<endl;
			cout<<" ciaoneeee "<<range<<endl;
			if(range>=0 && range-madlad.size()>1){
				range+=-madlad.size();
				finallad+=madlad;
			}
			i+=-1;
		}
			
	}
	parolona=veraparola;
	if(range>0){
			for(unsigned i=0;i<parolona.size()-(shit+1) ;i++){
				indice=parolona.find(parolona.substr(0,1));
				if(indice!=std::string::npos){
					
				}
			}
	}
	//cout<<" ciao "<<parolona<<endl;
	return finallad;
}*/


int main(){
	unsigned numinu,numpass,ciao;//,cie=0
	string paroli,password,aux;
	ifstream input("input (2).txt");
	ofstream output("output.txt");
	while(!input.eof() ){
		input>>numinu>>numpass;
		input>>paroli;
		password=parole(paroli,numpass,ciao);
		if(password.size()<numpass ){
			password=cercapassword(paroli,numpass);
		}
		cout<<endl<<endl<<password<<endl<<numpass<<endl;
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
