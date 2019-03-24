#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

/*void mergeSort(int arr[], int l, int r)
{
   if (l < r)
   {
      int m = l+(r-l)/2; //Same as (l+r)/2 but avoids overflow for large l & h
      mergeSort(arr, l, m);
      mergeSort(arr, m+1, r);
      merge(arr, l, m, r);
   }
}

void mergeiterative(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}*/

void Merge(int *array, int sinistra, int centro, int destra)
{
    int* tmp=new int[destra - sinistra + 1];
    int pos = 0, leftposition = sinistra, rightposition = centro + 1;
    while (leftposition <= centro && rightposition <= destra)
    {
        if (array[leftposition] < array[rightposition]){
            tmp[pos++] = array[leftposition++];
        }
        else{
            tmp[pos++] = array[rightposition++];
        }
    }
    while (leftposition <= centro)
        tmp[pos++] = array[leftposition++];
    while (rightposition <= destra)
        tmp[pos++] = array[rightposition++];
    int i;
    for (i = 0; i < pos; i++)
    {
        array[i + sinistra] = tmp[i];
    }
}
 
void MergeSort(int *array, int left, int right,unsigned& conteggio){
    int middle = (left+right)/2;
    if(left<right){
        MergeSort(array, left, middle,conteggio);      //parte sinistra
        //conteggio+=array[left];
    	//cout<<array[left]<<"contegio"<<conteggio<<endl;
        MergeSort(array, middle +1, right,conteggio);     //parte destra
        Merge(array, left, middle, right);      //merging
    }
}


int main(){
	unsigned numele;
	ifstream input("input.txt");
	ofstream output("output.txt");
	while(!input.eof()){
		input>>numele;
		int* arr=new int[numele];
		for(unsigned i=0;i<numele;i++){
			input>>arr[i];		
		}
		unsigned somma=0;
		if(numele%2!=0)
			somma=arr[0]+arr[numele/2+1];
		else somma=arr[0]+arr[numele/2];
		MergeSort(arr,0, numele-1,somma);
		for(unsigned i=0;i<numele;i++){
			//cout<<arr[i]<<" ";		
		}
		cout<<endl<<somma<<endl;
		output<<somma<<endl;
	}
	
}
