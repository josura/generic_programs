#include <iostream>
#include <cstdlib>
#include<ctime>
#define RANDPLACE(matrix,cols,rows) (matrix[rand() % rows][rand() % cols])

short ** campo(int rows,int cols){  
   short **m=new short*[rows]; 
   for (int i=0;i<rows;++i)  
       m[i]=new short[cols];  
   for (int i=0;i<rows;++i)
   {
      for (int j=0;j<cols;++j)
      {
         m[i][j]=rand()%3;
      }
   }
   return m;
}

int buche(short ** mat, int rows,int cols){
	short pallina=mat[rows/2][cols/2];
	int punteggio=0;
	while(pallina!=1){
		if(pallina==2){
			std::cout<<"un punto, un altro uccello\n";
			punteggio++;
		}
		pallina=RANDPLACE(mat,cols,rows);
		if(pallina==0)
			std::cout<<"un altro tiro\n";		
	}
	std::cout<<"se vuoi puoi riprenderla, buttati nell'acqua";
	return punteggio;
}

void print_matrix(short **matrix, int h, int w)
 {
         if(!w) w = h;
         for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                        std::cout << matrix[i][j] << '\t';
                }
                std::cout << "\n";
         }
 }
 
 void DeleteMatrix (short **m, int rows)
{
   for (int i=0;i<rows;++i)   
       delete [] m[i];        
   delete [] m;                   
}
 
 int main(){
 	srand(time(0));
	short **matrix=campo(8,8);
	print_matrix(matrix,8,8);
	std::cout<<"\n\n numero buche:  "<<buche(matrix,8, 8);
	DeleteMatrix(matrix,8);
	return 0;
}
