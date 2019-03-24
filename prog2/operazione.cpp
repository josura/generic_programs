#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

int main(){
	int n, num1, num2, risultato;
	string numero;
	ifstream input("input.txt");              //input (1).txt
	ofstream output("output.txt");              //output.txt
	while(!input.eof()){
		input >> n;
		for(int j=0; j<n; j++){
			input >> numero;
			for(int i=0; i<numero.length(); i++){
				if(numero[i]=='+'|| numero[i]=='-' || numero[i]=='*'){
					num1 = atoi((numero.substr(0,i)).c_str());
					num2 = atoi((numero.substr(i+1)).c_str());
					//cout << "num1: " << num1 << endl << "num2: " << num2 << endl;
					if(numero[i]=='+'){
						risultato=num1+num2;
					}
					else if(numero[i]=='-'){
						risultato=num1-num2;
					}
					else if(numero[i]=='*'){
						risultato=num1*num2;
					}
					output << risultato << " ";
				}
			}
		}
		output << endl;
	}
	
}