#include "MAZZO.h"
#include "CARTA.h"
#include<string>

Mazzo::Mazzo()
:tot(QUAN)
{
	unsigned char facce[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	string seme[] = {"Oro", "Bastoni", "Spade", "Coppe"};
	mazzo = new Carta[QUAN];
	cartaCorrente = 0;
	for(int count = 0; count < QUAN; count++){
		mazzo[count] = Carta(facce[count % 10], seme[count / 10]);
	}
}

Mazzo::Mazzo(int quan)
:tot(quan){
	unsigned char facce[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	string seme[] = {"Oro", "Bastoni", "Spade", "Coppe"};
	mazzo = new Carta[tot];
	cartaCorrente = 0;
	for(int count = 0; count < tot; count++){
		mazzo[count] = Carta(facce[count % 10], seme[count / 10]);
	}
}

void Mazzo::mescola(){	
	cartaCorrente = 0;
	for(int carta1 = 0; carta1 < tot; carta1++){
		int carta2 = (rand() + time(0)) % quan;
		Carta temp = mazzo[carta1];
		mazzo[carta1] = mazzo[carta2];
		mazzo[carta2] = temp;
}
}

Carta Mazzo::estrai(){
	Carta c;
	if(tot>0){
		c=mazzo[0];
		for(int i=1;i<tot;i++){
			mazzo[i-1]=mazzo[i];
		}
		tot--;
	}
	else{
		cerr<<"carte finite";
	}
	return c;
}

void Mazzo::inserisci(Carta c){
	if (tot==QUAN)
	cerr<<"mazzo completo";
	else{
		mazzo[tot]=c;
		tot++;
	}
}

int Mazzo::getNum(){
	return tot;
}

bool Mazzo::vuoto(){
	return (tot==0) ? true : false;
}

