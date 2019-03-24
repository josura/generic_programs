//Programmatore:josura aka Locicero Giorgio
//sorting di due array in un nuovo array con merge sort

#include <iostream>
#include<cstdlib>
#include<windows.h>
 
using namespace std;
 
int* Concatenation(int size1, int size2, int* arr1,int* arr2){
	int *result= new int[size1+size2];
	for (int i = 0; i < size1; i++) {
		result[i] = arr1[i];
	}                                                  //there is no need to concatenate, but the process will be kind of faster like this, i'm gonna change in the future otherwise
	for (int i = 0; i < size2; i++) {
		result[size1 + i] = arr2[i];
	}
	return result;
}

void printArray(int* arr, int size) {

	for (int i = 0; i < size - 1; i++) {

		cout << arr[i] << ", ";
	}
	cout << arr[size - 1];
}


void Merge(int * , int , int , int );
 
void MergeSort(int *array, int left, int right){
    int middle = (left+right)/2;
    if(left<right){
        MergeSort(array, left, middle);      //parte sinistra
        MergeSort(array, middle + 1, right);     //parte destra
        Merge(array, left, middle, right);      //merging
    }
}

void Merge(int *array, int left, int middle, int right)
{
    int tmp[right - left + 1];
    int pos = 0, leftposition = left, rightposition = middle + 1;
    while (leftposition <= middle && rightposition <= right)
    {
        if (array[leftposition] < array[rightposition]){
            tmp[pos++] = array[leftposition++];
        }
        else{
            tmp[pos++] = array[rightposition++];
        }
    }
    while (leftposition <= middle)
        tmp[pos++] = array[leftposition++];
    while (rightposition <= right)
        tmp[pos++] = array[rightposition++];
    int i;
    for (i = 0; i < pos; i++)
    {
        array[i + left] = tmp[i];
    }
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
    int* array = Concatenation(sizeA,sizeB,arr_A,arr_B);
    MergeSort(array, 0, size - 1);
    system("cls");
    cout<<" Arrays before sorting the elements inside:\n"<<endl;
    printArray(arr_A,sizeA);
    cout<<endl<<endl;
    printArray(arr_B,sizeB);
    cout<<endl;
    cout<<"\n Third array with the elements of the two arrays sorted \n";
    printArray(array, size);
    return 0;
}
