#include<algorithm>
#include<iostream>
#include<string>
#include<cctype>
#include<fstream>
#include<vector>

using namespace std;

void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

unsigned factorial(unsigned n){
	unsigned factor=1;
	for(unsigned short i =1; i <=n; i++)
    {
        factor*=i;
    }
    return factor;
}

void permute(char* alfa, int l, int r,vector<string> out)
{
   	int i;
   	if (l == r) {
   		string aux="";
   		for(unsigned i=0;i<sizeof(alfa)/sizeof(alfa[0]);i++)
   			aux +=alfa[i];
   		out.push_back(aux);	
   		return;	
   	}
    else{
       for (i = l; i <= r; i++){
          swap((alfa+l), (alfa+i));
          permute(alfa, l+1, r,out);
          swap((alfa+l), (alfa+i));
       }
   }
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
		vector<char> alfabeto;//,alfabetodellawild
		vector<unsigned short> indice;
		//vector<string> combinazioni;
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
		char* alfabetodellawild=new char[indice.size()];
		unsigned dio=0;
		for(unsigned j=0;j<alfabeto.size() ;j++){
			entraalf=true;
			for(unsigned k=0;k<wildcard.size() && entraalf;k++){
				if(wildcard[k]==alfabeto[j]) entraalf=false;
			}
			if(entraalf) {alfabetodellawild[dio]=alfabeto[j];dio++;}
		}
		int n = sizeof(alfabetodellawild)/sizeof(alfabetodellawild[0]);
		sort(alfabetodellawild,alfabetodellawild+n);
		for(unsigned i=0;i<indice.size();i++){
			final[indice[i]]=alfabetodellawild[i];
		}
		//combinazioni.push_back(final);
		output<<final<<" ";
		vector<string> auxshit;
		permute(alfabetodellawild, 0, n-1,auxshit);
		for(unsigned i=0;i<factorial(indice.size())-1;i++){
			for(unsigned j=0;j<indice.size();j++){
				final[indice[j]]=auxshit[i][j];
			}
			//combinazioni.push_back(final);
			output<<final<<" ";
		}
		//sort(combinazioni.begin(),combinazioni.end());
		/*for(unsigned i=0;i<combinazioni.size();i++){
			output<<combinazioni[i]<<" ";
		}*/
		output<<endl;
		
	}	
}
