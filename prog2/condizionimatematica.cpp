#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

main(){
	unsigned num1,num2,n=1;
	int counter;
	bool falso;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		counter=0;
		input>>num1>>num2;
		cout<<n++<<") "<<num1<<" "<<num2<<endl;
		falso=true;
		while(((num1!=1 && num2!=1)||(num1==1 && num2!=1)||(num1!=1 && num2==1)) && falso ){
			if((num1%2)==0 && (num2%2)==0){
				num1/=2;
				num2/=2;
			}
			else if((num1%2)!=0 && (num2%2)!=0){
				num1=num1*3+1;
				num2=num2*3+1;
			}
			else if((num1%2)!=0 && (num2%2)==0){
				num1+=3;}
			else if(((num2%2)!=0 && (num1%2)==0)){
				num2+=3;}
				counter++;
			if(counter>=100){
				counter=-1;
				falso=false;
			}		
		}
		output<<counter<<endl;
		
	}	
}
