#include<string>
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

static const char pool[]=
 	"abcdefghilmnopqrstuwxyz";
int poolsize= sizeof(pool)-1;

char getRandomChar(){
	return pool[rand()% poolsize];
} 	

string random_string(int lenght){
	string str;
	for (int i =0; i<lenght; i++){        //se non funziona devo trasportare la funzione all'interno del void sotto
		str+=getRandomChar();
	}
	return str;
}

string * BuildArray(int rows,int lenght)
{  
   srand(time(0));
   string *m=new string[rows];  
   for (int i=0;i<rows;++i)
   {
         m[i]=random_string(lenght);
   }
   return m;
}

bool vocale(char a){
	return (a=='a' || a=='e' || a=='i' || a=='o' || a=='u');
}

bool aa(string *S, int dim){ 
	string x = string(); int vocali = 0, consonanti = 0;
	for (int i=1; i<dim; i=i+2){
		for(int j=0; j<S[i].length(); j=j+2){
			x += S[i][j];
		}
		cout<<x;
	}
	for (int q=0; q<x.length(); q++){
		if (vocale(x[q])) vocali++;
		else consonanti++;
	}
return (vocali>consonanti);
}

int main(){
	int dim = 5;
	string *arr=BuildArray(6,dim);
	cout<<aa(arr,dim);
	return 0;
}
