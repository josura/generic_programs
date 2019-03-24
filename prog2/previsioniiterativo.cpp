#include<iostream>
#include<fstream>
#include<vector>


using namespace std;


main(){
	unsigned numgiorni,periodo;
	string str1,str2,strinv,Psx3,s,final;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numgiorni>>periodo;
		final=str2=strinv="";
		Psx3="P S S ";
		if(numgiorni+periodo>=1){
			for(unsigned i=0;i<numgiorni+periodo && str2.size()<=(numgiorni+periodo)*2;i++){
				if(i>1)str1=str2; else str1=Psx3;
				s=Psx3;
				for(unsigned j=0;j<i;j++)
					s+="S ";
				strinv=s+str1;
				str2=str1+strinv;	
			}
		} else str2=Psx3;
		if(numgiorni==8)
		cout<<str2<<endl;
		for(unsigned i=(numgiorni)*2;i<(numgiorni+periodo)*2;i++){
				final+=str2[i];
		}
		output<<final<<endl;
	}
}
