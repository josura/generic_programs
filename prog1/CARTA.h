#ifndef CARTA_H
#define CARTA_H
#include<string>
class Carta
{
	public:
			static const string ORO="Oro";
			static const string BASTONI="Bastoni";
			static const string SPADE="Spade";
			static const string COPPE="Coppe";
		Carta();
		Carta( unsigned char val,string figu);
		bool operator==(const Carta& other) const;
		bool operator<(const Carta& other) const;
		string seme;
		unsigned char numero; 
};

#endif
