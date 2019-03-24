/* Ad una festa partecipa una star del cinema. La star ha le seguenti caratteristiche:
- tutti la conoscono;
- la star non conosce nessuno;
L'obbiettivo è di individuare la star chiedendo solo domande del tipo "Conosci lui (o lei)?"
1. Dimostrare che esiste una sola star.
2. Trovare una strategia per individuare la star.
3. Trovare una strategia che richieda un massimo di O(n) domande. */

#include <iostream>

using namespace std;

for(int i=0; i<=n; i++){
	contatore=0;
	for(int j=0; j<=n; j++){
		if(i!==j && conosce(i, j))) contatore++;
	if(contatore==n-1) star=i;
	}
}	//Complessità O(n^2)

star=1;
i=1;
for(int j=0, j<=n; j++)
	if(conosce(i,j)){
		star=j;
		i=j;
	}	 //Funziona o no? Complessità O(n)

//Metodo del prof: usare una stack di persone, pescarne due, chiedere ad A se conosce B: se è sì rimuovo A perché B può essere
//la star, se dice no rimuovo B perché A può essere la star(che non conosce nessuno). Rimetto la possibile star
//nello stack e ripeto. Complessità O(n).