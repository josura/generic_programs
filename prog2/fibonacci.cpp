#include<iostream>
#include<fstream>
#include<vector>

using namespace std;



inline unsigned int fibonacci_iterativo (int n){
				  int i = 0;
				  int j = 1;
				  for (int k = 1; k < n; k++)
				  {	
					int temp;
					temp = i + j;
					i = j;
					j = temp;
				  }

	return j;
	
}

main(){
	int auxnum;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
			input>>auxnum;
			output<<fibonacci_iterativo(auxnum)<<endl;
	}
	
}
