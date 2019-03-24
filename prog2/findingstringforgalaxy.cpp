#include<iostream>
#include<fstream>

using namespace std;

int main(){
	unsigned numpar;
	string datro,cercare;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numpar>>datro;
		for(unsigned i =0;i<numpar;i++){
			input>>cercare;
			if (cercare.find(datro) != string::npos) {
				output<<cercare<<" ";
			} 
		}
		output<<endl;
	}
}
