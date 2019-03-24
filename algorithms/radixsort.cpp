#include<iostream> 
#include<fstream>
#include<algorithm>
#include<climits> 
#include <ctime>
using namespace std;

template<class T>
class Triple{
	public:
		T x,y,z;
		Triple():x(0),y(0),z(0){}
		Triple(T ax,T ay,T az):x(ax),y(ay),z(az){}
		T getx()const{return x;}
		T gety()const{return y;}
		T getz()const{return z;}
		bool operator <(const Triple<T>& dx){
			if(x<dx.x) return true;
			else if(x==dx.x && y<dx.y) return true;
			else if(x==dx.x && y==dx.y && z<dx.z) return true;
			return false;
		}
		bool operator >(const Triple<T>& dx){
			if(x>dx.x) return true;
			else if(x==dx.x && (y>dx.y)) return true;
			else if(x==dx.x && y==dx.y && z>dx.z) return true;
			return false;
		}  
		bool operator ==(const Triple<T>& dx){
			if(x==dx.x && y==dx.y && z==dx.z) return true;
			return false;
		} 
		bool operator <=(const Triple<T>& dx){
			if(*this<dx || *this==dx)return true;
			else return false;
		}
		bool operator >=(const Triple<T>& dx){
			if(*this>dx || *this==dx)return true;
			else return false;
		}
		void operator =(const Triple<T>& dx){
			x=dx.getx();
			y=dx.gety();
			z=dx.getz();
		}
		void stampa(ostream& stream)const{
			stream<<"("<<getx()<<","<<gety()<<","<<getz()<<")";
		}
		void stampa(ofstream& stream)const{
			stream<<"("<<getx()<<","<<gety()<<","<<getz()<<")";
		}
};

template<class T>
ostream& operator <<(ostream& stream,const Triple<T>& dx){
	dx.stampa(stream);
	return stream;
}

template<class T>
ofstream& operator <<(ofstream& stream,const Triple<T>& dx){
	dx.stampa(stream);
	return stream;
}

// funzione ausiliaria utilizzata per stampare gli elementi di un array A di dimensione n
template<class T>
void print(T *A, int n) {
	for(int i=0; i<n; i++)
		cout << A[i] << " ";
	cout << endl;
}



void CountingSort(int *A, int n,ofstream& str) {
	int max = A[0];
	int min = A[0];
	for(int i=1; i<n; i++) {
		if(max<A[i]) max=A[i];
		if(min>A[i]) min=A[i];
	}
	int range = max-min+1;
	int *B = new int[n];
	int *C = new int[range];
	for(int i=0; i<range; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[A[i]-min]++;
	for(int i=1; i<range; i++) C[i] += C[i-1];
	for(int i=n-1; i>=0; i--) {
		B[C[A[i]-min]-1] = A[i];
		C[A[i]-min]--;
	}
	for(int i=0; i<n; i++) A[i] = B[i];
	for(int i=0;i<range;i++) str<<C[i]<<" ";
}

void CountingSort(Triple<int> *A, int n,ofstream& str) {
	int max = A[0].x;
	int min = A[0].x;
	for(int i=1; i<n; i++) {
		if(max<A[i].x) max=A[i].x;
		if(min>A[i].x) min=A[i].x;
	}
	int range = max-min+1;
	Triple<int> *B = new Triple<int>[n];
	int *C = new int[range];
	for(int i=0; i<range; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[A[i].x-min]++;
	for(int i=1; i<range; i++) C[i] += C[i-1];
	for(int i=n-1; i>=0; i--) {
		B[C[A[i].x-min]-1]=A[i];
		C[A[i].x-min]--;
	}
	for(int i=0; i<n; i++) {
		A[i]=B[i];
	}
	for(int i=0;i<range;i++) str<<C[i]<<" ";
	delete [] B;
}

void CountingSort(int *A, int n,int esp) {
	int max = A[0];
	int min = A[0];
	for(int i=1; i<n; i++) {
		if(max<A[i]) max=A[i];
		if(min>A[i]) min=A[i];
	}
	int *B = new int[n];
	int *C = new int[10];
	for(int i=0; i<10; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[(A[i] / esp) % 10]++;
	for(int i=1; i<10; i++) C[i] += C[i-1];
	for(int i=n-1; i>=0; i--) {
		B[C[(A[i] / esp) % 10]-1] = A[i];
		C[(A[i] / esp) % 10]--;
	}
	for(int i=0; i<n; i++) A[i] = B[i];
}

void radixsort(int arr[], int n)
{
	int exp, mass=arr[0];
	for(int i=1;i<n;i++){
		if(mass<arr[i])mass=arr[i];
	}
	for (exp = 1; mass/exp > 0; exp *= 10)
		CountingSort(arr, n, exp);
}

int main(){
	ifstream input("input.txt");
    ofstream output("output.txt");
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
    string tipo="double";
    int numel;
    while(!input.eof()){
    	input>>numel;
    	//cin>>porco;
    	//cout<<numel<<" ";
    	if(tipo=="int"){
        	Triple<int>* arr=new Triple<int>[numel];
			for(int i=0; i<numel; i++){
				string coppia,nod1="",nod2="";
				input>>coppia;
    	    	int cosa=0;
       			for(unsigned i=1;(coppia[i]!=',');i++){
       				nod1+=coppia[i];
	      			cosa=i+1;
				}
    	    	for(unsigned i=cosa+1;(coppia[i]!=')');i++){
        		    nod2+=coppia[i];
				}
				arr[i].x=atoi(nod1.c_str());
				arr[i].y=atoi(nod2.c_str());
				/*string nod1="",arco2,nod2="";
	    		input>>nod1>>arco2;
	    		for(unsigned i=0;(arco2[i]!=')');i++){
            		nod2+=arco2[i];
				}
				arr[i].x=atoi((nod1.substr(1)).c_str());;
				arr[i].y=atoi(nod2.c_str());*/
			}
			cout<<endl;
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
				output << arr[i];
			}
        	output<<endl;
    	}
    	else if(tipo=="double"){
        	Triple<int>* arr=new Triple<int>[numel];
			for(int i=0; i<numel; i++){
				/*string coppia,nod1="",nod2="";
				input>>coppia;
				//cout<<coppia<<" ";
    	    	int cosa=0;
       			for(unsigned i=1;(coppia[i]!=',');i++){
       				nod1+=coppia[i];
	      			cosa=i+1;
				}
				//cout<<nod1<<" ";
    	    	for(unsigned i=cosa+1;(coppia[i]!=')');i++){
        		    nod2+=coppia[i];
				}
				//cout<<nod2+" ";
				arr[i].x=int(atof(nod1.c_str())*10);
				//cout<<"arr["<<i<<"].x="<<arr[i].x<<" ";
				arr[i].y=int(atof(nod2.c_str())*10);*/
				//cout<<"arr["<<i<<"].y="<<arr[i].y<<" ";
				string nod1="",arco2,nod2="";
				double we;
	    		input>>nod1>>we>>arco2;
	    		for(unsigned i=0;(arco2[i]!=')');i++){
            		nod2+=arco2[i];
				}
				arr[i].x=int(atof((nod1.substr(1)).c_str())*10);
				arr[i].y=int(we*10);
				arr[i].z=int(atof(nod2.c_str())*10);
			}
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
			output <<"("<<(arr[i].x)/10.0<<","<<(arr[i].y)/10.0<<","<<(arr[i].z)/10.0<<") ";
			}
        	output<<endl;
    	}
    	else if(tipo=="char"){
        	Triple<int>* arr=new Triple<int>[numel];
			for(int i=0; i<numel; i++){
				string nod1="",nod2="";
	    		input>>nod1>>nod2;
				arr[i].x=int(nod1[1]);
				arr[i].y=int(nod2[0]);
			}
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
			output <<"("<<char(arr[i].x)<<","<<char(arr[i].y)<<") ";
			}
        	output<<endl;
    	}
    	else if(tipo=="bool"){
        	Triple<int>* arr=new Triple<int>[numel];
			for(int i=0; i<numel; i++){
				string nod1="",arco2,nod2="";
	    		input>>nod1>>arco2;
	    		for(unsigned i=0;(arco2[i]!=')');i++){
            		nod2+=arco2[i];
				}
				arr[i].x=atoi((nod1.substr(1)).c_str());;
				arr[i].y=atoi(nod2.c_str());
			}
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
			output << arr[i]<<" ";
			}
        	output<<endl;
    	}
    }
    output.close();
    input.close();
}
