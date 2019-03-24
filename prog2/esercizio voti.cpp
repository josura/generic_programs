#include <iostream>
#include "voti.cpp"

using namespace std;

#define MAX 100

int main(){
	Voti voti;
	bool flag=1;
	cout<< "Inserisci i voti(e un numero negativo per terminare): ";
	do{
		double voto;
		cout << "-- "; cin >> voto;
		if(voto<0) flag=0;
		else voti.inserisci(voto);
	} while(flag);
	double media=voti.media_voti();
	cout<<"La media dei voti è " << media << endl;
	return 0;
}
