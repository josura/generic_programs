#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

template<class T>
int partition(T *arr, const int left, const int right) {
    const int mid = left + (right - left) / 2;
    const T pivot = arr[mid];
    // move the mid point value to the front.
    std::swap(arr[mid],arr[left]);
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while(i <= j && arr[i] <= pivot) {
            i++;
        }

        while(i <= j && arr[j] > pivot) {
            j--;
        }

        if (i < j) {
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i - 1],arr[left]);
    return i - 1;
}

template<class T>
void quicksort(T *arr, const int left, const int right, const int sz){

    if (left >= right) {
        return;
    }
    int part = partition(arr, left, right);
    quicksort(arr, left, part - 1, sz);
    quicksort(arr, part + 1, right, sz);
}

template<class T>
void quicksort(T* ar, int n){
	quicksort(ar,0,n-1,n);
}


template<class T>
class Activity{
	public:
		int number,start,finish,i;
		Activity(T _start=0,T _finish=0 , unsigned _number=0):start(_start),finish(_finish),number(_number){
			i=number;
			i++;
		}
		friend ifstream& operator >>(ifstream& stream, Activity<T>& dx){
			string coppia,nod1="",nod2="";
				//stream>>coppia;
				stream>>nod1>>nod2;
    	    	//int cosa=0;
       			/*for(unsigned i=1;(coppia[i]!=',');i++){
       				nod1+=coppia[i];
	      			cosa=i+1;
				}
    	    	for(unsigned i=cosa+1;(coppia[i]!=')');i++){
        		    nod2+=coppia[i];
				}*/
				dx.start=atoi(nod1.substr(1).c_str());
				dx.finish=atoi(nod2.substr(0,nod2.size()-1).c_str());
			return stream;
		}
		bool operator <(const Activity<T>& dx)const{
			if(finish<dx.finish) return true;
			else return false;
		}
		bool operator >(const Activity<T>& dx)const{
			if(finish>dx.finish) return true;
			return false;
		}  
		bool operator ==(const Activity<T>& dx)const{
			if(finish==dx.finish) return true;
			return false;
		} 
		bool operator <=(const Activity<T>& dx)const{
			if(*this<dx || *this==dx)return true;
			else return false;
		}
		bool operator >=(const Activity<T>& dx)const{
			if(*this>dx || *this==dx)return true;
			else return false;
		}
		void operator =(const Activity<T>& dx){
			start=dx.start;
			finish=dx.finish;
			number=dx.number;
		}
};

template<class T>
int activity_maximizer(Activity<T>* atti, int n){
	if(n==0)return 0;
	if(n==1)return 1;
	quicksort(atti,n);
	int numeroact=1;
	int finishback=atti[0].finish;
	for(unsigned i=1;i<n;i++){
		if(atti[i].start>=finishback){
			finishback=atti[i].finish;
			numeroact++;
		}
	}
	return numeroact;
}

int main(){
	ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    if (input.fail())
	{
		cout<< "Apertura input.txt fallita!\n";
		exit(1);
	}
	if(output.fail())
	{
		cout << "Non sono riuscito a scrivere l'output.txt!'\n";
		exit(1);
	}
    int numel;
    while(!input.eof()){
    	cout<<"ciao ";
		input>>numel;
		Activity<int>* attivita=new Activity<int>[numel];
		for(int i=0;i<numel;i++){
			input>>attivita[i];
		}
		output<<activity_maximizer(attivita,numel)<<endl;
	}
    output.close();
    input.close();
    return 0;
}
