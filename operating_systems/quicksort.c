#include<stdio.h>
#include <string.h>
void swap_str(char* a[], char* b[]){
    char* t = *a;
    *a = *b;
    *b = t;
}
int partition (char* arr[], int low, int high){
    char* pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++){
        if (strcmp(arr[j],pivot)<=0 && strlen(arr[j])<=strlen(pivot)){
            i++;
            swap_str(&arr[i], &arr[j]);
        }
    }
    swap_str(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(char* arr[], int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void printArray(char* arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
    printf("%s ", arr[i]);
    printf("\n");
}
int main(){
    char* arr[] = {"giorgio2", "giorgio1", "giorgiopiccolo", "giorgioz","giorgiomorto","giorgia", "giorgio","ali"};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    printf("The sorted array is: ");
    printArray(arr, n);
    return 0;
}
