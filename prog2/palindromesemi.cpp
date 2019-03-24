#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

main(){
	int numstr,numerovero,numerofalzo,numpalindrome;
	string str;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		//vector<string> numeri;
		vector<string> palindromi;
		numpalindrome=0;
		input>>numstr;
		for(int i =0;i<numstr;i++){
			numerovero=0;
			input>>str;
			cout<<str.size()/2-1<<endl;
			//numeri.push_back(str);
			for(unsigned j=0;j<str.size()/2;j++){
				if(str[j]==str[str.size()-1-j])
					numerovero++;	
			}
			cout<<"numerovero"<<numerovero<<endl;
			if(numerovero>=(str.size()/2-1)){
				palindromi.push_back(str);
				numpalindrome++;
			}
		}
		output<<numpalindrome<<" ";
		for(unsigned i=0;i<palindromi.size();i++)
			output<<palindromi[i]<<" ";
		output<<endl;	
	}
	
}
