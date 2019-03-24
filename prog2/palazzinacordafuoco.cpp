#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
	unsigned superstitinum,auxsup,sum;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		sum=0;
		input>>superstitinum;
		vector<unsigned> superstiti,auxsuperstiti;
		for(unsigned i=0;i<superstitinum;i++){
			input>>auxsup;
			superstiti.push_back(auxsup);
		}
		sort(superstiti.begin(),superstiti.end());
		for(unsigned i=0;i<superstiti.size();i++){
			cout<<superstiti[i]<<" ";
		}		
		cout<<endl;
		for(unsigned i=superstiti.size()-1;i>2 ;i-=2){
			sum+=max(superstiti[0],superstiti[1]);
			//cout<<"i piu' veloci saltano "<<superstiti[0]<<" e "<<superstiti[1]<<"   +"<<superstiti[1]<<endl;
			sum+=superstiti[0];
			//cout<<"il piu' veloce ritorna "<<superstiti[0]<<"   +"<<superstiti[0]<<endl;
			sum+=max(superstiti[i],superstiti[i-1]);
			//cout<<"i piu' lenti saltano "<<superstiti[i]<<" e "<<superstiti[i-1]<<"   +"<<superstiti[i]<<endl;
			sum+=superstiti[1];
			//cout<<"il secondo piu' veloce ritorna "<<superstiti[1]<<"   +"<<superstiti[1]<<endl;
			}if(superstiti.size()%2==0){
			sum+=superstiti[1];
			//cout<<"il secondo piu' veloce salta con il primo"<<superstiti[0]<<"   +"<<superstiti[0]<<endl;
			} else {
			sum+=superstiti[2]+superstiti[0];
			//cout<<"ritornano"<<superstiti[2]<<" e "<<superstiti[0]<<"   +"<<superstiti[2]<<"+"<<superstiti[0]<<endl;	
			sum+=superstiti[1];
			//cout<<"il  piu' veloce salta  col primo"<<superstiti[1]<<"   +"<<superstiti[1]<<endl;
			}
			cout<<sum<<endl;
			output<<sum<<endl;
	}
}
