#include <iostream>

using namespace std;

/* 
	Numero spostamenti: NS(n) = 2NS(n-1)+1 
	NS(n)= 2^n - 1
	Dimostriamo per induzione.
	Caso base: n=1
	NS(1)= 2^1 - 1 = 1
	n=k
	NS(k)= 2^k - 1
	n=k+1
	NS(k+1)=2NS(k)+1=2(2^k - 1)+1=2^(k+1)-1 
	
	Costo nel caso peggiore: la complessità che ci interessa di più.
	Costo nel caso medio: costo mediato tra tutte le istanze della funzione aventi dimensioni pari ad n
	
	Calcoliamo il caso peggiore:
	if: Costo(guardia)+max(costo(blocco 1), costo(blocco 2)...costo(blocco n))
	for: sommatoria(i=0...m-1)(t di i), in cui t di i è il costo di corpo all'iterazione i
	while: sommatoria(i=0...m) (t' di i + t di i) in cui t' di i è il costo di guardia all'iterazione i, 
	t di i è il costo del corpo all'iterazione i
	Il costo di una funzione è dato dal costo del suo corpo (più il passaggio dei parametri)
	Il costo di una sequenza di istruzioni è la somma dei costi delle istruzioni nella sequenza
	Sn=1+a+a^2+...+a^n=
	Sn-1=a+a^2...a^n
	Sn-1=a(1+a+...a^n-1)
	Sn-1=a(Sn-a^n)
	Sn-aSn=1-a^(n+1)
	(1-a)Sn=1-a^(n+1)
	Sn=(a^(n+1)-1)/(a-1)
	Funzione quadratica: due cicli for annidati con i e j che vanno da 0 ad n; f(n)=cn^2
	sommatoria(i da 1 ad n)((sommatoria(j che va da 1 ad i)t))=sommatoria(i da 1 a n)(it)=
		=t(sommatoria(i da 1 ad n)(i))=t*(n(n+1)/2)= circa n^2
	Complessità 3 cicli annidati:
	for(int i=1; i<=n; i++)
		for(int j=1; j<=i; j++)
			for(int k=1; k<=j; k++)
				do_something();
	sommatoria(i=1...n)sommatoria(j=1...i)sommatoria(k=1...j)t=
	t*sommatoria(i=1...n)sommatoria(j=1...i)j=t*sommatoria(i=1...n)(i(i+1))/2=
	(t/2)*sommatoria(i(i+1))=(t/2)*sommatoria(i=1...n)(i^2)+sommatoria(i=1...n)i=
	=(t/2)*(((n*(n+1)(2n+1))/6)+(n(n+1))/2))=circa (t/2) n^3
	Notazione asintotica: le costanti sono irrilevanti. O(f(n)) limite superiore, 
	omega(f(n)) limite inferiore (ad esempio, un algoritmo di ricerca del massimo in a[n] deve fare almeno
	n passi); theta(f(n)) sse g(n)=O(f(n)) e f(n)=O(g(n))
	La comnplessità della versione ricorsiva della potenza è n semplicemente, perché moltiplo x se stesso n volte, in termini
	di spazio è dispendioso.
	Esiste un algoritmo per la potenza che riesce a fare meglio dell'ordine di n? O(n)
*/