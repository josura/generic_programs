#include <iostream>

using namespace std;

/*
	Pile
	Struttura LIFO, last in first out, ogni volta che inseriamo un elemento questo sarà il primo ad essere 
	cancellato. Operazione di inserimento push, di cancellazione pop.
	Una pila può essere realizzata con un array o una lista semplice. Se la pila è vuota dobbiamo fare
	in modo di non poter fare pop, viceversa se è piena. Indice per la cima della pila etc.
*/

enum stato_pila{OK, PIENA, VUOTA};

template <class T>

class Pila{
	public:
		Pila(int lung);
		~Pila() {delete [] tabella;}
		void Push(T);
		T Pop();
		void StampaPila();
		int PilaPiena();
		int PilaVuota();
		int num_elementi(){return cima+1;}
		int leggi_lunghezza(){return lunghezza;}
	private:
		T* tabella;
		int cima;
		int lunghezza;
		stato_pila stato;
};

template <class T> Pila <T> :: Pila(int lung){
	lunghezza=lung;
	cima=-1;
	tabella=new T[lunghezza];
	stato=VUOTA;
}
/*
int Pila::PilaPiena() {
	if(cima==(MaxDimPila-1)) return 1;
	else return 0;
}

int Pila::PilaVuota(){
	if(cima==-1) return 1;
	else return 0;
}
*/
	
template <class T> void Pila<T>::Push(T x){
	if(stato!=PIENA) tabella[++cima]=x;
	else cout << "Pila pienaaaaaaaaa! \n";
	if (cima==lunghezza-1) stato=PIENA;
	else stato=OK;
}

template <class T> T Pila<T>::Pop(){
	int elem = 0;
	if(stato!=VUOTA) {
		elem=tabella[cima--];
	}
	else cout << "Cazz estraggo, la pila e' vuota! \n";
	if(cima==-1) stato=VUOTA;
	else stato=OK;
	return elem;
}

template <class T> void Pila<T>::StampaPila(){
	if(stato==VUOTA) cout << "Cazz stampo, e' vuota. \n";
	else{
		for(int i=cima; i>=0; i--) cout << "Posizione " << i << " : " << tabella[i] << endl;
	}
}

int main(){
	Pila<int> stack(6);
	Pila<char> stack2(3);
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	cout << "Numero di elementi: " << stack.num_elementi() << endl;
	stack.StampaPila();
	cout << "Estrarre il primo: " << stack.Pop() << endl;
	cout << "Estrarre il secondo: " << stack.Pop() << endl;
	cout << "Estrarre il terzo: " << stack.Pop() << endl;
	cout << "Numero di elementi: " << stack.num_elementi() << endl;
	cout << "Estrarre il quarto: " << stack.Pop() << endl;
	cout << endl;
	stack2.Push('A');
	stack2.Push('B');
	stack2.Push('C');
	stack2.Push('D');
	cout << "Estrarre il primo: " << stack2.Pop() << endl;
	cout << "Estrarre il secondo: " << stack2.Pop() << endl;
	cout << "Estrarre il terzo: " << stack2.Pop() << endl;
	cout << "Numero di elementi: " << stack2.num_elementi() << endl;
	cout << "Estrarre il quarto: " << stack2.Pop() << endl;
	stack2.StampaPila();
	return 0;
}	