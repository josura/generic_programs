#include<iostream>
#include<cstdlib>

using namespace std;

long long factorial (int n)
{   
    long long factorial=1;
	for(int i=1; i<=n; ++i)
	{
		factorial *=i;
	}
	return factorial;
}
int main()
{   
   unsigned int n;
	while (1)
	{
		system("cls");
		cout<<"numero in modo da computare il fattoriale ";
		cin>>n;
		if (n!=0)
		{
			long long result= factorial (n);
			cout<<"il fattoriale di n e' "<< result <<" per convenzione\n";
		    system("pause");
		}
		else {
		int	result=1;
			cout<<"il fattoriale di n e' "<< result << endl;
			system("pause");
			
			
		}
		
	}
	return 0;
}
