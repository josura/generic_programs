#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
	unsigned numele,aux;
	ifstream input("input.txt");              //input (1).txt
	ofstream output("output.txt");              //output.txt
	while(!input.eof()){
		input>>numele;
		for(unsigned i=0;i<numele;i++){
			input>>aux;
            if((aux%2)!=0)
			output<<aux<<" ";
		}
        output<<endl;
		
	}
	
}
