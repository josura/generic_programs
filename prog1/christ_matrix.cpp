#include <iostream>
#include<cstdlib>
#include<ctime> 
using namespace std;

int ** BuildMatrix(int rows,int cols)
{  
   int **m=new int*[rows]; 
   for (int i=0;i<rows;++i)  
       m[i]=new int[cols];  
   for (int i=0;i<rows;++i)
   {
      for (int j=0;j<cols;++j)
      {
         m[i][j]=rand()%15;
      }
   }
   return m;
}


void DeleteMatrix (int **m, int rows)
{
   for (int i=0;i<rows;++i)   
       delete [] m[i];        
   delete [] m;                   
}


inline void PrintMatrix(int **mat,int rows,int cols)
{
   for (int i=0;i<rows;++i)
   {
      for (int j=0;j<cols;++j)
      {
         cout<<mat[i][j]<<" ";
      }
      cout<<endl;
   }
}
bool cross(int **mat, int rows, int cols)
{
	int div;
	for(int i=1;i<rows-1;i++){
		for(int j=1;j<cols-1;j++){
			div=mat[i][j];
			if((mat[i][j-1] % div)==0 && (mat[i][j+1] % div)==0 && (mat[i-1][j] % (div-1))==0 && (mat[i+1][j] % (div-1))==0)
			return true;
		}
	}
	return false;
}

int main()
{ 
   srand(time(0));
   int rows=3;
   int cols = 4;  
   bool cristo;
   int **matrix;
   matrix = BuildMatrix(rows, cols);  
   matrix[1][2]=3;
   matrix[1][1]=matrix[1][3]=18;
   matrix[0][2]=matrix[2][2]=24;
   PrintMatrix(matrix, rows, cols);
   cristo=cross(matrix,rows,cols);
   if(cristo==true){
   	cout<<"there is a cross in the matrix";
   }
   else{
   	cout<<"there is no christ in this matrix";
   }
   DeleteMatrix(matrix, rows);
   return 0;
} // End main()
