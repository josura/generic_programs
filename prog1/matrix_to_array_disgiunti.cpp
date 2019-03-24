#include <iostream>
#include <ctime>
#include <cstdlib>
#include<iomanip>
 
using namespace std;

int random_int(int min, int max);
void random_matrix(int *matrix,int x, int y); 
void print_array(int *aptr,int size);
void print_matrix(int *matrix,int rows,int cols);
bool existence(int *matrix,int rows, int cols,int value,int self);

int main(){
srand(time(0));
bool ex=false;
int rows,cols,value,self,array_size;
cout<<"insert the number of rows and columns: ";
cin>>rows>>cols;
//int size=rows*cols;
int *ptr=new int;
int matrix[rows][cols];
random_matrix(&matrix[0][0],rows,cols);
cout<<"this is the matrix:"<<endl;
print_matrix(&matrix[0][0],rows,cols);
for(int i=0;i<rows;i++){
	for(int j=0;j<cols;j++){
		value=matrix[i][j];
		self=i*cols+j;
		ex=existence(&matrix[0][0],rows,cols,value,self);
		if (ex==true){
			*(ptr+array_size)=matrix[i][j];
			array_size++;
		}
		else if (ex==false)
		break;
	}
}
cout<<endl<<"and this is the array with unique elements"<<endl;
print_array(ptr,array_size);
return 0;
} 

int random_int(int min, int max)
 {
        max -= min - 1;
        return int(rand() % max + min);
 }
 
void random_matrix(int *matrix,int x,int y){
	for (int j=0;j<y;j++){
		for(int i=0;i<x;i++){                                 
			matrix[i*y+j]= random_int(0,20);				  
		}
	}
}

void print_array(int *array, int size){
        for(int i = 0; i < size; i++) {
                cout <<"["<< *(array + i)<<"] ";
        }
        return;
 }
 
void print_matrix(int *matrix,int rows,int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j=0; j<cols;j++)  
		cout << right << setw(3) << matrix[i*cols+j] << ",";
		cout<<"\n";
	}
}

bool existence(int *matrix,int rows,int cols,int value,int self){
	for (int k=0;k<rows;k++){
			for(int z=0;z<cols;z++){
				if (k*cols+z!=self){
					if(matrix[k*cols+z]!=matrix[(rows-1)*cols+(cols-1)]){
						if(matrix[k*cols+z]==value)
						return false;
						}						
				}
				else if (k*cols+z==(rows-1)*cols+(cols-1)){
					if(matrix[k*cols+z]==matrix[(rows-1)*cols+(cols-1)]){
						return false;
					}	
					else if (matrix[k*cols+z]!=matrix[(rows-1)*cols+(cols-1)])
					return true;
				}
				/*if (matrix[i][j]!=matrix[k][z]){
					counter=1;
					counterplus++;
				}		
				else if(matrix[i][j]==matrix[k][z]){
					counter=0;
					counterplus=0;
					goto endc;
				}*/	
			}
		/*endc:
		if (counter!=0 && counterplus==size-(z*rows+k)-1){
			*(ptr+array_size)=matrix[i][j];
			array_size++;
			}
		else //if(matrix[i][j]==matrix[k][z])
		break;*/
		}	
}

