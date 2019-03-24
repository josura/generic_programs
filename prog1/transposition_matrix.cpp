#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int random_int(int min, int max);
void matrix_rand(int *matrix,int rows,int cols);
int **matrix_transpo(int *matrix_1, int rows, int cols);
void print_matrix(int *matrix, int rows, int cols)
 {
         for(int i = 0; i < rows; i++) {
                for (int j=0; j<cols;j++)  
		cout << right << setw(3) << matrix[i*cols+j] << ",";
		cout<<"\n";
		}
        return;
 }

int main(){
	srand(time(0));
	int rows,cols;
	cout<<"enter the number of rows: ";
	cin>>rows;
	cout<<endl;
	cout<<"enter the number of columns: ";
	cin>>cols;
	cout<<endl;
	int matrix[rows][cols];
	matrix_rand(&matrix[0][0],rows,cols);
	print_matrix(&matrix[0][0],rows,cols);
	cout<<endl<<"matrix before transposition"<<endl<<endl;
	int *ptr_matrix=matrix_transpo(&matrix[0][0],rows,cols);
	print_matrix(&matrix[0][0],rows,cols);
	cout<<"matrix after transposition"; 
	return 0;
		
}

int random_int(int min, int max)
{
        max -= min - 1;
        return int(rand() % max + min);
}

int **matrix_rand(int rows, int cols)
 {
        int **matrix = new int*[rows];
        for(int i = 0; i < rows; i++) {
                matrix[i] = new int[cols];               
                for(int j = 0; j < cols; j++) 
                    matrix[i][j] = random_int(random_int(0,13),17) ;
        }
       
        return matrix;
 }

int **matrix_transpo(int *matrix_1, int rows, int cols)
 {
        int **matrix = new int*[rows];
        int k=0,temp;
        for(int i = 0; i < rows; i++) {
                matrix[i] = new int[cols];               
                for(int j = k; j < cols; j++) {
                        matrix[j][i] =matrix_1[i*cols+j];
                        matrix[i][j]=matrix_1[j*rows+i]; 
                }
            k++;    
        }
        return matrix;
 }
