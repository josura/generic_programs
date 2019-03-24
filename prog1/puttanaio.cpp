#include <iostream>
#include <cstdlib>
#include<cmath>
#define l 4
#define letterecas  ((rand()%4)+5)

using namespace std;

void colnondecresc(string** matrix,unsigned rows, unsigned cols){
    for(int y = 0; y < cols; y++){
        for(int x = 0; x < rows-1; x++){
            for(int p = x + 1; p < rows; p++){
                if(matrix[x][y] > matrix[p][y]){
                    string s {matrix[x][y]};         //ma non decrescente lessicalmente o di lunghezza
                    matrix[x][y] = matrix[p][y];
                    matrix[p][y] = s;
                /*if(matrix[x][y].length > matrix[p][y].lenght){
                    string s = matrix[x][y];         //io li faccio tutti e due
                    matrix[x][y] = matrix[p][y];
                    matrix[p][y] = s;*/    
                }
            }
        }
    }
}

bool diaginverseuguali(short** matrix,unsigned rows){
    for(int x=1, k=rows-2; x<rows; x++, k--){
        int y = 0, c = rows-1;
        bool nodiag = false;
        for(int z=x, j=k; z<rows && !nodiag; z++, j--){
            if(matrix[z][y] == matrix[j][c]){
                if(z==rows-1) return true;
                y++, c--;
            }else nodiag = true;
        }
    }
    return false;
}

template<typename T>
inline bool elementidistintiarr(T *arr,int n){
	for(int i=0;i<n-1;i++){
		for(int j=1;j<n;j++){
			if(arr[i]==arr[j])
				return false;
		}
	}
	return true;
}

int ** matrixVect(int *arr1,int *arr2,int n, int m){
	int**mat=new int*[n];
	for(int i=0;i<m;i++){
		mat[i]=new int;
		for(int j=0;j<m;j++){
			if(elementidistintiarr(arr1, n))
				mat[i][j]=arr1[i] * arr2[j]; 
			else mat[i][j]= (i==j) ? 1 : 0;
		}
	}
	return mat;		
}

/*int aereowow(int**S,int n,int m){
	int spos=0;
	
	while(j<m){
		if (S[i][j]==0)
			return spos;
		if (S[i][j]<0){
		 cout<<"evvaih bambini morti, torri gemelle num 2";
		 return spos;
		}
	}
}*/

bool viciniEDivisibilli7(int*arr,int n){
	int min=abs(arr[0]-arr[1]),num1,num2;
	for(int i=1;i<n-1;i++){
            for(int j=i+1; j<n ; j--){
                if((abs(arr[i]-arr[j]))<=min){
                	min=abs(arr[i]-arr[j]);
                	num1=arr[i];
                	num2=arr[j];
				}
            }
    	}
    return (((num1+num2)%7)==0);	
}


bool strcomunearray(string *mat,int n){
	int counter=0,k,g=0,counterstr=3;
	bool cond=true;
	string cercata=string();
	while (k<mat[0].length() && g<k && g<=counterstr ){
			if(g<3){
        		if(mat[0][k]==mat[1][g])
        		{cercata+=mat[0][k];k++;g++;}
        		else {k++;g=0;cercata="";}
			}
			if(g>=3){
				if(mat[0][k]==mat[1][g])
        		{cercata+=mat[0][k];k++;g++;counterstr++;}
        		else {k++;g=0;counterstr=g-1;}
			}
	}
    for (int i=0;i<n && cond==true;i++){
       	k=0;g=0;
       	while (k<mat[i].length() && g<k && g<cercata.length() && cercata.length()!=0){
       		if(mat[i][k]==cercata[g])
   	    		{k++;g++;cercata+=mat[i][k];}
       		else {k++;g=0;}
		}
		if(g>=3){
			cond=true;
			counter++;
		}
	}
	if(counter==n)
		return true;
	return false;
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

bool diagonaliInverseWoW(short **mat,int n){
	int coso1=1,i,counter;
	while(coso1<n-1){
		i=0;counter=0;
		while(i<n){
			if (mat[i][i+coso1]==mat[n-i][n-i-coso1])
				counter++;
			i++;		
		}
		if(counter>=n-1)
			return true;
		coso1++;	
	}
	return false;
}

bool strtuttcol(string **mat,int n,int m,string str){
	int counter,k,g;
	bool cond=true;
	for (int j=0;j<m;j++){
		counter=0;
        for (int i=0;i<n && cond==true;i++){
        	k=0;
        	while (k<mat[i][j].length() && g<k && g<str.length() ){
        		if(mat[i][j][k]==str[g])
        		{k++;g++;}
        		else {k++;g=0;}
			}
			if(g==str.length()){
				cond=true;
				counter++;
			}
		}
		if(counter==n)
			return true;
	}
	return false;
}


string **B(short *A,int n){               //programma del 2016 eser 2 ma non mi compila per un errore che non riesco a comprendere 
	srand(666);
	int accasonum,numcas;
		string **B=new string*[n];
		for(int i=0;i<n;i++){ 
        	B[i]=new string[A[i]];
        	for (int h=0;h<A[i];h++){
   			B[i][h]=string();
			numcas=letterecas;
			for(int k=0;k<numcas;k++){
				accasonum=(rand()%8);
				if(accasonum<6)
					B[i][h]+="w";
				else if(accasonum==6)
					B[i][h]+="s";
				else if(accasonum==7)
					B[i][h]+="k";
				
			}
		}
	}
	return B;	
}

bool stringasenzap(string *S,int n){
	for (int j=0;j<n;j++){
	string forse=string();
        for (int i=0;i<S[j].size();i++){        	
   	        	if(S[j][i]!='p'){                              //matrice wow
        			forse+=S[j][i];
				}
				if(S[j].size()==forse.size()){
					return true;
				}
        		
    	}
	}
	return false;
}

int maxPointerSameValue(long*** mat,int n,int m){
	int maxpoint=0,pointcorr,maxcol=0;
	for (int j=0;j<m;j++){
		pointcorr=0;
        for (int i=0;i<n-1;i++){
        	for(int k=i+1;k<n;k++){
         		if (*(mat[i][j])==*(mat[k][j]))
         			pointcorr++;
            }
		}
		if(pointcorr>maxpoint){
		    maxpoint=pointcorr;
		    maxcol=j;
      }
   }
   return maxcol;
}

float prodThird(float** mat,int n){
	float num1 = mat[0][2], num2 = mat[1][2];
	float min = fabs(num1-num2);
	for (int i=0;i<n-1;i++){
      for (int k=i+1;k<n;k++){
         if (fabs(mat[i][2]-mat[k][2])<min) {
				num1 = mat[i][2], num2 = mat[k][2];
				min = fabs(num1 - num2);
      }
   }
   }
   return (num1*num2);

}

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

template<typename T>
void DeleteMatrix (T **m, int rows)
{
   for (int i=0;i<rows;++i)   
       delete [] m[i];        
   delete [] m;                   
}

template<typename T>
void print_matrix(T **matrix, int h, int w)
 {
         if(!w) w = h;
         for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                        std::cout << matrix[i][j] << '\t';
                }
                std::cout << "\n";
         }
 }

template<typename T>
bool sameDiag(T **mat,int rows,int cols){
	int i=0;
	for(i=0;i<rows;i++){
		if(mat[i][i]!=mat[i][cols-1-i])
			return false;
	} 
	return true;
} 

void mex(int **matrix,bool risp){
	print_matrix(matrix,l,l);
	if(risp==true)
		std::cout<<"matrice con diagonali uguali";
	else
		std::cout<<" no matrice con diagonali uguali";	
}

int main(){
	int **matrix=BuildMatrix(l,l);
	print_matrix(matrix,l,l);
	std::cout<<"\n\n :  "<<sameDiag(matrix,l,l)<<"\n";
	mex(matrix,sameDiag(matrix,l,l));				
	DeleteMatrix(matrix,4);
	return 0;
}
