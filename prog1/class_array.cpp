#ifndef Arraycon
#define Arraycon
#include<iostream>
#include<string>
using namespace std;

class Array{
	public:
		Array(){
			items= new int[lenght];
			
		}
		~Array(){
			delete items;
		}
		void Lenght(int lenght){
			cout<<"enter lenght of the array";
			cin>>lenght
			for
		}
	private:
		int* items;	
};
#endif


