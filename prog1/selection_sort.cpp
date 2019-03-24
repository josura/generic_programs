//Programmer: dead God aka Locicero Giorgio
//programma per sort di due array con selection sort

#include <iostream>
#include <cstdlib>
#include<windows.h>

using namespace std;

int* Concatenation(int size1, int size2, int* arr1,int* arr2){
	int *result= new int[size1+size2];

	for (int i=0; i<size1; i++) {

		result[i]=arr1[i];
	}

	for (int i=0; i < size2; i++) {

		result[size1 + i] = arr2[i];
	}

	return result;
	/*for (i=0; i<(size1+size2);i++){
		if (i<size1){
			array[i]=arr1[i];
		}
		else {                                //parte brutta
			array[i]=arr2[i-size2];
		}		
	}     return array;*/ 
}
void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}
 
void selectSort(int arr[], int size)
{
    int i, j, min_el;									
    for (i = 0; i < size-1; i++)						 
    {        
        min_el = i;   									// minimo elemento
        for (j = i+1; j < size; j++)
          	if (arr[j] < arr[min_el])
           	    min_el = j;
 	   	swap(arr[min_el], arr[i]);                // Swap 
    }
}
void printArray(int* arr, int size) {

	for (int i=0; i< size-1; i++) {

		cout<<arr[i]<< ", ";
	}
	cout<<arr[size-1];
}
int main()
{
	int sizeA,sizeB,i;
    int arr_A[sizeA],arr_B[sizeB];    
    cout<<"enter the size of the first array\n";
    cin >> sizeA;
    cout<<"\n enter the first array elements";
    for (i = 0; i < sizeA; i++)
    {
        cin>> 
		arr_A[i];
    }
    system("cls");
    cout<<"enter the size of the second array\n";
    cin >> sizeB;
    cout<<"\n enter the second array elements";
    for (i = 0; i < sizeB; i++)
    {
        cin>> 
		arr_B[i];
    }
    int size = sizeA+sizeB;
  	int* array = Concatenation(sizeA, sizeB, arr_A, arr_B);
  	selectSort(array,size);		
	cout<<"\nSorted list is as follows\n";
    printArray(array,size);
    return 0;
}


/*
void print_arr1( int size1){
	double *parr;
	int i;
	double arr1[i];                                     //print array ignorante
	parr=arr1;
	for (int i=0; i<size1 ;i++){
		cout << "Value of var[" << i << "] = ";
      	cout << *parr << endl;	
		parr++;
	}
}*/

