#include<iostream>
#include<cstdlib>
#include<time.h>
#include<stdlib.h>
#include<windows.h>

using namespace std;


int main(){
	char c = 'y';
	do{
	int dado=0;
	int lanci=0;
	int lanci_tot=0;
	int set=0;
	srand(time(0));
	
	while (set<5){
	while(dado!=2)
	{
		int aux=rand()% 6;
		dado=(aux )+1;
		cout<<" "<<dado<<" ";
		lanci++;
	}
	cout<<endl;
	lanci_tot+=lanci;
	set++;
	lanci=0;
	dado=0;
}
	cout<<" lanci effettuati : "<<lanci_tot;
	Sleep(2000);
 	cout<<endl<<"\n Giochi ancora d'azzardo'"<<endl<<" y/n:\n";
 	cin>>c;
 } while (c== 'y');
	return 0;
}
