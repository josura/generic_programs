#include <iostream>

using namespace std;

class Punto{
		double x, y;
	public:
		Punto(double xx, double yy): x(xx), y(yy)	{}
		double getX() {return x;}
		double getY() {return y;}
		void setX(double xx)	{x=xx;}
		void setY(double yy)	{y=yy;}
		Punto operator+(const Punto& p);
		Punto& operator+=(const Punto& p);
		Punto& operator++();	//++p
		Punto operator++(int); //p++
};

Punto Punto::operator+(const Punto& p){
	Punto temp(0.0,0.0);
	temp.x=x+p.x;
	temp.y=y+p.y;
	return temp;
}

Punto& Punto::operator+=(const Punto& p){
	x+=p.x;
	y+=p.y;
	return *this;
}

Punto& Punto::operator++(){
	x++;
	y++;
	return *this;
}

Punto Punto::operator++(int){
	Punto pp(x,y);
	++(*this);
	return pp;
}

ostream& operator<<(ostream& out, Punto& a){
	out <<	"Coordinata x: " << a.getX() << "\t Coordinata y: " << a.getY() << endl;
	return out;
}

int main(){
	Punto p1(3,4), p2(5,7), p(0,0);
	cout << "p1.x: " << p1.getX() << "\tp1.y: " << p1.getY() << endl;
	cout << "p1.x: " << p2.getX() << "\tp2.y: " << p2.getY() << endl;
	p++;
	cout << "p.x: " << p.getX() << "\tp.y: " << p.getY() << endl;
	cout << p;
	return 0;
}