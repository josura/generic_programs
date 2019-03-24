#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


int main(){
	unsigned numpart,vinteB,vinteC,g,indi;
	bool vinta;
	int segno;
	string line;
	short tictac[3][3];
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		vinteB=vinteC=indi=0;
		input>>numpart;
		vector<int> coppie;
		getline(input,line);
		cout<<line<<endl;
		int aux;
    	for(unsigned i=0; i<line.length(); i++){
      		if(line[i]!=')' && line[i]!='(' && line[i]!=',' && line[i]!=' '){
        		aux=line[i]-48; 
				coppie.push_back(aux);    
      		}
    	}
    	/*for(unsigned i=0;i<coppie.size();i++){
			cout<<coppie[i]<<" ";		
		}
		cout<<endl;*/
		for(unsigned i=0;i<numpart ;i++){
			//cout<<"prob num("<<i<<endl;
			for(unsigned i=0;i<3;i++){
				for(unsigned j=0;j<3;j++)
					tictac[i][j]=-1;}	
			//mosse=0;
			vinta=false;
			segno=1;
			for( g=indi;(g<coppie.size() && g<indi+18) && !vinta;g+=2){
				for(unsigned i=0;i<3;i++){
					for(unsigned j=0;j<3;j++)
						cout<<tictac[i][j]<<"  ";
					cout<<endl;	}
					cout<<endl;	
				//cout<<segno<<endl;
				if(segno>0){
					cout<<"X  ( "<<coppie[g]<<","<<coppie[g+1]<<")"<<endl;
					tictac[coppie[g]][coppie[g+1]]=1;
					//mosse++;
					if(((tictac[2][2]==1) && (tictac[0][0]==tictac[1][1])&& (tictac[1][1]==tictac[2][2])) || ((tictac[2][0]==1) && (tictac[0][2]==tictac[1][1])&&(tictac[1][1]==tictac[2][0]))){
						vinta=true;
						vinteB++;
						
						for(unsigned i=0;i<3;i++){
							for(unsigned j=0;j<3;j++){
								cout<<tictac[i][j]<<"  ";
								tictac[i][j]=-1;
							}
							cout<<endl;
						}
						cout<<endl<<"partita vinta B\n";
					}
					for(unsigned i=0;i<3 && !vinta ;i++){
						if(((tictac[i][0]==tictac[i][1])&& (tictac[i][1]==tictac[i][2]) && (tictac[i][2]==1)) || ((tictac[0][i]==tictac[1][i])&&(tictac[1][i]==tictac[2][i])&&(tictac[2][i]==1))){
							vinta=true;
							vinteB++;
							
							for(unsigned i=0;i<3;i++){
								for(unsigned j=0;j<3;j++){
									cout<<tictac[i][j]<<"  ";
									tictac[i][j]=-1;
								}
								cout<<endl;
							}
							cout<<endl<<"partita vinta B\n";
						}
					}
				}
				else if(segno<0 && !vinta){
					cout<<"O  ( "<<coppie[g]<<","<<coppie[g+1]<<")"<<endl;
					tictac[coppie[g]][coppie[g+1]]=0;
					//mosse++;
					if(((tictac[0][0]==tictac[1][1])&& (tictac[1][1]==tictac[2][2]) && (tictac[2][2]==0)) || ((tictac[0][2]==tictac[1][1])&&(tictac[1][1]==tictac[2][0])&&(tictac[2][0]==0))){
						vinta=true;
						vinteC++;
						
						for(unsigned i=0;i<3;i++){
							for(unsigned j=0;j<3;j++){
									cout<<tictac[i][j]<<"  ";
									tictac[i][j]=-1;
								}
								cout<<endl;
						}
							cout<<endl<<"partita vinta C\n";
					}
					for(unsigned i=0;i<3 && !vinta ;i++){
						if(((tictac[i][0]==tictac[i][1])&& (tictac[i][1]==tictac[i][2]) && (tictac[i][2]==0)) || ((tictac[0][i]==tictac[1][i])&&(tictac[1][i]==tictac[2][i])&&(tictac[2][i]==0))){
							vinta=true;
							vinteC++;
							for(unsigned i=0;i<3;i++){
								for(unsigned j=0;j<3;j++){
									cout<<tictac[i][j]<<"  ";
									tictac[i][j]=-1;
								}
								cout<<endl;
							}
							cout<<endl<<"partita vinta C\n";
						}
					}
				}
				segno*=-1;
			}
			cout<<"patta?"<<endl;
			indi=g;
		}
		/*for(unsigned i=0;i<3;i++){
			for(unsigned j=0;j<3;j++)
				cout<<tictac[i][j]<<"  ";
		cout<<endl;			
		}*/
		cout<<vinteB<<" "<<vinteC<<endl;
		output<<vinteB<<" "<<vinteC<<endl;
	}
	
}
