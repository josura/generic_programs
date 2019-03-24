#include<iostream>
#include<cstdlib>
#include<iomanip>

using namespace std;

/*void initialize(int **matrix,int size){
	for (int i=0;i<size;i++){
      for (int j=0;j<(size*2-1);j++){
      	matrix[i][j]=0;
      }}
}*/

int **BuildTart(int size){
	int **m= new int*[size];
	for(int i=0;i<size;i++)
		m[i]=new int[size*2-1];
	//initialize(m,size);
	for (int i=0;i<size;i++){
      for (int j=0;j<(size*2-1);j++){
      	m[i][j]=0;
      	if(i==0)
      	m[i][size]=1;
      	else{
      		if((j-1)<0 || (j+1)>=(size*2-1)){
      			if((j-1)<0)
      			m[i][j]=m[i-1][j+1];
      			else if((j+1)>=(size*2-1))
      			m[i][j]=m[i-1][j-1];
      		}
      		else{
      		m[i][j]=m[i-1][j-1]+m[i-1][j+1];
      		}
		  }
      }
   }
   return m;
}

void PrintMatrix(int **mat,int rows,int cols)
{
   for (int i=0;i<rows;++i){
      for (int j=0;j<cols;++j){
      	if(mat[i][j]==0)
      	 cout << right << setw(2) <<"";
      	 else
         cout << right << setw(2) <<mat[i][j]<<"";
      }
      cout<<endl;
   }
}

int main(){
	int numTart=20;
	int **matrix;
	matrix=BuildTart(numTart);
	PrintMatrix(matrix,numTart,numTart*2-1);
	return 0;
	
}
