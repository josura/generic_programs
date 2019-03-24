#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int QUAD=10;

bool MXM(int[][QUAD]);

int main()
{
	int Matrix[QUAD][QUAD];
	int i, j;
	bool diag;
	

	srand(time(NULL));

	for(i=0; i<QUAD; i++)
	{
		for(j=0; j<QUAD; j++)
		{
			Matrix[i][j]=(rand()%10)-5;
			cout << right << setw(2) << Matrix[i][j];
		}
		cout << endl;
	}

	diag= MXM(Matrix);

	cout << endl << endl << diag;
    
	return 0;
}

bool MXM(int Matrix[][QUAD])
{
	int i, j, r, c, somma1,somma2;
	bool diag0=false;
	bool diag1=false;

	for(j=QUAD-1, i=0; j>=0; j--)
	{
		for(c=j, r=i, somma1=0; c<QUAD; c--, r++)
		{
			somma1 += Matrix[r][c];
		}
		if(somma1==0)
		{
			diag0=true;
		}
	}

	for(i=1, j=QUAD-1; i<QUAD-1; i++)
	{
		for(r=i, c=j, somma2=0; r<QUAD; r++, c--)
		{
			somma2 += Matrix[r][c];
		}
		if(somma2==0)
		{
			diag1=true;
		}
	}
    
	if (diag0==true && diag1==true)	{
		cout<<"above and under the diagonal is null";
		return (true);
	}
	else if (diag0==true){
		cout<<"above the diagonal is null";
		return(true);
	}
	else if (diag1==true){
		cout<<"under the diagonal null";
		return(true);
	}
	return(false);
}

