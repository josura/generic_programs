#include<iostream>
#include<cmath>
#include<stdlib.h>
#include <string> 
using namespace std;

double square(double x){
	return x*x;
}
void print_square(double x){
	cout<<"the square of "<<x<<" is "<<square(x)<<"\n";
}
int main(){
	double x;bool hey=false;	
	do {	
	system("cls"); 
		cout <<"write a number ";
		cin>>x;
 		print_square(x);
 		char c;
 		cout<<"continue y/n: ";
 		cin>>c;
 		switch (c){
 			case 'y':
 				hey=true;
 				break;
 			case 'n':
			 	hey=false;
			 	break;
			default:
			 	hey=false;
		 }} while (hey==true);
 return 0;
}
