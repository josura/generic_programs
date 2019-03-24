#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

main(){
	int numcontainer,minut,auxind;
	unsigned auxstr;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		auxind=0;
		minut=0;
		bool uscita=false;
		vector<unsigned> container;
		vector<unsigned> containersort;
		input>>numcontainer;
		for(int i =0;i<numcontainer;i++){
			input>>auxstr;
			container.push_back(auxstr);
			containersort.push_back(auxstr);
		}
		sort(containersort.begin(),containersort.end(),std::greater<int>());
		for(int i =0;i<numcontainer;i++){
			cout<<containersort[i]<<" ";
		}
		for(int i =0;i<numcontainer;i++){
			uscita=false;
			for(int j =0;j<numcontainer && !uscita;j++){               
				if(containersort[i]==container[j]){
					cout<<"ind"<<i<<j<<"auxind "<<auxind<<"minut"<<minut<<endl;
					minut+=abs(j-auxind);
					auxind=j;
					uscita=true;
				}
			}
		}
		output<<minut<<endl;			
	}
	
}
