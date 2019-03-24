#ifndef MAZZO_H
#define MAZZO_H
#include "CARTA.cpp"

const int QUAN=40;

class Mazzo
{
	public:
		Mazzo();
		Mazzo(int quan);
		void mescola();
		Carta estrai();
		void inserisci(Carta c);
		int getNum();
		bool vuoto();
	private:
		int tot;
		Carta mazzo[tot]; 
};

#endif
