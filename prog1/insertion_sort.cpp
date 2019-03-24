//programmer: ai wont tu die so bedli AKA Locicero Giorgio AKA josura
//program to sort an array using insertion sort

#include<iostream>
#include<cstdlib>

using namespace std;

template<typename T>
void insertionSort(T* arr, int n)
{
    int j;
   	T numb;
   	for (unsigned i=1; i<n; i++){
       	numb=arr[i];
       	j=i-1;
       	while (j>= 0 && arr[j] > numb){
           	arr[j+1]=arr[j];
           	j=j-1;
       	}
       	arr[j+1]=numb;
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
	int size,i;   
    cout<<"enter the size of the first array\n";
    cin >> size;
    int *arr_A= new int[size];
    cout<<"\n enter the first array elements";
    for (i=0; i<size; i++)
    {
        cin>> arr_A[i];
    }
    system("cls");
  	insertionSort(arr_A,size);		
	cout<<"\nSorted list is as follows\n";
    printArray(arr_A,size);
    return 0;
}
