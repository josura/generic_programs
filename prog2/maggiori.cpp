#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

int main(){
	int numele,mini,aux;
    vector<int> maggiori;
	ifstream input("input.txt");              //input (1).txt
	ofstream output("output.txt");              //output.txt
	while(!input.eof()){
        maggiori.clear();
		input>>numele>>mini;
		for(unsigned i=0;i<numele;i++){
            input>>aux;
            if(aux>mini){
                maggiori.push_back(aux);
            }
        }
        output<<maggiori.size()<<" ";
        for(unsigned i=0;i<maggiori.size();i++){
            output<<maggiori[i]<<" ";
        }
        output<<endl;
		
	}
	
}