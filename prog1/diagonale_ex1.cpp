#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

//const int DIM=15;

void Matrix_print(int* matrix);

bool Es(int quad ,int* matrix);

int main()
{
	srand(time(NULL));	
	int i,j,quad;
	bool diags;
	cout<<"enter the number of rows and columns(quadratic matrix): ";
	cin>>quad;
	cout<<endl;
	int matrix[quad][quad];
	for(i=0; i<quad; i++)
	{
		for(j=0; j<quad; j++)
		{
		    matrix[i][j]=(rand()%15)-7;
			cout << right << setw(3) << matrix[i][j];
		}
		cout << endl;
	}
	Matrix_print(&matrix[0][0]);
	diags = Es(quad,&matrix[0][0]);
	if (diags==true){
		cout<<"the sum above or under the diagonal is NULL";
		return 0;
	}
    cout<<"the sum above or under the diagonal is not NULL";
	return 0;
}

void Matrix_print(int quad,int *matrix) {
	for (int i = 0; i < quad; i++) {
		for (int j=0; j<quad;j++) 
		cout << matrix[i*quad+j] << ", ";
		cout<<"\n";
	}
}

bool Es(int quad,int *matrix)
{
	int i, j, r, c, somma, wow;
	bool diag0=false;
	for(j=quad-1, i=0; j>=0; j--)
	{
		for(c=j, r=i, somma=0; c<quad; c--, r++)
		{
			wow=matrix[i*quad+j];
			somma += wow;										//al di sopra della diagonale
		}
		if(somma==0)
		{
			diag0=true;
			cout << endl << endl << i+1 << "-" << j+1;
			return(diag0);
		}
	}

	for(i=1, j=quad-1; i<quad-1; i++)
	{
		for(r=i, c=j, somma=0; r<quad; r++, c--)
		{
			wow=matrix[i*quad+j];
			somma += wow;
		}
		if(somma==0)												//al di sotto della diagonale
		{
			diag0=true;
			cout << endl << endl << i+1 << "-" << j+1;
			return(diag0);
		}
	}
    
	return(diag0);	
}
