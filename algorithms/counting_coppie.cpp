#include<iostream> 
#include<fstream>
#include<algorithm>
#include<climits> 
#include <ctime>
using namespace std;

template<class T>
class Coppie{
	public:
		T x,y;
		Coppie():x(0),y(0){}
		Coppie(T ax,T ay):x(ax),y(ay){}
		T getx()const{return x;}
		T gety()const{return y;}
		bool operator <(const Coppie<T>& dx){
			if(x<dx.x) return true;
			else if(x==dx.x && y<dx.y) return true;
			return false;
		}
		bool operator >(const Coppie<T>& dx){
			if(x>dx.x) return true;
			else if(x==dx.x && (y>dx.y)) return true;
			return false;
		}  
		bool operator ==(const Coppie<T>& dx){
			if(x==dx.x && y==dx.y) return true;
			return false;
		} 
		bool operator <=(const Coppie<T>& dx){
			if(*this<dx || *this==dx)return true;
			else return false;
		}
		bool operator >=(const Coppie<T>& dx){
			if(*this>dx || *this==dx)return true;
			else return false;
		}
		void operator =(const Coppie<T>& dx){
			x=dx.getx();
			y=dx.gety();
		}
		void stampa(ostream& stream)const{
			stream<<"("<<getx()<<","<<gety()<<")";
		}
		void stampa(ofstream& stream)const{
			stream<<"("<<getx()<<","<<gety()<<")";
		}
};

template<class T>
ostream& operator <<(ostream& stream,const Coppie<T>& dx){
	dx.stampa(stream);
	return stream;
}

template<class T>
ofstream& operator <<(ofstream& stream,const Coppie<T>& dx){
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

void CountingSort(Coppie<int> *A, int n,ofstream& str) {
	int max = A[0].x;
	int min = A[0].x;
	for(int i=1; i<n; i++) {
		if(max<A[i].x) max=A[i].x;
		if(min>A[i].x) min=A[i].x;
	}
	int range = max-min+1;
	Coppie<int> *B = new Coppie<int>[n];
	int *C = new int[range];
	for(int i=0; i<range; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[A[i].x-min]++;
	for(int i=1; i<range; i++) C[i] += C[i-1];
	for(int i=n-1; i>=0; i--) {
		B[C[A[i].x-min]-1].x = A[i].x;
		B[C[A[i].x-min]-1].y = A[i].y;
		C[A[i].x-min]--;
	}
	for(int i=0; i<n; i++) {
		A[i].x = B[i].x;
		A[i].y = B[i].y;
	}
	for(int i=0;i<range;i++) str<<C[i]<<" ";
	//delete [] B;
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
        	Coppie<int>* arr=new Coppie<int>[numel];
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
        	Coppie<int>* arr=new Coppie<int>[numel];
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
	    		input>>nod1>>arco2;
	    		for(unsigned i=0;(arco2[i]!=')');i++){
            		nod2+=arco2[i];
				}
				arr[i].x=int(atof((nod1.substr(1)).c_str())*10);
				arr[i].y=int(atof(nod2.c_str())*10);
			}
			CountingSort(arr,numel,output);
			for(int i=0; i<numel; i++){
			output <<"("<<(arr[i].x)/10.0<<","<<(arr[i].y)/10.0<<") ";
			}
        	output<<endl;
    	}
    	else if(tipo=="char"){
        	Coppie<int>* arr=new Coppie<int>[numel];
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
        	Coppie<int>* arr=new Coppie<int>[numel];
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
