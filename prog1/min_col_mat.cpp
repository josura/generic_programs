#include <iostream>
#include <cstdlib>

float ** BuildMatrix(int rows,int cols)
{  
   srand(666);
   float **m=new float*[rows]; 
   for (int i=0;i<rows;++i)  
       m[i]=new float[cols];  
   for (int i=0;i<rows;++i)
   {
      for (int j=0;j<cols;++j)
      {
         m[i][j]=rand()%30;
      }
   }
   return m;
}

void DeleteMatrix (float **m, int rows)
{
   for (int i=0;i<rows;++i)   
       delete [] m[i];        
   delete [] m;                   
}

float minElCol(float **mat,int rows, int numCol){
	float min=mat[0][numCol];
	for(int i=0; i<rows;i++){
		if(min>mat[i][numCol])
		    min=mat[i][numCol];
	}
	return min;
}

void print_matrix(float **matrix, int h, int w)
 {
         if(!w) w = h;
         for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                        std::cout << matrix[i][j] << '\t';
                }
                std::cout << "\n";
         }
 }
 
int main(){
	float **matrix=BuildMatrix(8,8);
	print_matrix(matrix,8,8);
	std::cout<<"\n\n elemento piu' mini della colonna:  "<<minElCol(matrix,8, 1);
	DeleteMatrix(matrix,8);
	return 0;
}
