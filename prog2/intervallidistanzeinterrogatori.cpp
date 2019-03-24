#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

#define INTERV finis[i]-starts[i]
													//5 7 16 17 25 10 17 0 8 11 20
													//5 7 12 17 21 10 13 0 4 11 16 
using namespace std;


int Distanza(int coso1,int coso2){
	return abs(coso2-coso1);
}

bool tuttuguali(vector<int>& shit){
	unsigned contatore=0;
	for(unsigned i=0;i<shit.size()-2;i++){
		if(Distanza(shit[i],shit[i+1])==Distanza(shit[i+2],shit[i+1]))
			contatore++;
	}
	if(contatore==shit.size()-2)
		return true;
	else return false;	
}

int minimo(vector<int>& coso){
	int mini=abs(coso[1]-coso[0]);
	for(unsigned i=1;i<coso.size()-1;i++){
		
		if(abs(coso[i+1]-coso[i])<mini) mini=abs(coso[i+1]-coso[i]);
		
	}
	//cout<<"mini"<<mini<<"  ";
	return mini;
}

int valoremax(int coso1,int coso2){
	return (coso1+coso2-1);
}

void incrementonocout(vector<int>& finali,vector<int>& possincrem,int distanzina){
	for(unsigned i=0;i<finali.size()-1;i++){
		if(valoremax(finali[i],possincrem[i])>valoremax(finali[i+1],possincrem[i+1])){
					swap(finali[i],finali[i+1]);
					swap(possincrem[i],possincrem[i+1]);
					while(finali[i]>finali[i+1]){
						finali[i+1]+=1;
						possincrem[i+1]--;
					}
					i=0;
					if(i>0) i+=-1;
					else if(i>1)i+=-2;
				}	
		if(Distanza(finali[i],finali[i+1])<=distanzina){
			if(i<finali.size()-2){
				if(possincrem[i+1]>0 && possincrem[i+2]>0 && ((Distanza(finali[i],finali[i+1])<=Distanza(finali[i+1],finali[i+2])) )){                 //&&  (Distanza(finali[i],finali[i+1])<Distanza(finali[i+1],finali[i+2]))    
					finali[i+1]+=1;
					possincrem[i+1]--;
				}
			}
			else if(possincrem[i+1]>0)	{
					finali[i+1]+=1;
					possincrem[i+1]--;
			}
		}
	}
}

void incremento(vector<int>& finali,vector<int>& possincrem,int distanzina){
	cout<<distanzina<<" ahah"<<endl;
	for(unsigned i=0;i<finali.size()-1;i++){
		if(finali[i]==finali[i+1]){
			if(possincrem[i]>possincrem[i+1]){
			 swap(possincrem[i],possincrem[i+1]);
			 i=0;}
		}
		else if(i>0 && finali[i-1]==finali[i]){
			if(possincrem[i-1]>possincrem[i]){
			 swap(possincrem[i-1],possincrem[i]);
			 i=0;}
		}	
		if(finali[i]>finali[i+1]){
			swap(finali[i],finali[i+1]);
			swap(possincrem[i],possincrem[i+1]);
			 i=0;
		}	
		else if(valoremax(finali[i],possincrem[i])>valoremax(finali[i+1],possincrem[i+1])+1 ){
			//if(i>0 && Distanza(finali[i-1],finali[i])>1){
						swap(finali[i],finali[i+1]);
						swap(possincrem[i],possincrem[i+1]);
					//cout<<"risono dentro"<<finali[i]<<"->"<<possincrem[i]<<" to "<<finali[i+1]<<"->"<<possincrem[i+1];
						int distanza=Distanza(finali[i],finali[i+1]),k=0;
						while(k<distanza){
							finali[i+1]+=1;
							possincrem[i+1]--;
							k++;
						}
					//}
		}
		if(Distanza(finali[i],finali[i+1])<=distanzina){
			
			if(i<finali.size()-2){cout<<" dinstanza cazzo "<<Distanza(finali[i],finali[i+1])<<" sclero "<<distanzina<<"cazo"<<Distanza(finali[i+1],finali[i+2]);
				if(possincrem[i+1]>0 && possincrem[i+2]>0 &&  ( Distanza(finali[i],finali[i+1])<=Distanza(finali[i+1],finali[i+2]))){                 //&&  (Distanza(finali[i],finali[i+1])<Distanza(finali[i+1],finali[i+2]))    
				//	cout<<" ciao finale "<<finali[i+1]<<"->"<<possincrem[i+1]<<" to ";
					finali[i+1]+=1;
					possincrem[i+1]--;
					cout<<finali[i+1]<<"->"<<possincrem[i+1]<<endl;
					/**/if(finali[i+1]==finali[i+2]){
						if(possincrem[i+1]>possincrem[i+2]){
							cout<<"scancio"<<possincrem[i+1]<<" ->"<<possincrem[i+2];
					 		swap(possincrem[i+1],possincrem[i+2]);
						}
					}
					else if(i>=1 && finali[i-1]==finali[i]){
						if(possincrem[i-1]>possincrem[i]){
							cout<<"cancio "<<possincrem[i-1]<<" <-"<<possincrem[i];
					 	swap(possincrem[i-1],possincrem[i]);}
					}
					//cout<<" ciaone finale "<<finali[i+1]<<"->"<<possincrem[i+1]<<endl;
				}
			}
			else if(possincrem[i+1]>0)	{
				//cout<<" ciao finalone "<<finali[i+1]<<"->"<<possincrem[i+1]<<" to ";
					finali[i+1]+=1;
					possincrem[i+1]--;
					cout<<finali[i+1]<<"->"<<possincrem[i+1]<<endl;
					if(finali[i-1]==finali[i]){
						if(possincrem[i-1]>possincrem[i]){
							cout<<"cancio "<<possincrem[i-1]<<" <-"<<possincrem[i];
					 	swap(possincrem[i-1],possincrem[i]);}
					}
			}
		}
	}
	for(unsigned i=0;i<finali.size();i++){
			cout<<"("<<finali[i]<<"->"<<possincrem[i]<<") ";
	}
	cout<<endl<<endl;
}

void incrementocheriesce(vector<int>& finali,vector<int>& possincrem,int distanzina){
	cout<<distanzina<<" ahah"<<endl;
	for(unsigned i=0;i<finali.size()-1;i++){
		if(finali[i]==finali[i+1]){
			if(possincrem[i]>possincrem[i+1]){
			 swap(possincrem[i],possincrem[i+1]);
			 i=0;}
		}
		else if(i>0 && finali[i-1]==finali[i]){
			if(possincrem[i-1]>possincrem[i]){
			 swap(possincrem[i-1],possincrem[i]);
			 i=0;}
		}	
		if(finali[i]>finali[i+1]){
			swap(finali[i],finali[i+1]);
			swap(possincrem[i],possincrem[i+1]);
			 i=0;
		}	
		if(Distanza(finali[i],finali[i+1])<=distanzina){
			
			if(i<finali.size()-2){cout<<" dinstanza cazzo "<<Distanza(finali[i],finali[i+1])<<" sclero "<<distanzina<<"cazo"<<Distanza(finali[i+1],finali[i+2]);
				if(possincrem[i+1]>0 && possincrem[i+2]>0 &&  ( Distanza(finali[i],finali[i+1])<=Distanza(finali[i+1],finali[i+2]))){                 //&&  (Distanza(finali[i],finali[i+1])<Distanza(finali[i+1],finali[i+2]))    
					cout<<" ciao finale "<<finali[i+1]<<"->"<<possincrem[i+1]<<" to ";
					finali[i+1]+=1;
					possincrem[i+1]--;
					//cout<<finali[i+1]<<"->"<<possincrem[i+1]<<endl;
					/**/if(finali[i+1]==finali[i+2]){
						if(possincrem[i+1]>possincrem[i+2]){
							cout<<"scancio"<<possincrem[i+1]<<" ->"<<possincrem[i+2];
					 		swap(possincrem[i+1],possincrem[i+2]);
						}
					}
					else if(i>=1 && finali[i-1]==finali[i]){
						if(possincrem[i-1]>possincrem[i]){
							cout<<"cancio "<<possincrem[i-1]<<" <-"<<possincrem[i];
					 	swap(possincrem[i-1],possincrem[i]);}
					}
					if(i>1) i+=-2;
					//cout<<" ciaone finale "<<finali[i+1]<<"->"<<possincrem[i+1]<<endl;
				}
			}
			else if(possincrem[i+1]>0)	{
				//cout<<" ciao finalone "<<finali[i+1]<<"->"<<possincrem[i+1]<<" to ";
					finali[i+1]+=1;
					possincrem[i+1]--;
					cout<<finali[i+1]<<"->"<<possincrem[i+1]<<endl;
					if(finali[i-1]==finali[i]){
						if(possincrem[i-1]>possincrem[i]){
							cout<<"cancio "<<possincrem[i-1]<<" <-"<<possincrem[i];
					 	swap(possincrem[i-1],possincrem[i]);}
					}
			}
		}
	}
	for(unsigned i=0;i<finali.size();i++){
			cout<<"("<<finali[i]<<"->"<<possincrem[i]<<") ";
	}
	cout<<endl<<endl;
}


int main(){
	unsigned numele,iniz,fine,ges=0;
	int mindist,minicoso1,mindo;
	ifstream input("input (2).txt");
	//ofstream output("output.txt");
	while(!input.eof()){
		input>>numele;
		if(ges>=1) return 0;
		ges++;
		
		vector<int> starts,finis,distanze,intervalli,stafin,auxsta,auxint;
		for(unsigned i=0;i<numele;i++){
			input>>iniz>>fine;
			starts.push_back(iniz);
			finis.push_back(fine);
			cout<<iniz<<" "<<fine<<" ";
		}
		cout<<endl;
    	int j;
   		int numb,numb1;
   		for (unsigned i=1; i<starts.size(); i++){
       	numb=starts[i];
       	numb1=finis[i];
       	j=i-1;
       	while (j>= 0 && starts[j] > numb){
           	starts[j+1]=starts[j];
           	finis[j+1]=finis[j];
           	j=j-1;
       	}
       	starts[j+1]=numb;
       	finis[j+1]=numb1;
   		}
   		for(unsigned i=0;i<numele-1;i++){
			if(starts[i]==starts[i+1])
				if(finis[i]>finis[i+1]) swap(finis[i],finis[i+1]);
		}  
    	for(unsigned i=0;i<numele;i++){
			stafin.push_back(starts[i]);
		}
		cout<<endl;
		for(unsigned i=0;i<numele;i++){
			intervalli.push_back(INTERV);
			cout<<"("<<starts[i]<<"->"<<INTERV<<") ";
		}
		starts=auxsta=stafin;
		finis=auxint=intervalli;
		fine=0;
		mindo=0;
		while(fine<50){
			if(mindo<minimo(starts)) mindo=minimo(starts);
			incrementonocout(starts,finis,mindo);
			fine++;
		}
		fine=0;
		mindist=minicoso1=0;
		while(mindist<mindo && fine<15){
			//cout<<endl<<fine<<")"<<endl;
			incrementocheriesce(auxsta,auxint,mindist);
			//if(mindist>minicoso1) cout<<fine<<")"<<endl; 
			mindist=minimo(auxsta);
			fine++;
		}
		fine=0;
		mindist=minicoso1=0;
		cout<<"mindo "<<mindo<<endl;
		while(mindist<mindo && fine<15){
			//cout<<endl<<fine<<")"<<endl;
			incremento(stafin,intervalli,mindist);
			//if(mindist>minicoso1) cout<<fine<<")"<<endl; 
			mindist=minimo(stafin);
			fine++;
		}
		cout<<endl<<endl;
		for(unsigned i=0;i<numele;i++){
			cout<<auxsta[i]<<" ";
		}
		cout<<endl;
		for(unsigned i=0;i<numele;i++){
			cout<<stafin[i]<<" ";
		}
		cout<<endl<<endl;
		//output<<maxi<<endl;
	}
	
}
