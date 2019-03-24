#ifndef FRACTION_CPP
#define FRACTION_CPP

#include "Fractions.h"

// Parameter Constructor 
template<typename T>
Fraction<T>::Fraction():numer(0),denomin(1) {}

template<typename T>
Fraction<T>::Fraction(T num):numer(num),denomin(1) {}

template<typename T>
Fraction<T>::Fraction(T num,T den):numer(num),denomin(den) {}

//destructor
template<typename T>
Fraction<T>::~Fraction(){}

//functions
template<typename T>
T Fraction<T>::GCD(const T& num1,const T& num2) const{
	return abs(num2 == 0 ? num1 : GCD(num2, num1 % num2));
}

template<typename T>
T Fraction<T>::LCM(const T& num1,const T& num2) const{
	return (abs(num1*num2)/GCD(num1 , num2));
}

//overloading operator
template<typename T>
Fraction<T> Fraction<T>::operator+(const Fraction<T>& rhs){
	T shit= (numer*(LCM(denomin,rhs.getDenum())/denomin)+(rhs.numer*(LCM(rhs.getDenum(),denomin)/rhs.getDenum())));
	T fuck= LCM(denomin,rhs.getDenum());
	T why=GCD(shit,fuck);
	shit=shit/why;
	fuck=fuck/why;
	Fraction sum(shit,fuck);
	return sum;
}

template<typename T>
Fraction<T>& Fraction<T>::operator+=(const Fraction<T>& rhs){
	*this= *this+rhs;                     //i don't know if this will work
	return *this;
}

template<typename T>
Fraction<T> Fraction<T>::operator-(const Fraction<T>& rhs){
	T sx= (numer*(LCM(denomin,rhs.getDenum())/denomin)-(rhs.numer*(LCM(rhs.getDenum(),denomin)/rhs.getDenum())));
	T dx= LCM(denomin,rhs.getDenum());
	T why=GCD(sx,dx);
	sx=sx/why;
	dx=dx/why;
	Fraction sott(sx,dx);
	return sott;
}

template<typename T>
Fraction<T>& Fraction<T>::operator-=(const Fraction<T>& rhs){
	*this= *this-rhs;                     //i don't know if this will work
	return *this;
}

template<typename T>
Fraction<T> Fraction<T>::operator*(const Fraction<T>& rhs){
	T sx= (numer/(GCD(numer,rhs.getDenum()))*(rhs.getNum()/(GCD(rhs.getNum(),denomin))));
	T dx= (denomin/(GCD(denomin,rhs.getNum()))*(rhs.getDenum()/(GCD(rhs.getDenum(),numer))));
	Fraction mult(sx,dx);
	return mult;
}

template<typename T>
Fraction<T>& Fraction<T>::operator*=(const Fraction<T>& rhs){
	*this= (*this)*rhs;                     //i don't know if this will work
	return *this;
}

template<typename T>
Fraction<T> Fraction<T>::operator/(const Fraction<T>& rhs){
	T sx= (numer/(GCD(numer,rhs.getNum()))*(rhs.getDenum()/(GCD(rhs.getDenum(),denomin))));
	T dx= (denomin/(GCD(denomin,rhs.getDenum()))*(rhs.getNum()/(GCD(rhs.getNum(),numer))));
	Fraction divi(sx,dx);
	return divi;
}

template<typename T>
Fraction<T>& Fraction<T>::operator/=(const Fraction<T>& rhs){
	*this= (*this)/rhs;                     //i don't know if this will work
	return *this;
}

template<typename T>
bool Fraction<T>::operator==(const Fraction<T>& rhs){
	return(numer == rhs.getNum() && denomin==rhs.getDenum());
}

template<typename T>
bool Fraction<T>::operator!=(const Fraction<T>& rhs){
	return (numer != rhs.getNum() && denomin!=rhs.getDenum());
}

template<typename T>
bool Fraction<T>::operator<(const Fraction<T>& rhs){
	float a=(numer/denomin),b=(rhs.getNum()/rhs.getDenum());
	return(a<b);
}

template<typename T>
bool Fraction<T>::operator<=(const Fraction<T>& rhs){
	float a=(numer/denomin),b=(rhs.getNum()/rhs.getDenum());
	return(a<b || (*this==rhs));
}

template<typename T>
bool Fraction<T>::operator>(const Fraction<T>& rhs){
	float a=(numer/denomin),b=(rhs.getNum()/rhs.getDenum());
	return(a>b);
}

template<typename T>
bool Fraction<T>::operator>=(const Fraction<T>& rhs){
	float a=(numer/denomin),b=(rhs.getNum()/rhs.getDenum);
	return((*this==rhs) || a>b);
}

//overloading operators of costants
template<typename T>
Fraction<T> Fraction<T>::operator+(const T& rhs){
	T up= numer+(rhs*denomin);
	T down= denomin;
	T why=GCD(up,down);
	up=up/why;
	down=down/why;
	Fraction sum(up,down);
	return sum;
}

template<typename T>
Fraction<T> Fraction<T>::operator-(const T& rhs){	
	T up= numer-(rhs*denomin);
	T down= abs(denomin);
	T why=GCD(up,down);
	up=up/why;
	down=down/why;
	Fraction sott(up,down);
	return sott;
}

template<typename T>
Fraction<T> Fraction<T>::operator*(const T& rhs){
	T up= numer*(rhs/GCD(rhs,getDenum()));
	T down= denomin/GCD((rhs,getDenum()));
	Fraction mult(up,down);
	return mult;
}

template<typename T>
Fraction<T> Fraction<T>::operator/(const T& rhs){
	T up= numer/GCD(rhs,getNum());
	T down= denomin*(rhs/GCD(rhs,getNum()));
	Fraction divi(up,down);
	return divi;
}

template<typename T>
bool Fraction<T>::operator==(const T& rhs){
	return(numer == rhs && denomin==1);
}
template<typename T>
bool Fraction<T>::operator!=(const T& rhs){
	return (numer != rhs && denomin!=1);
}

template<typename T>
bool Fraction<T>::operator<(const T& rhs){
	float a=(numer/denomin);
	return(a<rhs);
}

template<typename T>
bool Fraction<T>::operator<=(const T& rhs){
	float a=(numer/denomin);
	return(a<rhs || (*this==rhs));
}

template<typename T>
bool Fraction<T>::operator>(const T& rhs){
	float a=(numer/denomin);
	return(a>rhs);
}

template<typename T>
bool Fraction<T>::operator>=(const T& rhs){
	float a=(numer/denomin);
	return((*this==rhs) || a>rhs);
}

//other methods
template<typename T>
T Fraction<T>::getNum() const{
	return this->numer;
}

template<typename T>
T Fraction<T>::getDenum() const{
	return this->denomin;
}

template<typename T>
void Fraction<T>::setNum(const T& rhs) {
	numer=rhs;
}

template<typename T>
void Fraction<T>::setDenum(const T& rhs) {
	denomin=rhs;
}

template<typename T>
Fraction<T> Fraction<T>::inverse() const{
	T up= denomin;
	T down= numer;
	Fraction inv(up,down);
	return inv;
}

template<typename T>
ostream& operator << (ostream& os,const Fraction<T>& rhs){
	if(rhs.numer==0 || rhs.denomin==1)
		os<<rhs.getNum();
	else
		os<<rhs.numer<<"/"<<rhs.denomin;	
	return os;
}

template<typename T>
istream& operator>> (istream& is, Fraction<T>& dt){  
    is>> dt.numer;
    if(dt.numer!=0)
		is>> dt.denomin;
	else 
		dt.setDenum(1);	  
    return is;  
}  

/*
template<typename T>
Fraction<T> operator+ (const T& sx,const Fraction<T>& dx){
	Fraction sum();
	sum.numer= dx.numer+(sxdenominm);
	sum.denomin= denomin;
	return sum;
}

template<typename T>
Fraction<T> operator- (const T& sx,const Fraction<T>& dx){
	Fraction sott();
	sott.numer= dx.numer-(sx*denomin);
	sott.denomin= denomin;
	return sott;
}

template<typename T>
Fraction<T> operator* (const T& sx,const Fraction<T>& dx){
	Fraction mult();
	mult.numer= dx.numer*(sx/(GCD(sx,dx.denomin)));
	mult.denomin= denomin/(GCD(sx,dx.denomin));
	return mult;
}

template<typename T>
Fraction<T> operator/ (const T& sx,const Fraction<T>& dx){
	Fraction divi();
	divi.numer= dx.numer/(GCD(sx,dx.numer)));
	divi.denomin= denomin/(sx/(GCD(sx,dx.numer)));
	return divi;
}
*/
template<typename T>
Fraction<T> operator+ (const T& sx,const Fraction<T>& dx){
	T num= dx.getNum()+(sx*dx.getDenum());
	T denom= dx.getDenum();
	T why=dx.GCD(num,denom);
	num=num/why;
	denom=denom/why;
	Fraction<T> sum(num,denom);
	return sum;
}

template<typename T>
Fraction<T> operator- (const T& sx,const Fraction<T>& dx){
	T num= (sx*dx.getDenum())-dx.getNum();
	T denom= dx.getDenum();
	T why=dx.GCD(num,denom);
	num=num/why;
	denom=denom/why;
	Fraction<T> sott(num,denom);
	return sott;
}

template<typename T>
Fraction<T> operator* (const T& sx,const Fraction<T>& dx){
	T num= dx.getNum()*(sx/(dx.GCD(sx,dx.getDenum())));
	T denom= dx.getDenum()/(dx.GCD(sx,dx.getDenum()));
	Fraction<T> mult(num,denom);
	return mult;
}

template<typename T>
Fraction<T> operator/ (const T& sx,const Fraction<T>& dx){
	T num= dx.getNum()/(dx.GCD(sx,dx.getNum()));
	T denom= dx.getDenum()/(sx/(dx.GCD(sx,dx.getNum())));
	Fraction<T> divi(num,denom);
	return divi;
}

#endif
