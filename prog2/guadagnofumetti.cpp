#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

main(){
	int numfum,gaspmoney,auxnum,numguadagno;
	//bool doppioni=false;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		vector<int> numeri;
		numguadagno=0;
		input>>numfum>>gaspmoney;
		for(int i =0;i<numfum;i++){
			input>>auxnum;
			numeri.push_back(auxnum);		
		}
		for(int i =0;i<gaspmoney;i++){
			//doppioni=false;
			input>>auxnum;
			for(unsigned j=0;j<=numeri.size() ;j++)//&& !doppioni
				if(numeri[j]==auxnum){
					numguadagno+=5;
					//doppioni=true;
				}
		}
		output<<numguadagno<<endl;
	}
	
}
