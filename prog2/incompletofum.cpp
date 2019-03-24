#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>


using namespace std;

/*
	
*/

main(){
	int numcarte;
	string auxstr,realauxstr,strwoa;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		vector<string> manoinver,manonorm;
		input>>numcarte;
		for(int i =0;i<numcarte;i++){
			input>>auxstr;
			reverse(auxstr.begin(),auxstr.end());
			manoinver.push_back(auxstr);
			sort(manoinver.begin(),manoinver.end());
			manonorm=manoinver;
			for(unsigned j=0;j<manonorm.size();j++){
				reverse(manonorm[j].begin(),manonorm[j].end());
			}
			//for(unsigned god=0;god<manonorm.size();god++)	
				for(unsigned j=1;j<manonorm.size();j++){
					//cout<<manoinver[j-1]<<" "<<manoinver[j]<<" whela ";
					if(manonorm[j-1].size()>manonorm[j].size() && manonorm[j][manonorm[j].size()-1]==manonorm[j-1][manonorm[j-1].size()-1])
						swap(manonorm[j-1],manonorm[j]);
				}
			for(unsigned j=0;j<manonorm.size();j++){
				output<<" "<<manonorm[j];
			}
			output<<",";			
		}
		output<<endl;
	}
	
}
