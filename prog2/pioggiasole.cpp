#include<iostream>
#include<fstream>
#include<vector>


using namespace std;

string giornateN(ofstream& out,unsigned periodotot){
	string str="";
	if(periodotot==0){
		str="P S S ";
	}
	else {
		string Ps="";
		for(unsigned i=0;i<periodotot+2;i++)
			Ps+="S ";
		str=giornateN(out,periodotot-1)+"P "+Ps+giornateN(out,periodotot-1);
	}
	return str;
}

main(){
	unsigned numgiorni,periodo;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numgiorni>>periodo;
		
		//if(numgiorni==20) cout<<"ci sono";
		string wow=giornateN(output,numgiorni+periodo),final="";
		//final=wow.substr((numgiorni-1)*2,(periodo+numgiorni-1)*2);
		cout<<wow<<endl;
		for(unsigned i=(numgiorni-1)*2;i<(numgiorni+periodo-1)*2;i++){
				final+=wow[i];
		}
		output<<final<<endl;
	}
}
