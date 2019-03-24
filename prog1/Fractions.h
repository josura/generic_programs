#ifndef FRACTIONS_H
#define FRACTIONS_H

#include<iostream>
#include<cmath>

using namespace std;

template <typename T> class Fraction;
template <typename T> ostream& operator<<(ostream& os,const Fraction<T>& rhs);
template <typename T> istream& operator>>(istream& is, Fraction<T>& dt); 

template <typename T> Fraction<T> operator+(const T& sx,const Fraction<T>& dx); 
template <typename T> Fraction<T> operator-(const T& sx,const Fraction<T>& dx);         //these operators overloading could be implemented outside the class, without friendship
template <typename T> Fraction<T> operator*(const T& sx,const Fraction<T>& dx);
template <typename T> Fraction<T> operator/(const T& sx,const Fraction<T>& dx);

template<typename T> class  Fraction  {
	private:
		T numer, denomin;
	public:
		Fraction();
		Fraction(T num);
		Fraction(T num,T den);
		~Fraction();
		T GCD(const T& num1,const T& num2) const;                           //greatest common divisor
		T LCM(const T& num1,const T& num2) const;					        //least common multiple
//overloading for Fractions
		Fraction<T> operator+(const Fraction<T>& rhs);
  		Fraction<T>& operator+=(const Fraction<T>& rhs);
  		Fraction<T> operator-(const Fraction<T>& rhs);
  		Fraction<T>& operator-=(const Fraction<T>& rhs);
  		Fraction<T> operator*(const Fraction<T>& rhs);
  		Fraction<T>& operator*=(const Fraction<T>& rhs);
		Fraction<T> operator/(const Fraction<T>& rhs);
		Fraction<T>& operator/=(const Fraction<T>& rhs);
		bool operator==(const Fraction<T>& rhs);
		bool operator!=(const Fraction<T>& rhs);
		bool operator<(const Fraction<T>& rhs);
		bool operator<=(const Fraction<T>& rhs);  	
		bool operator>(const Fraction<T>& rhs); 
		bool operator>=(const Fraction<T>& rhs); 	
//overloading for Fractions and costants
		Fraction<T> operator+(const T& rhs);
  		Fraction<T> operator-(const T& rhs);
  		Fraction<T> operator*(const T& rhs);
  		Fraction<T> operator/(const T& rhs);
		bool operator==(const T& rhs);
		bool operator!=(const T& rhs);
		bool operator<(const T& rhs); 
		bool operator<=(const T& rhs); 
		bool operator>(const T& rhs);   	
		bool operator>=(const T& rhs);   
//methods
		T getNum() const;
		T getDenum() const;
		void setNum(const T& rhs);
		void setDenum(const T& rhs);
		Fraction<T> inverse() const;
//overloading stream operators
		friend ostream& operator<< <> (ostream& os,const Fraction<T>& rhs);
		friend istream& operator>> <> (istream& is, Fraction<T>& dt);
		/*friend Fraction<T> operator+ <> (const T& sx,const Fraction<T>& dx); 
		friend Fraction<T> operator- <> (const T& sx,const Fraction<T>& dx);         //these operators overloading could be implemented outside the class, without friendship
		friend Fraction<T> operator* <> (const T& sx,const Fraction<T>& dx);
		friend Fraction<T> operator/ <> (const T& sx,const Fraction<T>& dx);	
		*/	  		
};

#include "Fraction.cpp"

#endif
