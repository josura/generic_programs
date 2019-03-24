#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>


using namespace std;

main(){
	unsigned numthief,maxcol,maxrow,auxx1,auxx2,auxy1,auxy2,maxtheft;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numthief;
		maxcol=0;
		maxrow=0;
		maxtheft=0;
		vector<unsigned> coordinate;
		for(unsigned i=0;i<numthief;i++){
			input>>auxx1>>auxy1>>auxx2>>auxy2;
			coordinate.push_back(auxx1);
			coordinate.push_back(auxy1);
			coordinate.push_back(auxx2);
			coordinate.push_back(auxy2);
		}
		
			/*	for(unsigned i=0;i<coordinate.size();i++){
					cout<<coordinate[i]<<" ";
				}*/
		
		for(unsigned i=0;i<coordinate.size();i++){
			if(i%2==0){
				if(coordinate[i]>maxcol)
					maxcol=coordinate[i];
			}
			else if(coordinate[i]>maxrow) maxrow=coordinate[i];		
		}
		//cout<<"max col"<<maxcol<<"maxrow"<<maxrow;
		unsigned** matrix= new unsigned*[maxrow];
		for (unsigned i = 0; i < maxrow; ++i)
    		matrix[i] = new unsigned[maxcol];	
		for(unsigned i=0;i<maxrow;i++)
			for(unsigned j=0;j<maxcol;j++)
				matrix[i][j]=0;
		for(unsigned i=0;i<coordinate.size();i+=4)
			for(unsigned j=min(coordinate[i+1],coordinate[i+3]);j<max(coordinate[i+1],coordinate[i+3]);j++)
				for(unsigned k=min(coordinate[i],coordinate[i+2]);k<max(coordinate[i],coordinate[i+2]);k++)
					matrix[j][k]++;
		for(unsigned i=0;i<maxrow;i++)
			for(unsigned j=0;j<maxcol;j++)
				if(matrix[i][j]>maxtheft)
					maxtheft=matrix[i][j];			
		output<<maxtheft<<endl;
		for (unsigned i = 0; i < maxrow; ++i)
    		delete [] matrix[i];
		delete [] matrix;
	}
	
}
