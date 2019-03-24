#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

main(){
	int numfum,numfum2,auxnum;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		vector<int> numeri;
		input>>numfum;
		input>>numfum2;
		for(int i =0;i<numfum;i++){
			input>>auxnum;
			numeri.push_back(auxnum);		
		}
		for(int i =0;i<numfum2;i++){
			input>>auxnum;
			numeri.push_back(auxnum);
		}
		int numb, j;
   			for (int i = 1; i <(numfum+numfum2); i++){
       			numb = numeri[i];
       			j = i-1;
       			while (j >= 0 && numeri[j] > numb){
           			numeri[j+1] = numeri[j];
           			j=j-1;
       			}
       			numeri[j+1] = numb;
   			}
		for(unsigned i =0;i<numeri.size();i++){
			output<<numeri[i]<<" ";		
		}
		output<<endl;
	}
	
}
