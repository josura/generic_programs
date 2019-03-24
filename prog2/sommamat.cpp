#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

int main(){
	int righe,cols,aux;
    int **mat1,**mat2;
	ifstream input("input.txt");              //input (1).txt
	ofstream output("output.txt");              //output.txt
	while(!input.eof()){
		input>>righe>>cols;
        mat1=new int*[righe];
        mat2=new int*[righe];
        for(unsigned i=0;i<righe;i++){
            mat1[i]=new int[cols];
            mat2[i]=new int[cols];
        }
		    for(unsigned i=0;i<righe;i++){
                for(unsigned j=0;j<cols;j++){
                    input>>aux;
                    mat1[i][j]=aux;
                }
            }
            for(unsigned i=0;i<righe;i++){
                for(unsigned j=0;j<cols;j++){
                    input>>aux;
                    mat2[i][j]=aux;
                }
            }
        for(unsigned i=0;i<righe;i++){
                for(unsigned j=0;j<cols;j++){
                   output<<mat1[i][j]+mat2[i][j]<<" " ;
                }
        }  
        output<<endl;
        for(unsigned i=0;i<righe;i++){
            delete  mat1[i];
            delete  mat2[i];}
        delete [] mat1;
        delete [] mat2;    
		
	}
	
}