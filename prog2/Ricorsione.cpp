#include <iostream>

using namespace std;

void A(int);
void B(int);

void A(int c){
	if (c>5) B(c);
	cout << c << "  ";
}

void B(int c){
	A(--c);
}

int MCD(int m, int n){
	if((n<=m) && (m%n==0)) return n;
	else if (m<n) return MCD(n,m);
	else return MCD(n,m%n);
}

int Calcola_MCD(int m, int n) {
	int a=m, b=n, aux;
	while(b!=0){
		aux=b;
		b=a%aux;
		a=aux;
	}
	return a;
}

int MCD_iterativo(int m, int n){
	int output;
	if(m>n) output=Calcola_MCD(n,m);
	else output=Calcola_MCD(n,m);
	return output;
}

void Hanoi(char iniziale, char centrale, char finale,int n1){
	if(n1==1) cout << "Muovo il disco 1 dal piatto " << iniziale << " al piatto " << finale << endl;
	else{
		Hanoi(iniziale,finale, centrale, n1-1);
		cout << "Muovo il disco " << n1 << " dal piatto " << iniziale << " al piatto " << finale << endl;
		Hanoi(centrale, iniziale, finale, n1-1);
	}
}

int main(){
	A(25);
	unsigned int m, n;
	int n1;
	cout << "\nInserire due interi positivi ";
	cin >> m >> n;
	if(cin.fail()) cout << "Fai schifo, ritirati!" <<endl;
	cout << "\nIl MCD è: " << MCD(m,n) << endl;
	cout << "E invece, calcolato iterativamente..." << MCD_iterativo(m,n) << endl;
	cout << "Inserire un numero di dischi: ";
	cin >> n1;
	Hanoi('A','B','C',n1);
	return 0;
}

/*A(5) non farà più chiamata ricorsiva, e fa la cout; conclusa questa, ritorna a B(6), poi B(7), poi B(8) etc. Fa la pop di continuo.
A(25), viene sospeso e invoca B(25), che si ferma e invoca B(24)...A(5) è il primo che finisce, stampa 5 e 
comunicherà alla procedura chiamante, B(6), che ha finito. A(6) scrive 6 e avrà finito, e restituirà il controllo alla procedura che
l'aveva chiamata che è B(7), poi A(7) che stampa 7 etc. La procedura chiamante(A(25) è quella che dà l'ordine di stackare.)
Lo stack è tipo una pila di magliette, A(25), B(25) etc dal basso verso l'alto 

Hanoi: Calcolare il numero di spostamenti.
numspostamenti(n)=2*numspostamenti(n-1)+1
= 2^n - 1 */