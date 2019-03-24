#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

void cambioattornoE(char** map,unsigned short** matmos,unsigned rows,unsigned cols,int i,int j,unsigned counter){
	//orizzontali e verticali
	if(i+1<rows)
	if(map[i+1][j]=='_' && i+1<rows ){
		matmos[i+1][j]=counter;
		map[i+1][j]='G';
	} 
	if(i+2<rows)
	 if(map[i+2][j]=='_' && i+2<rows) {
		matmos[i+2][j]=counter;
		map[i+2][j]='G';
	}
	if(i-1>=0)         //{cout<<"ciao "<<i-1<<endl;}
	 if (map[i-1][j]=='_') {
		matmos[i-1][j]=counter;
		map[i-1][j]='G';
	}
	if(i-2>=0)
	 if(i-2>=0 && map[i-2][j]=='_') {
		matmos[i-2][j]=counter;
		map[i-2][j]='G';
	}
	if(j-2>=0)
	 if(j-2>=0 && map[i][j-2]=='_'){
		matmos[i][j-2]=counter; 
		map[i][j-2]='G';
	}
	if(j-1>=0)
	 if(j-1>=0 && map[i][j-1]=='_'){
		matmos[i][j-1]=counter; 
		map[i][j-1]='G';
	}
	if(j+2<cols)
	 if(map[i][j+2]=='_' && j+2<cols){
		matmos[i][j+2]=counter; 
		map[i][j+2]='G';
	}
	if(j+1<cols)
	 if(map[i][j+1]=='_' && j+1<cols){
		matmos[i][j+1]=counter; 
		map[i][j+1]='G';
	}
	//diagonali
	if(i+1<rows && j+1<cols)
	 if(map[i+1][j+1]=='_' && i+1<rows && j+1<cols){
		matmos[i+1][j+1]=counter; 
		map[i+1][j+1]='G';
	}
	if(i-1>=0 && j+1<cols) 
	 if(map[i-1][j+1]=='_' && i-1>=0 && j+1<cols){
		matmos[i-1][j+1]=counter; 
		map[i-1][j+1]='G';
	}
	if(i-1>=0 && j-1>=0) 
	 if(map[i-1][j-1]=='_' && i-1>=0 && j-1>=0){
		matmos[i-1][j-1]=counter; 
		map[i-1][j-1]='G';
	}
	if(j-1>=0 && i+1<rows)
	 if(map[i+1][j-1]=='_' && i+1<rows && j-1>=0){
		matmos[i+1][j-1]=counter; 
		map[i+1][j-1]='G';
	}
}



int main(){
	unsigned righe,colon,counter;
	unsigned uscita[2];
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		counter=1;
		vector<unsigned> percorsi;
		input>>righe>>colon;
		char** map=new char* [righe];
		unsigned short** maptrace=new unsigned short* [righe];
		for(unsigned i=0;i<righe;i++){
			maptrace[i]=new unsigned short[colon];
			map[i]=new char[colon];}
		for(unsigned i=0;i<righe;i++){
			for(unsigned j=0;j<colon;j++){
				input>>map[i][j];
				if(map[i][j]=='U') {
					uscita[0]=i;uscita[1]=j;
					map[i][j]='_';}
				if(map[i][j]=='X') {
					maptrace[i][j]=10000;}
				if(map[i][j]=='E') {
					maptrace[i][j]=0;}
			}
		}
		unsigned d=0;
		while(d<=max(righe,colon)*max(righe,colon)){
			//cout<<"counter fuori "<<counter<<endl;
			for(unsigned i=0;i<righe;i++){
				for(unsigned j=0;j<colon;j++){
					if(map[i][j]=='E'){
						map[i][j]='M';
						cambioattornoE(map,maptrace,righe,colon,i,j,counter);
					}
				}
			}
			for(unsigned i=0;i<righe;i++){
				for(unsigned j=0;j<colon;j++){
					if(map[i][j]=='G'){
						map[i][j]='E';
					}
				}
			}
			d++;counter++;
			
		}	
		cout<<"passi minimi "<<maptrace[uscita[0]][uscita[1]]<<endl;
		output<<maptrace[uscita[0]][uscita[1]]<<endl;
		for (unsigned i = 0; i < righe; i++)
  			delete [] map[i];
		delete [] map;
	}
}
