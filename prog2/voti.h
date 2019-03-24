#include <iostream>

using namespace std;

/*
	Stack: funzioni e variabili locali.
	Heap: variabili dinamiche.
	int * pi;
	pi=new int; //allocazione dinamica quando ho già il puntatore.
*/
	
class contatore{
	public:
		contatore() {conto=1;}
		void incrementa(){conto++;}
		int legge_conto(){return conto;}
	private:
		int conto;
};

class rettangolo{
	public:
		double area(){
			return base*altezza;
		}
		void modifica(double Alt, double Base){
			altezza=Alt;
			base=Base;
		}
		void stampa(){
			cout << "La base è " << base << endl;
			cout << "L'altezza è " << altezza << endl;
		}
	private:
		double altezza;
		double base;
};

int main(){
	rettangolo r;
	double area;
	r.modifica(5,7);
	area=r.area();
	cout << "L'area del rettangolo è " << area << endl;
	r.stampa();
	contatore c1, c2;
	cout << "c1=" << c1.legge_conto() << "\tc2=" << c2.legge_conto() << endl;
}
