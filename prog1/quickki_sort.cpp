//programmer:uomo deddino AKA voglio morire AKA Locicero Giorgio
//quick_sorting an array

#include<iostream>
#include<ctime>
#include<cstdlib>
#define SIZE(array) (sizeof(array)/sizeof(array[0]))

using namespace std;

void swap(int &a, int &b){
	int temp=a;
	a=b;
	b=temp;
}


int random_partition(int* arr, int start, int end){
    srand(time(0));
    int pivotIndex = start + rand() % (end-start+1);
    int pivot = arr[pivotIndex];
    swap(arr[pivotIndex], arr[end]); 
    pivotIndex = end;
    int i = start -1;
    for(int j=start; j<=end-1; j++){
        if(arr[j] <= pivot){
            i = i+1;
            swap(arr[i], arr[j]);
        }
    }
 	swap(arr[i+1], arr[pivotIndex]);
    return i+1;
}
 
void quickSort(int* arr, int start, int end)
{
    if(start < end) {
        int mid = random_partition(arr, start, end);
        quickSort(arr, start, mid-1);
        quickSort(arr, mid+1, end);
    }
}

void printArray(int *array, int size){
        for(int i = 0; i < size; i++){
                if(!i) cout << '[';
                cout << *(array + i) << (i == size-1 ? ']' : '\t');
        }
        return;
}

int main(){
    int arr[] = {2,5,7,1,10,8,9,456,234,1,666};
  	int size=SIZE(arr);
	quickSort(arr,0,size-1);		
	cout<<"\nSorted list is as follows\n";
    printArray(arr,size);
    return 0;
}
