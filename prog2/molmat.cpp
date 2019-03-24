#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(){
	int righe,cols,multcol,aux;
    int **mat1,**mat2,**mult;
	ifstream input("input.txt");              //input (1).txt
	ofstream output("output.txt");              //output.txt
	while(!input.eof()){
		input>>righe>>cols>>multcol;
        mat1=new int*[righe];
        mat2=new int*[cols];
        mult=new int*[righe];
        for(unsigned i=0;i<righe;i++){
            mat1[i]=new int[cols];
            mat2[i]=new int[multcol];
            mult[i]=new int[multcol];
        }
		    for(unsigned i=0;i<righe;i++){
                for(unsigned j=0;j<cols;j++){
                    input>>aux;
                    mat1[i][j]=aux;
                }
            }
            for(unsigned i=0;i<cols;i++){
                for(unsigned j=0;j<multcol;j++){
                    input>>aux;
                    mat2[i][j]=aux;
                }
            }
            for(unsigned i=0;i<righe;i++){
                for(unsigned j=0;j<multcol;j++){
                    aux=0;
                    for(unsigned k=0;k<cols;k++)
                        aux+=mat1[i][k]*mat2[k][j];
                   // output<<aux<<" ";    
                    mult[i][j]=aux;    
                }
            }
        for(unsigned i=0;i<righe;i++){
                for(unsigned j=0;j<multcol;j++){
                   output<<mult[i][j]<<" " ;
                }
        }  
        output<<endl;
        for(unsigned i=0;i<righe;i++){
            delete  mat1[i];
            delete  mat2[i];
            delete  mult[i];
            }
        delete [] mat1;
        delete [] mat2;    
		delete [] mult;
	}
	
	
}