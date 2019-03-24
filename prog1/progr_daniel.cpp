#include <iostream>
#include<stdio.h>
#include <cmath>
#include<windows.h>
using namespace std;
 int main()
 {
 
 	int i;
 	char x = 'y';
 	do {
	 	system("cls");
 	cout << "Hey, puzzone!"<<endl<<"Questo programma calcola la quantita' di seme emessa dal pistolino." << endl << "Inserisci la lunghezza in cm per continuare: ";
 	cin >> i;
 	if (i==0)
 	{
 		cout << "Sei una donna, e forse anche un po' eccitata";
 	}	
 		else if (i<=0)
 	{
 		cout << "Ti esce dal culo?";
 	}	
 		else if (i>0 && i<=7)
 	{
 		cout << "Sei un bambino ritardato o beh, e' piccolo. Facciamo 2 ml";
 	}
 		else if (i>7 && i<=15)
 	{
 		cout << "Dai, potrebbe essere peggio. 15 ml";
 	}
 		else if (i>15 && i<=20)
 	{
 		cout << "Sei una mucca. 2 litri";
 	}
 		else if (i>20 && i<=30)
 	{
 		cout << "Molto divertente, Rocco. Se fossi un vero programmatore a quest'ora ti starei gia' formattando il PC";
 	}
 		else if (i>30)
 	{ 
 		cout << "Un cavallo umano, vai a fare il porno attore, montagne di money";
		 }	
 	Sleep(3000);
 	cout<<endl<<"vorresti cambiare la dimensione del tuo pene ?"<<endl<<"y/n:\n";
 	cin>>x;
 } while (x== 'y');
 return 0;
 }

