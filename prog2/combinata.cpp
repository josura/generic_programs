#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class Combined{
	int testa,posizione,numel,MAX;
	T* elementi;
	int* puntatori;
	int find_index(T el){
		for(int i=0;i<numel;i++){
			if(elementi[i]==el)return i;
		}
		return -1;
	}
	void rearrange(int god){
		int iteratore=numel;
		posizione=0;
		numel=0;
		testa=-1;
		for(int i=0;i<iteratore;i++){
			if(i!=god)
				insert(elementi[i]);
		}
	}
	public:
		Combined(int k){
			testa=-1;
			posizione=numel=0;
			MAX=k;
			elementi=new T[k];
			puntatori=new int[k];
		}
		~Combined(){delete [] elementi;
		delete [] puntatori;
		}
		Combined<T>* insert(T el){
			elementi[posizione]=el;
			if(testa==-1){
				testa=posizione;
				puntatori[posizione]=-1;
				posizione++;
				numel++;
				return this;
			}
			if(el<elementi[testa]){
				puntatori[posizione]=testa;
				testa=posizione;
				posizione++;
				numel++;
				return this;
			}
			int prec=-1,i=testa;
			while(i!=-1 && elementi[i]<=el){
				prec=i;
				i=puntatori[i];
			}/*if(prec==-1){
				puntatori[posizione]=testa;
				testa=posizione;
				posizione++;
				numel++;
				return this;
			}*/
			puntatori[prec]=posizione;
			puntatori[posizione]=i;
			posizione++;
			numel++;
			return this;	
		}
		Combined<T>* delet(T el){
			int s=find_index(el);
			if(s==-1)return this;
			rearrange(s);
			return this;
		}
		void printlist(){
			int i=testa;
			while(i!=-1){
				
				i=puntatori[i];
			}
		}
		void printpointers(ofstream& str)const{
			for(int i=0;i<numel;i++){
				str<<puntatori[i]<<" ";
			}
			//str<<testa;
			str<<endl;
		}
		void printpointers(){
			for(int i=0;i<numel;i++){
				cout<<puntatori[i]<<" ";
			}
			//cout<<testa;
		}
};

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
	string op;
    int numel,aux;
    while(!input.eof()){
    	input>>numel;
    	Combined<int> listina(numel);
    	for(int i=0;i<numel;i++){
    		input>>op;
    		if(op[0]=='i'){
    			aux=atoi((op.substr(1)).c_str());
				listina.insert(aux);
				
    		}
    		else if(op[0]=='c'){
    			aux=atoi((op.substr(1)).c_str());
				listina.delet(aux);
				
    		}
		}
		//listina.printlist();
		//listina.printpointers();
		//cout<<endl;
		listina.printpointers(output);
    }
    
    output.close();
    input.close();
    return 0;
}
