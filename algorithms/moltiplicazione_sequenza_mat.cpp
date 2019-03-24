#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

int MatrixChainOrder(int* p, int n){ 
    int** m=new int*[n];
	for(int i=0;i<n;i++)
		m[i]=new int[n];
    int i, j, k, L, q;
 
    for (i=1; i<n; i++)
        m[i][i] = 0;    //number of multiplications are 0(zero) when there is only one matrix
 
    //Here L is chain length. It varies from length 2 to length n.
    for (L=2; L<n; L++){
        for (i=1; i<n-L+1; i++){
            j = i+L-1;
            m[i][j] = INT_MAX;  //assigning to maximum value
 
            for (k=i; k<=j-1; k++){
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;    //if number of multiplications found less that number will be updated.
                }
            }
        }
    }
	/*for (int i=1; i<n; i++) {
		for (int j=1; j<n; j++) {
			cout<<m[i][j]<<"\t";
		}
		cout<<endl;
	}*/
    return m[1][n-1]; 
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
    int nummat;
    string dimat;
    while(!input.eof()){
    	cout<<"ciao ";
		input>>nummat;
		int* dimensioni=new int[nummat + 1];
		for(int i=0;i<nummat-1;i++){
			input>>dimat;
			string nod1="";
	    		for(unsigned j=1;isdigit(dimat[j]);j++){
            		nod1+=dimat[j];
				}
				dimensioni[i]=atoi(nod1.c_str());
		}
		input>>dimat;
		string nod1="",nod2="";
	    int cosa=0;
       			for(unsigned i=1;isdigit(dimat[i]);i++){
       				nod1+=dimat[i];
	      			cosa=i+1;
				}
				//cout<<nod1<<" ";
    	    	for(unsigned i=cosa+1;isdigit(dimat[i]);i++){
        		    nod2+=dimat[i];
				}
				dimensioni[nummat-1]=atoi(nod1.c_str());
				dimensioni[nummat]=atoi(nod2.c_str());
			for(unsigned i=0;i<nummat+1;i++){
        		    cout<<dimensioni[i]<<" ";
				}
				cout<<endl;
			int moltsca=MatrixChainOrder(dimensioni,nummat+1);
		output<<moltsca<<endl;
	}
    output.close();
    input.close();
    return 0;
}
