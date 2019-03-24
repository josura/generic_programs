#include "CARTA.h"
#include<string>
Carta::Carta(){
}

Carta::Carta(unsigned char val,string figu)
:numero(val),seme(figu)
{
	if (val<1 || val>10)
		cerr<<"carte strane che vanno fuori gli schemi";
	else
		numero=val;
	if (seme!=ORO || seme!=BASTONI || seme!=SPADE || seme!=COPPE)
		cerr<<"diventa joker perche' fuori dagli schemi";
		seme="joker";
	else
		seme=figu;		
}

const string Carta::GetCard(){
	string str;
	switch(numero){
		case 1: str="asso di ";
		break;
		case 2: str="due di ";
		break;
		case 3: str="tre di ";
		break;
		case 4: str="quattro di ";
		break;
		case 5: str="cinque di ";
		break;
		case 6: str="sei di ";
		break;
		case 7: str="sette di ";
		break;
		case 8: str="donna di ";
		break;
		case 9: str="cavallo di ";
		break;
		case 10: str="re' di ";
		break;
		cerr<<"lo faccio passare come joker \n";
		default : str="joker ";
		break;		
	}
	
	switch(seme){
		case ORO: str+="ori";
		break;
		case BASTONI: str+="bastoni";
		break;
		case SPADE: str+="spade";
		break;
		case COPPE: str+="coppe";
		break;
		case default: str+="nullo";
		break;
	}
	
}

string Carta::Getseme(){
	return seme;
}

unsigned char Carta::GetValore(){
	return numero;
}

bool Carta::compara(Carta b){
	return (b.GetValore()==GetValore);
}

bool Carta::operator==(const Carta& other) const{
	return (other.seme==seme && other.numero==numero);
}

bool Carta::operator<(const Carta& other) const{
	return std::tie(lhs.rank, lhs.suit) < std::tie(rhs.rank, rhs.suit);
}
