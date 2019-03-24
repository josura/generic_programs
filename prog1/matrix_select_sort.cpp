//program to sort columns of matrix with selectsort
#include <iostream>
#include <cstdlib>

int ** BuildMatrix(int rows,int cols)
{  
   srand(666);
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

template<typename T>
void swap(T &x, T &y)
{
    T temp = x;
    x = y;
    y = temp;
}

void selectsort_cols(int** mat, int rows, int cols){
	int i, k, min_el;
	for(int j=0;j<cols;j++){
		for(i=0;i<rows-1;i++){
			min_el=i;
			for(k=i+1;k<rows;k++){
				if(mat[k][j]<mat[min_el][j])
					min_el=k;
			}
			swap(mat[i][j],mat[min_el][j]);		
		}
	}
}

void insertsort_cols(int** mat, int rows, int cols){
	int i, k, numb;
	for(int j=0;j<cols;j++){
		for(i=1;i<rows;i++){
            numb = mat[i][j];
            for(k=i-1; k>=0 && mat[k][j]>numb; k--){
                mat[k+1][j]=mat[k][j];
            }
         	mat[k+1][j]=numb;
    	}
    }/*	for(i=1;i<rows;i++){
			numb=mat[i][j];
			k=i-1;
			while(k>=0 && mat[k][j]>numb){
				mat[k+1][j]=mat[k][j];
				k--;
			}
			mat[k+1][j]=numb;		
		}*/
}

void print_matrix(int **matrix, int h, int w)
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
	int **matrix=BuildMatrix(8,8);
	print_matrix(matrix,8,8);
	std::cout<<"\n matrice ordinata per colonne di seguito\n";
	insertsort_cols(matrix,8,8);
	print_matrix(matrix,8,8);
	DeleteMatrix(matrix,8);
	return 0;
}
