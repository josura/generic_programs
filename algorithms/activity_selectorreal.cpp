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
		friend ofstream& operator <<(ofstream& stream, Activity<T>& dx){
				stream<<" ("<<dx.start<<","<<dx.finish<<")";
				return stream;
		}
		friend ostream& operator <<(ostream& stream, Activity<T>& dx){
				stream<<" ("<<dx.start<<","<<dx.finish<<")";
				return stream;
		}
		bool operator <(const Activity<T>& dx)const{
			//if(finish<dx.finish) return true;
			if(start<dx.start) return true;
			else return false;
		}
		bool operator >(const Activity<T>& dx)const{
			//if(finish>dx.finish) return true;
			if(start>dx.start) return true;
			return false;
		}  
		bool operator ==(const Activity<T>& dx)const{
			//if(finish==dx.finish) return true;
			if(start==dx.start) return true;
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
	//int startfront=atti[0].start;
	for(unsigned i=1;i<n;i++){
		if(atti[i].start>=finishback){
			finishback=atti[i].finish;
			numeroact++;
		}
	}
	return numeroact;
}

template<class T>
Activity<T>* activity_selector(Activity<T>* atti, int n,int& numero,int& maxtem,int tempo=0){
	int m=activity_maximizer(atti,n);
	if(tempo==0)tempo=atti[n-1].finish;
	int** Tem=new int*[tempo+1];
	for(int i=0;i<=tempo;i++){
		Tem[i]=new int[n+1];
	}
	for(int i=0;i<=tempo;i++){
		Tem[i][0]=0;
	}
	for(int i=0;i<=n;i++){
		Tem[0][i]=0;
	}
	
	for(int i=1;i<=tempo;i++){
		for(int j=1;j<=n;j++){
			if(atti[j-1].finish>i){
				Tem[i][j]=Tem[i][j-1];
			}
			else{
				Tem[i][j]=max(Tem[i][j-1],Tem[atti[j-1].start][j-1]+(atti[j-1].finish-atti[j-1].start));				
			}
			/*if(atti[j-1].start>i){
				Tem[i][j]=Tem[i][j-1];
			}
			else{
				Tem[i][j]=max(Tem[i][j-1],Tem[atti[j-1].finish][j-1]+(atti[j-1].start-atti[j-1].finish));				
			}*/
			//cout<<Tem[i][j]<<" ";
		}
		//cout<<endl;
	}
	
	m=0;
	maxtem=Tem[tempo][n];
	for(unsigned j=n,i=tempo;i>0 && j>0 &&!(atti[j-1].start==0 && atti[j-1].finish==0);j--){
		if(Tem[i][j]-(atti[j-1].finish-atti[j-1].start)==Tem[atti[j-1].start][j-1]){
			m++;
			i=atti[j-1].start;
		}
		else if(Tem[i][j]==Tem[i][j-1]){						//parte giusta
			if(j>=2 && atti[j-2].finish>i)j--;
		}
	}
	Activity<T>* selez=new Activity<T>[m];
	numero=m;
	for(unsigned j=n,i=tempo,k=m-1;i>0 && j>0 && k>=0 &&!(atti[j-1].start==0 && atti[j-1].finish==0);j--){
		if(Tem[i][j]-(atti[j-1].finish-atti[j-1].start)==Tem[atti[j-1].start][j-1]){
			selez[k]=atti[j-1];
			i=atti[j-1].start;
			k--;
		}
		else if(Tem[i][j]==Tem[i][j-1]){
			if(j>=2 && atti[j-2].finish>i)j--;
			/*else if(j>=2 && atti[j-2].finish<=i){
				if(Tem[i][j-1]-(atti[j-2].finish-atti[j-2].start)==Tem[atti[j-2].start][j-2]){
					selez[k]=atti[j-2];
					i=atti[j-2].start;
					k--;
					j--;
				}
			}*/
		}
	}
	/*for(unsigned i=0;i<m;i++){
		cout<<selez[i];
	}
	cout<<endl;*/
	return selez;
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
    int numel,f=0;
    while(!input.eof() && f<100){
    	f++;
    	cout<<"ciao ";
		input>>numel;
		int numeroatt,maxt;
		Activity<int>* attivita=new Activity<int>[numel];
		for(int i=0;i<numel;i++){
			input>>attivita[i];
		}
		Activity<int>* selezione=activity_selector(attivita,numel,numeroatt,maxt);
		/*for(int i=0;i<numel;i++)
			cout<<attivita[i];
		cout<<endl;*/
		output<<maxt;//<<" "<<numeroatt;
		/*for(int i=0;i<numeroatt;i++)
			output<<selezione[i];*/
		output<<endl;
		//cin>>numel;	
	}
    output.close();
    input.close();
    return 0;
}
