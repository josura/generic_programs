#include<iostream>
#define SIZE(array) (sizeof(array)/sizeof(array[0]))

int salpiu(long *S,int size){
	int inimax = 0,inicorr = 0,salmax = 0,salcorr,i;
	for (i=1; i<size; i++) {
		if(S[i]<S[i-1]) {
			salcorr=i-inicorr;
			if(salcorr>salmax) {
				inimax = inicorr;
				salmax= salcorr;
			}
			inicorr=i;
		}
	}
	if (inicorr>salmax)
		return inicorr;
	else return inimax;
}

int sla(long *S,int size){
	int indi=0,sal=0,salmax=0,i=0,j;
	//con una sola iterazione non funziona,il metodo è stato però riscritto sopra
	/*while(i<size-1 ){
		j=i+1;
		if(S[j]>=S[i]){
			j++;
			sal++;
			//std::cout<<"shout"<<sal;
		}
		if (sal>salmax && S[j]<S[i]){
			indi=i;
			salmax=sal;
			sal=1;
			//std::cout<<"shit"<<salmax<<"\n";
		}
		i=j+1;
	}*/
	while(i<size-1){
		j=i+1;
		while(j<size && S[j]>=S[i]){
			j++;
			sal++;
		}
		if (sal>salmax && S[j]<S[i]){
			indi=i;
			salmax=sal;
			sal=0;
		}
		i=j+1;
	}
	return indi;
} 

int main(){
	long array[]={3,3,2,3,4,5,6,7,1,2,1,27,28,29,33,34,35,36,37};
	std::cout<<sla(array,SIZE(array));
	std::cout<<salpiu(array,SIZE(array));
}
