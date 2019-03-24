#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

#define INTERV finis[i]-starts[i]

using namespace std;

int valoremax(int coso1,int coso2){
	return (coso1+coso2-1);
}

int Distanza(int coso1,int coso2){
	return abs(coso2-coso1);
}

int minimo(vector<int>& coso){
	int mini=abs(coso[1]-coso[0]);
	for(unsigned i=1;i<coso.size()-1;i++){
		if(abs(coso[i+1]-coso[i])<mini) mini=abs(coso[i+1]-coso[i]);
	}
	return mini;
}

void incremento(vector<int>& finali,vector<int>& possincrem,int distanzina){
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
				else if(valoremax(finali[i],possincrem[i])>valoremax(finali[i+1],possincrem[i+1])+3 ){
					if(i>0 && Distanza(finali[i-1],finali[i])>3){
						swap(finali[i],finali[i+1]);
						swap(possincrem[i],possincrem[i+1]);
					//cout<<"risono dentro"<<finali[i]<<"->"<<possincrem[i]<<" to "<<finali[i+1]<<"->"<<possincrem[i+1];
						int distanza=Distanza(finali[i],finali[i+1]),k=0;
						while(k<distanza){
							finali[i+1]+=1;
							possincrem[i+1]--;
							k++;
						}
					}
				}		
		if(Distanza(finali[i],finali[i+1])<=distanzina){
			if(i<finali.size()-2){
				if(possincrem[i+1]>0 && possincrem[i+2]>0 && ( Distanza(finali[i],finali[i+1])<=Distanza(finali[i+1],finali[i+2]))){                 //&&  (Distanza(finali[i],finali[i+1])<Distanza(finali[i+1],finali[i+2]))    
					finali[i+1]+=1;
					possincrem[i+1]--;
					if(finali[i+1]==finali[i+2]){
						if(possincrem[i+1]>possincrem[i+2]){
					 		swap(possincrem[i+1],possincrem[i+2]);
						}
					}
					else if(i>=1 && finali[i-1]==finali[i]){
						if(possincrem[i-1]>possincrem[i]){
					 	swap(possincrem[i-1],possincrem[i]);}
					}
					if(i>1) i+=-2;
				}
			}
			else if(possincrem[i+1]>0)	{
					finali[i+1]+=1;
					possincrem[i+1]--;
					if(finali[i-1]==finali[i]){
						if(possincrem[i-1]>possincrem[i]){
					 	swap(possincrem[i-1],possincrem[i]);}
					}
			}
		}
	}
}


int main(){
	unsigned numele,iniz,fine;
	int mindist,minicoso,mindo;
	ifstream input("inputcrassssimo.txt");              //input (1).txt
	ofstream output("outputcrassissi.txt");              //output.txt
	while(!input.eof()){
		input>>numele;
		vector<int> starts,finis,distanze,intervalli,stafin;
		for(unsigned i=0;i<numele;i++){
			input>>iniz>>fine;
			starts.push_back(iniz);
			finis.push_back(fine);
		}
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
		/*unsigned min_idx;
     	for (unsigned i = 0; i < starts.size()-1; i++){
        min_idx = i;
        for (unsigned j = i+1; j < starts.size(); j++)
          if (starts[j] < starts[min_idx])
            min_idx = j;
	    swap(starts[min_idx], starts[i]);
	    swap(finis[min_idx], finis[i]);
    	}*/
    	for(unsigned i=0;i<numele;i++){
			stafin.push_back(starts[i]);
		}
		for(unsigned i=0;i<numele;i++){
			intervalli.push_back(INTERV);
		}
		starts=stafin;
		finis=intervalli;
		fine=0;
		mindo=0;
		while(fine<100){
			if(mindo<minimo(starts)) mindo=minimo(starts);
			incremento(starts,finis,mindo);
			fine++;
		}
		fine=0;
		mindist=minicoso=0;
		cout<<mindo<<endl;
		while(mindist<mindo && fine<100){
			incremento(stafin,intervalli,mindist);
			mindist=minimo(stafin);
			fine++;
		}
		for(unsigned i=0;i<numele;i++){
			output<<stafin[i]<<" ";
		}
		output<<endl;
		cout<<endl<<endl;
		
	}
	
}
