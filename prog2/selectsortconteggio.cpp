#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


unsigned selectSortconconteggio(int* arr, unsigned size)
{
	unsigned conteggio=0;
    int  min_el;									
    for (unsigned i = 0; i < size-1; i++){        
        min_el=i;   								
        for (unsigned j=i+1; j<size; j++)
          	if (arr[j]<arr[min_el])
           	    min_el=j;
 	   	swap(arr[min_el], arr[i]);
		conteggio+=min_el-i;	               
    }
    return conteggio;
}

int main(){
	unsigned numele;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numele;
		int* arr=new int[numele];
		for(unsigned i=0;i<numele;i++){
			input>>arr[i];		
		}
		unsigned somma=selectSortconconteggio(arr, numele);
		for(unsigned i=0;i<numele;i++){
			cout<<arr[i];		
		}
		cout<<endl<<somma;
		output<<somma<<endl;
	}
	
}
