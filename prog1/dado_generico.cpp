#include <iostream>
#include<cstdlib>
#include<ctime>


using namespace std;


int main()
{
   int dado = 0;
   int y = 0; 
   int lanci = 0,x=0;
   srand(time(0));
   while (y < 5)
      {
        int aux = rand();
        dado = (aux % 6) + 1;
        cout<<" "<<dado<<", ";
        if (dado!=x){
        	x=dado;
        	y=1;
		}
        else if (dado == x)
        	{   
        		cout<<"\n";
        		dado=0;
        		y++;
        	}
        lanci++; 
      } 
      
   cout << "\nLanci effettuati : " << lanci << endl; 

   system("PAUSE");    
   return 0;
} 
