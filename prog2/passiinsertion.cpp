#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
	unsigned numarr,passi;
	int auxnum;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		passi=0;
		input>>numarr;
		vector<int> inserarr;
		for(unsigned i =0;i<numarr;i++){
			input>>auxnum;
			inserarr.push_back(auxnum);
			}
		int j,numb;
   		for (unsigned i=1; i<numarr; i++){
       		numb=inserarr[i];
       		j=i-1;
       		while (j>= 0 && inserarr[j] > numb){
           		inserarr[j+1]=inserarr[j];
           		j=j-1;
           		passi++;
       		}
       		inserarr[j+1]=numb;
   		}
		output<<passi<<endl;   	 
	}
	output<<endl;
}
