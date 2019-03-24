#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;


string lcs( string X, string Y) {
	int m=X.length(),n=Y.length(); 
   	int** L=new int*[m+1];
   	for(int i=0;i<=m;i++)
   	 	L[i]=new int[n+1];
   	for (int i=0; i<=m; i++) { 
     	for (int j=0; j<=n; j++) { 
       		if (i == 0 || j == 0)  L[i][j] = 0; 
       		else if (X[i-1] == Y[j-1]) L[i][j] = L[i-1][j-1] + 1; 
       		else L[i][j] = max(L[i-1][j], L[i][j-1]); 
     	} 
   	}	 
   	string lcs; 
   	lcs=""; 
   	int i = m, j = n; 
   	while (i > 0 && j > 0){ 
      if (X[i-1] == Y[j-1]) { 
          lcs += X[i-1]; // Put current character in result 
          i--; j--;     // reduce values of i, j and index 
      }
      else if (L[i-1][j] > L[i][j-1]) 
         i--; 
      else
         j--; 
   } 
  	for(unsigned i=0;i<floor(lcs.size()/2);i++){
  		char aux=lcs[i];
  		lcs[i]=lcs[lcs.size()-i-1];
  		lcs[lcs.size()-i-1]=aux;
	  }
   return lcs;
} 



int main(){
	ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    if (input.fail())
	{
		cout<< "Apertura input.txt fallita!\n";
		exit(1);
	}
	if(output.fail())
	{
		cout << "Non sono riuscito a scrivere l'output.txt!'\n";
		exit(1);
	}
    int char1,char2;
    while(!input.eof()){
    	//cout<<"ciao ";
		input>>char1>>char2;
		string aux1,aux2,longestcs;
		input>>aux1>>aux2;
		//cout<<aux1<<" "<<aux2<<endl;
		longestcs=lcs(aux1,aux2);
		//cout<<longestcs<<endl;
		output<<longestcs<<endl;
	}
    output.close();
    input.close();
    return 0;
}
