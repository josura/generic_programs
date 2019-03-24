#include <iostream>
#include<string>


bool strfind(string a, string b){
	for(int i=0;i<a.lenght();i++){
		int h=i;
		int k=0;
		while(h<s.lenght() && k<x.lenght() && a[h]==b[k]){
			h++,k++;
		}
		if(k==x.lenght())
		return true;
	}
	return false;
}
