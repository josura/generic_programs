#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


void cambioattornoE(ofstream& output,char** map,short** matmos,unsigned rows,unsigned cols,int i,int j,unsigned counter){
	//orizzontali e verticali
	if(i+1<rows){
	if(map[i+1][j]=='_' && i+1<rows ){
		matmos[i+1][j]=counter;
		map[i+1][j]='G';
	} }
	if(i+2<rows){
	 if(map[i+2][j]=='_' && i+2<rows) {
		matmos[i+2][j]=counter;
		map[i+2][j]='G';
	}}
	if(i-1>=0) {        
	 if (i-1>=0 && map[i-1][j]=='_') {
		matmos[i-1][j]=counter;
		map[i-1][j]='G';
	 }}
	if(i-2>=0){
	 if(i-2>=0 && map[i-2][j]=='_') {
		matmos[i-2][j]=counter;
		map[i-2][j]='G';
	}}
	if(j-2>=0){
	 if(j-2>=0 && map[i][j-2]=='_'){
		matmos[i][j-2]=counter; 
		map[i][j-2]='G';
	}}
	if(j-1>=0){
	 if(j-1>=0 && map[i][j-1]=='_'){
		matmos[i][j-1]=counter; 
		map[i][j-1]='G';
	}}
	if(j+2<cols){
	 if(map[i][j+2]=='_' && j+2<cols){
		matmos[i][j+2]=counter; 
		map[i][j+2]='G';
	}}
	if(j+1<cols){
	 if(map[i][j+1]=='_' && j+1<cols){
		matmos[i][j+1]=counter; 
		map[i][j+1]='G';
	}}
	//diagonali
	if(i+1<rows && j+1<cols){
	 if(map[i+1][j+1]=='_' && i+1<rows && j+1<cols){
		matmos[i+1][j+1]=counter; 
		map[i+1][j+1]='G';
	}}
	if(i-1>=0 && j+1<cols){ 
	 if(map[i-1][j+1]=='_' && i-1>=0 && j+1<cols){
		matmos[i-1][j+1]=counter; 
		map[i-1][j+1]='G';
	}}
	if(i-1>=0 && j-1>=0) {
	 if(map[i-1][j-1]=='_' && i-1>=0 && j-1>=0){
		matmos[i-1][j-1]=counter; 
		map[i-1][j-1]='G';
	}}
	if(j-1>=0 && i+1<rows){
	 if(map[i+1][j-1]=='_' && i+1<rows && j-1>=0){
		matmos[i+1][j-1]=counter; 
		map[i+1][j-1]='G';
	}}
	for(unsigned d=0;d<rows;d++){
			for(unsigned k=0;k<cols;k++){
				output<<matmos[d][k]<<" ";
			}
			output<<endl;
		}
		output<<endl;
}



int main(){
	unsigned righe,colon,counter;
	unsigned uscita[2];
	ifstream input("input (1).txt");
	ofstream output("output (2).txt");
	while(!input.eof()){
		
		//esci=false;
		counter=1;
		vector<unsigned> percorsi;
		input>>righe>>colon;
		char** map=new char* [righe];
		short** maptrace=new short* [righe];
		for(unsigned i=0;i<righe;i++){
			maptrace[i]=new short[colon];
			map[i]=new char[colon];}
			/*for(unsigned i=0;i<righe;i++){
				for(unsigned j=0;j<colon;j++){
					map[i][j]='0';
					}
				}*/	
		for(unsigned i=0;i<righe;i++){
			for(unsigned j=0;j<colon;j++){
				input>>map[i][j];
				//cout<<map[i][j]<<" ";
				if(map[i][j]=='U') {
					cout<<"ciao uscita "<<i<<j<<endl;
					uscita[0]=i;uscita[1]=j;
					map[i][j]='_';}
				if(map[i][j]=='X') {
					cout<<"ciao ostacolo "<<i<<j<<endl;
					maptrace[i][j]=-1;}
				if(map[i][j]=='E') {
					cout<<"ciao entrata "<<i<<j<<endl;
					maptrace[i][j]=0;}
			}
		}
		for(unsigned i=0;i<righe;i++){
			for(unsigned j=0;j<colon;j++){
				if(map[i][j]=='U') {
					cout<<"ciao uscita "<<i<<j<<endl;
					map[i][j]='_';}
			}
		}
		//cout<<endl;cout<<endl;
		for(unsigned i=0;i<righe;i++){
			for(unsigned j=0;j<colon;j++){
				//if(i!=uscita[0] || j!=uscita[1]){
				output<<map[i][j]<<" ";
				cout<<map[i][j]<<" ";//}
				/*else {
					output<<"U ";
				    cout<<"U ";}*/
			}
			output<<endl;
			cout<<endl;
		}	
		output<<endl<<endl;
		cout<<endl;
		/*for(unsigned i=0;i<righe;i++){
			for(unsigned j=0;j<colon;j++){
				cout<<maptrace[i][j]<<" ";
			}
			cout<<endl;
		}*/
		unsigned d=0;
		while(d<=max(righe,colon)*2){
			//cout<<"counter fuori "<<counter;
			for(unsigned i=0;i<righe;i++){
				for(unsigned j=0;j<colon;j++){
					if(map[i][j]=='E'){
						map[i][j]='M';
						cambioattornoE(output,map,maptrace,righe,colon,i,j,counter);
						for(unsigned i=0;i<righe;i++){
							for(unsigned j=0;j<colon;j++){
								//if(i!=uscita[0] || j!=uscita[1]){
									output<<map[i][j]<<" ";//}
								/*else {
									output<<"U ";}*/
							}
							output<<endl;
						}	
						output<<endl<<endl;
					}
				}
			}
			for(unsigned i=0;i<righe;i++){
				for(unsigned j=0;j<colon;j++){
					if(map[i][j]=='G'){
						map[i][j]='E';
						for(unsigned i=0;i<righe;i++){
							for(unsigned j=0;j<colon;j++){
								//if(i!=uscita[0] || j!=uscita[1]){
									output<<map[i][j]<<" ";//}
								/*else {
									output<<"U ";}*/
							}
							output<<endl;
						}	
						output<<endl<<endl;
					}
				}
			}
			d++;counter++;
			
		}	
		for(unsigned i=0;i<righe;i++){
			for(unsigned j=0;j<colon;j++){
				cout<<maptrace[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
		for(unsigned i=0;i<righe;i++){
			for(unsigned j=0;j<colon;j++){
				//if(i!=uscita[0] || j!=uscita[1])
				cout<<map[i][j]<<" ";
				//else cout<<"U ";
			}
			cout<<endl;
		}	
		cout<<endl;
		cout<<maptrace[uscita[0]][uscita[1]]<<" uscita "<<uscita[0]<< " e "<<uscita[1];
		for (unsigned i = 0; i < righe; i++)
  			delete [] map[i];
		delete [] map;
	}
}
