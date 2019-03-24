#include <iostream>

using namespace std;

/* 
	g(n)=4n^3 + 3n^2
	O(n^3)
	f(n)=n^3
	g(n)<=4(n^3 + 3n^3)=7n^3
	c=7, n0=1
	Per ogni n più grande di 1,
	4n^3 + 3n^2 <= 7n^3
	Devono esistere queste costanti.
	5n^2 + 3nlog(n) + 2n + 5 <= 5n^2 + 3n^2 + 2n^2 + 5n^2 = 15n^2
	f(n)=n^2
	Per c=15 e n0=1,
	5n^2 + 3nlog(n) + 2n + 5 <= 15n^2
	La procedura del calcolo di potenze, per quanto riguarda lo spazio dell'input, è esponenziale (2^n). La complessità è
	dell'ordine di n. Per ridurla:
	
	int power(int x, int n){
		if (n==0) return 1;
		else if (n%2==1) return x*power(x,(n-1)/2)^2
		else if (n%2==0) return x*power(x,n/2)^2
		
	x^24 = (x^12)^2=((x^6)^2)^2=(((x^6)^2)^2)^2=((((x^3)^2)^2)^2)^2=((((x*x*x)^2)^2)^2)^2
	Quest'algoritmo, sia in termini di spazio che di tempo ha complessità log(n). Log(n) chiamate ricorsive. Invoco la funzione
	power su un esponente che è la metà dell'esponente iniziale, e ancora a metà e così via. Questa procedura arriva ad uno, 
	quando ha fatto un numero tale di passi per cui 2^k = n; klog(2) = log(n) -> k = log(n);
	
	Banca 1: qualunque sia il capitale che investo, mi aggiunge 200 euro a fine anno
	Se ho un investimento iniziale di 100 euro, la formula è 100+200k, in cui k è il numero di anni
	Banca 2: Interesse del 20% ogni anno su quello che ho investito
	Primo anno - 100+20%(100 euro)= 100*1,2
	Secondo anno - 100*1,2 + 20%(100*1,2)=100*1,2+0,2*100*1,2=100*1,2(1+0,2)=100*(1,2)^2
	Dopo k anni, 100*(1,2)^k
	anni: 		1		2		3		4		5		10		20		30		50
	Banca 1:   300	500	 700	 900	1100	2100	 4100	 6100	10100
	Banca 2:	144	173	 207	 207	 249	 619	 3833	 23738  910044
	
	Abbiamo un array di interi che possono essere sia positivi che negativi, determiniamo il segmento di valore massimo.
	Avevamo proposto una soluzione che prendeva come limite sinistro un indice i, limite destro un indice j e faceva variare
	questi due indici; un terzo indice che aveva il compito di valutare il massimo.
	
	sommamassima1(int *a, int n){
		int max = 0;
		int somma = 0;
		for(int i=0; i<n; i++){
			for(j=i; j<n; j++){
				somma = 0;
					for(int k=i; k<=j; k++){
						somma += a[k];
					if(somma>max) max=somma;
					}
			}
		return max;
		}
	}
	
	Se tutti i cicli fossero andati n volte, uno ripete il precedente n volte etc quindi sarebbe stato n^3.
	sommatoria(i=0...n-1)sommatoria(j=i...n-1)sommatoria(k=i...j)t = sommatoria(i=0...n-1)sommatoria(j=i...n-1)(j-i+1)t=
	=t * sommatoria(i=0...n-1)sommatoria(j=i...n-1)(j-i-1)    Per j=i, l'argomento vale 1; per j=n-1, n-i. Sto sommando, quindi,
	i numeri compresi fra 1 ed n-i quindi è la formula di Gauss.
	t*sommatoria(i=0...n-1)sommatoria(j=1...n-i)j = t*sommatoria(i=0...n-1)((n-i)(n-i-1))/2
	Siccome noi siamo fighi, togliamo tutte le costanti, anche quelle dentro la sommatoria.
	=circa sommatoria(i=0...n-1) (n-i)^2= sommatoria(i=1...n) i^2
	Questa è la somma dei quadrati dei primi n interi.
	sommatoria(i=1...n) i^2 = (n(n+1)(2n+1))/6
	Questo è ordine di n^3.
	
	Una volta che io ho trovato il valore della somma del segmento i, j-1, non ripartiamo da capo per la somma del segmento i, j
	
	sommamassima2(int *a, int n){
		int max = 0, somma = 0;
		for(int i=0; i<n; i++){
			somma = 0;
			for(int j=i; j<n; j++){
				somma += a[j];
				if (somma>max) max = somma;
			}
		}
		return max;
	}
	
	In un segmento di somma massima, tutte le sue componenti iniziali devono essere positive; se fosse negativo, basterebbe
	togliere un segmento che contiene numeri negativi. Quando scorro l'array, appena trovo una componente negativa la tolgo
	e non la dovrò guardare più e non potrà contribuire ad un segmento di somma massima.
	
	sommamassima3(int *a, int n){
		int max = 0, somma = max;
		for(int j=0; j<n; j++){
			if(somma>0){
				somma += a[j];
			}
			else{
				somma = a[j];
			}
			if(somma>max) max = somma;	
		}
		return max;
	} 
	Questa soluzione ha complessità O(n), dal punto di vista asintotico è il meglio che posso fare.
*/