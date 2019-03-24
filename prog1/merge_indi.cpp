#include<iostream>
#include<cstdlib>

int main(){
	int arr1[7]={16,3,2,8,20,23,1};
	int arr2[10]={14,25,35,31,4,9,67,13,22,3},arr3[17];
	int i,j,temp,k=0;
	for(i=0;i<17;i++){
		if(i>6){
			arr3[i]=arr2[k];
			k++;
		}
		arr3[i]=arr1[i]
	}
}
