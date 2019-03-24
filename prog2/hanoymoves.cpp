#include<iostream>
#include<fstream>

using namespace std;

void towers(unsigned& moves,ofstream& output,unsigned cercamove,int num, char frompeg, char auxpeg, char topeg){
	if(moves==cercamove){
    	towers( moves, output, cercamove, num-1, frompeg,  topeg,  auxpeg);
        output << frompeg << " " << topeg << endl;
        towers( moves, output, cercamove, num-1, auxpeg,  frompeg,  topeg);
        return;
	}
    if( num > 0 ) 
    {
    	moves++;
        towers( moves, output, cercamove, num-1, frompeg,  topeg,  auxpeg);
        cout << frompeg << "->" << topeg << endl;
        towers( moves, output, cercamove, num-1, auxpeg,  frompeg,  topeg);
    }
}

int main(){
	unsigned numdisks,nummove;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		unsigned moves=0;
		input>>numdisks>>nummove;
		towers(moves,output,nummove,numdisks,'1','2','3');
	}
}
