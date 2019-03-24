#include<fstream>
#include<cstdlib>
#include<iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;
int main(){
	ifstream read;
	ofstream write;
	int a, b;
	unsigned contatore, n;
	string output;
	read.open("input.txt");
	if (read.fail())
	{
		cout<< "Apertura input.txt fallita!\n";
		exit(1);
	}
	write.open("output.txt");
	if(write.fail())
	{
		cout << "Non sono riuscito a scrivere l'output.txt!'\n";
		exit(1);
	}
	while(!read.eof()){
		contatore = 0;
		n = 0;
		read >> a >> b;
		while((a!=1 && b!=1) || (a!=1 && b==1) || (a==1 && b!=1)){
			if(a%2==0 && b%2==0){
				a/=2;
				b/=2;
			}
			else if(a%2==1 && b%2==1){
				a=a*3+1;
				b=b*3+1;
			}
			else{
				if(a%2==1){
					a+=3;
				}
				else b+=3;
			}
			contatore++;
			cout << "a: " << a << "  b: " << b << endl;
			if (contatore>100){
				contatore = -1;
				break;
			}
		}
		write << contatore << endl;
	}
	read.close();
	write.close();
	return 0;
}
