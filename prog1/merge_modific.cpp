#include<iostream>
#include<windows.h>

using namespace std;
void sort(int arr[],int size)
{
int temp;
for(int i=0;i<size;i++)
{ for(int j=0;j<(size-1)-i;j++)
{
 if(arr[j]>arr[j+1])
  {
   temp=arr[j];
   arr[j]=arr[j+1];
   arr[j+1]=temp;
   }
 }
 }
 }
int main()
{
int temp,k=0;
int a[5]={5,3,8,2,9};
int b[5]={0,19,23,11,10},c[10];
for(int i=0;i<10;i++)
{ if(i>4)
   {
   c[i]=b[k];
   k++ ;
   }
  else
  c[i]=a[i];
}
for(int j=0;j<10;j++)
cout<<"\n"<<c[j];
cout<<"\n\n\n";
sort(c,10);
cout<<"Sorted=\n";
for(int r=0;r<10;r++)
cout<<"\n"<<c[r];
getch();
}?
