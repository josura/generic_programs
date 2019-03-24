#include<iostream>
#include<windows.h>
#include<iomanip>

using namespace std;

void printMatrix(int rows,int col,int *matrix) {
	for (int i = 0; i < rows; i++) {
		for (int j=0; j<col;j++)  
		cout << right << setw(3) << matrix[i*col+j] << ",";
		cout<<"\n";
	}
	//cout<<matrix[(rows-1)*col+(col-1)];
}

int main(){
	int rows;
	int col;
	cout<<"enter the number of rows: ";
	cin>>rows;
	cout<<endl;
	cout<<"enter the number of columns: ";
	cin>>col;
	cout<<endl;
	int matrix[rows][col];
	for(int i=0;i<rows;i++){
		for(int j=0;j<col;j++)
			matrix[i][j]=i+j;
	}
	printMatrix(rows,col,&matrix[0][0]);
	
}


