#include "MatrixMat.h"
#include "Fractions.h"

int main(){
	unsigned rows,cols;
	cout<<"enter the number of rows and columns of the matrix:\n";
	cin>>rows>>cols;
	Matrix<Fraction<int> > piss(rows,cols,0.0);	
	cout<<"insert the element of the matrix \n"	;	
	for(int i=0;i<piss.get_rows();i++){
		for(int j=0;j<piss.get_cols();j++){
			cout<<"\aa["<<i<<"]["<<j<<"] = ";
			cin>>piss(i,j);
		}
	}
	cout<<"\n matrix: \n";
	cout<<piss;	
	if(rows==cols){
		//shit.operator<<(cout);
		cout<<"\n \n inverse of the matrix";
		//Matrix<float> shit=piss.inverse();
		cout<<"\n \n"<<piss.inverse();
	}
    cout<<"il rango della matrice e' : "<<piss.rank();	
	cout<<"\n \n ciao sono giorgio ";	
	unsigned suca,hellcounter=0;	
	cin>>suca;	
	while(suca==666){
		cout<<"welcome to hell \n want to continue?";
		cin>>suca;
		hellcounter++;
		if(hellcounter>=13)
			cout<<"are you to continue: y/n /n";
	}
	return 0;
}
