#include<iostream>
#include<cmath>
#include<stdlib.h>
#include <cstring>
#include<vector> 
using namespace std;

double square(double x){
	return x*x
}
void print_square(double x){
	cout<<"the square of "<<x<<" is "<<square(x)<<"\n";
}
int main(){
	double x;
	char c[4];
	do {
	system("cls");
		cout <<"write a number ";
		cin>>x;
 		print_square(x);
 		cout<<"repeat yes/no";
 		cin.getline(c,4);
 		switch (c){
 			case 'yes':
 				accept=1;
 			case 'no':
			 	accept=0;
			default:
				cout<<"i'll take that for a no";
			 	accept=0;
		 } while (accept!=false ) 
}
}
