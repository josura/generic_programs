#include<iostream>

/*template <typename Type>
Type **BuildMatrix(int rows, int cols){
	Type**mat=new Type*[rows];
	for(int i=0; i<rows;i++)
		mat[i]=new Type[cols];            //altrimenti every other number will do the work
}*/

int **BuildMatrix(int rows, int cols){
	int**mat=new int*[rows];
	for(int i=0; i<rows;i++)
		mat[i]=new int[cols];            //altrimenti every other number will do the work

int main()
{ 
   int righe=3;
   int colonne = 4;  
   int **matrice;// puntatore doppio

   // la seguente implementazione crea dinamicamente la matrice riga per riga,
   // ed è totalmente diversa dalla rappresentazione 
   // classica delle matrici in C/C++
    
   matrice = BuildMatrix(righe, colonne);
   matrice[1][2]=0;
   StampaMatrice(matrice, righe, colonne); 
   EliminaMatrice(matrice, righe);
   
   system("PAUSE");    // ns. comodo!
   return EXIT_SUCCESS;
} // End main()
