#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include<iomanip>
 
using namespace std;

static const char pool[]=
 	"ab";
int poolsize= sizeof(pool)-1;

char random_char();
string random_string(int lenght);
void random_matrix_string(string *matrix,int x, int y,int lenght);
bool contiguous_inverse_string(string *matrix,int x, int y);
void printMatrix(string *matrix,int rows, int cols);
 
int main(){
	srand(time(0));
	int rows,cols,lenght;
	cout<<"enter the size of the matrix(rows and then columns): ";
	cin>>rows>>cols;
	cout<<"enter the lenght of the words: ";
	cin>>lenght;
	string matrix[rows][cols];
	random_matrix_string(&matrix[0][0],rows,cols,lenght);
	printMatrix(&matrix[0][0],rows, cols);
	bool answer=false;
	answer=contiguous_inverse_string(&matrix[0][0],rows,cols);
	if (answer==true){
		cout<<"there are two strings in the matrix that are contiguous and inversed ";
	}
	else
	{
		cout<<"there are not strings in the matrix that are contiguous and inversed";
	}
	
return 0;	
}

char random_char(){
	return pool[rand()% poolsize];	
}

string random_string(int lenght){
	string str;
	for (int i =0; i<lenght; i++){        //se non funziona devo trasportare la funzione all'interno del void sotto
		str+=random_char();
	}
	return str;
}

void random_matrix_string(string *matrix,int x,int y,int lenght){
	for (int j=0;j<y;j++){
		for(int i=0;i<x;i++){                                 //ma la matrice di string, nonostante string sia una classe Giorgio ignorante
			matrix[i*y+j]= random_string(lenght);				  //e invece le classi si comportano come dei tipi(TIPI DEFINITI DALL'UTENTE)
		}
	}
}

bool contiguous_inverse_string(string *matrix,int x, int y){
	int wow=0;
	for(int j=0;j<y;j++){
		for(int i=0;i<x-1;i++){
			string s1=matrix[i*y+j];
			cout<<"["<<s1<<"]";
			string s2=matrix[(i+1)*y+j];
			//cout<<"["<<s2<<"]";
			int size1=matrix[i*y+j].size(),
			size2=matrix[(i+1)*y+j].size();
			if (size1==size2){
				for(int k=0;k<size1;k++){
					if(s1[k]==s2[size1-1-k])
					wow++;
				}
				if (wow==size1)
				return true;
				/*while(s1[k]==s2[size1-k]){
					k++;
				};
				if (k==size1)
				return true;*/
			}
		}
	}
	return false;
}

void printMatrix(string *matrix,int rows,int col) {
	for (int i = 0; i < rows; i++) {
		for (int j=0; j<col;j++)  
		cout << right << setw(3) << matrix[i*col+j] << ",";
		cout<<"\n";
	}
}


