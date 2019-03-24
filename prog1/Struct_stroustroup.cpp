#include<iostream>

struct Vector{
	int sz;  //numero di elementi
	double* elem;    //puntatore a elementi
};

void vector_init(Vector& v, int s){
	v.elem = new double[s];
	v.sz=s
}

double read_sum(int s){
	Vector v;
	vector_init(v,s);
	for(int i=0; i!=s;++i)
		sum+=v.elem[i];
	return sum;	
}

void f(Vector v, Vector& rv, Vector* pv){
	int i1=v.sz     //accesso tramite nome
	int i2=rv.sz    //accesso tramite riferimento
	int i3=pv->sz   //accesso tramite puntatore
}

