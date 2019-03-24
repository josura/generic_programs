/*Scrivere un metodo che prenda in input due array A e B di int di lunghezza n ed m rispettivamente,
e restituisca una matrice di dimensione nxm di int contenente il prodotto AxB se in A tutti gli
elementi sono distinti e la matrice identità altrimenti.*/


#include <iostream>
#include <cstdlib>

#define l 4

float ** crossProduct(float* arrA,float* arrB,int n,int m)
{  
   float **m=new float*[rows]; 
   for (int i=0;i<rows;++i)  
       m[i]=new float[cols];  
   for (int i=0;i<rows;++i)
   {
      for (int j=0;j<cols;++j)
      {
         if(n);
      }
   }
   return m;
}

template<typename T>
void DeleteMatrix (T **m, int rows)
{
   for (int i=0;i<rows;++i)   
       delete [] m[i];        
   delete [] m;                   
}

template<typename T>
void print_matrix(T **matrix, int h, int w)
 {
         if(!w) w = h;
         for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                        std::cout << matrix[i][j] << '\t';
                }
                std::cout << "\n";
         }
 }


