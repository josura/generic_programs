#include<iostream>
#include<cstdlib>
#include<string>
#include<time.h>

using namespace std;

static const char pool[]=
 	"abcd";
int poolsize= sizeof(pool)-1;

char getRandomChar(){
	return pool[rand()% poolsize];
} 	

void rand_str(int lenght){
	string str;
	for (int i =0; i<lenght; i++){
		str+=getRandomChar();
	}
	cout<<str<<endl;
	str="";
}

int main(){
	while(true){
		int lenght;
		srand(time(0));
		cout<<"enter the lenght of the string";
		cin>>lenght;
		rand_str(lenght);
		if (lenght==0)
		return false;
	}
}
