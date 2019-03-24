#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class Node{
    public:
        Node<T>* right,*left,*prec,*succ;
        T elem;
        int level;
        Node(T el,Node<T>* p=NULL){
            right=left=prec=NULL;
            succ=p;
            elem=el;
        }
        void setsucc(Node<T>* p){succ=p;}
};

template<class T>
class Coda{
	int head,tail,numel,MAX;
	T* arr;
	public:
		Coda(int k):MAX(k){
			arr=new T[k];
			head=tail=numel=0;
		}
		~Coda(){
			delete arr;	
		}
		T* getptrarr(){return arr;}
		int gethead(){return head;}
		bool Piena(){return (numel==MAX);}
		bool Vuota(){return !numel;}
		Coda<T>* enqueue(T el){
			if(Piena())return this;
			arr[tail]=el;
			tail=(tail+1)%MAX;
			numel++;
			return this;
		}
		T dequeue(){
			if(Vuota()) exit(1);
			T out=arr[head];
			head=(head+1)%MAX;
			numel--;
			return out;
		}
		friend ostream& operator<<(ostream& str,const Coda<T>& rx){
			int heade=rx.head;
			for(int i=0;i<rx.numel;i++){
				str<<rx.arr[(i+heade)%rx.MAX]<<" ";
			}
			str<<endl;
			return str;
		}
		friend ofstream& operator<<(ofstream& str,const Coda<T>& rx){
			int heade=rx.head;
			for(int i=0;i<rx.numel;i++){
				str<<rx.arr[(i+heade)%rx.MAX]<<" ";
			}
			str<<endl;
			return str;
		}
};

template<class T>
class Pila{
	Node<T>* top;
	void succe(){if (top)top=top->succ;}
	void succe(Node<T>* iter){if (iter)iter=iter->succ;}
	public:
		Pila():top(NULL){}
		~Pila(){
			Node<T>* iter=top;
			while(iter){
				iter=top->succ;
				delete top;
				top=iter;
			}
		}
		bool Vuoto(){return !top;}
		Pila<T>* push(T el){
			Node<T>* nuovo=new Node<T>(el,top);
			top=nuovo;
			return this;
		}
		T pop(){
			if(Vuoto())exit(1);
			T out=top->elem;
			Node<T>* elim =top;
			succe();
			delete elim;
			return out;
		}
		void travaso(Coda<T>& coda){
			while(!Vuoto()){	
				T elem=pop();
				coda.enqueue(elem);
			}
		}
		friend ostream& operator<<(ostream& str,const Pila<T>& rx){
			for(Node<T>* iter=rx.top;iter!=NULL;iter=iter->succ){
				str<<iter->elem<<" ";
			}
			str<<endl;
			return str;
		}
		friend ofstream& operator<<(ofstream& str,const Pila<T>& rx){
			for(Node<T>* iter=rx.top;iter!=NULL;iter=iter->succ){
				str<<iter->elem<<" ";
			}
			str<<endl;
			return str;
		}
};


int main()
{
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
    string tipo,operazione;
    int numel;
    while(!input.eof()){
    	cout<<"ciao ";
        input>>tipo;
		input>>numel;
		if(tipo=="int"){
            int elem;
			Coda<int> coda(numel);
			Pila<int> pila;
			for(int i=0; i<numel; i++){
				input >> operazione;
				if(operazione[0]=='e'){
					elem=atoi((operazione.substr(2)).c_str());
					coda.enqueue(elem);

				}
				else if(operazione[0]=='p'){
					if(operazione[1]=='o'){
						pila.pop();
					}
					else{
						elem=atoi((operazione.substr(2)).c_str());
						pila.push(elem);
					}
				}
				else if(operazione[0]=='t'){
					pila.travaso(coda);
				}
				else if(operazione[0]=='d'){
					coda.dequeue();
				}
				//cout<<coda<<" ah ";
			}
			output<<coda;
			//cout<<" finale "<<coda;
            
        }
        else if(tipo=="double"){
            double elem;
            Pila<double> pila;
			Coda<double> coda(numel);
			for(int i=0; i<numel; i++){
				input >> operazione;
				if(operazione[0]=='e'){
					elem=atof((operazione.substr(2)).c_str());
					coda.enqueue(elem);

				}
				else if(operazione[0]=='p'){
					if(operazione[1]=='o'){
						pila.pop();
					}
					else{
						elem=atof((operazione.substr(2)).c_str());
						pila.push(elem);
					}
				}
				else if(operazione[0]=='t'){
					pila.travaso(coda);
				}
				else if(operazione[0]=='d'){
					coda.dequeue();
				}
				//cout<<coda<<" ah ";
			}
			output<<coda;
			//cout<<" finale "<<coda;
        }
        else if(tipo=="char"){
            char elem;
            Pila<char> pila;
			Coda<char> coda(numel);
			for(int i=0; i<numel; i++){
				input >> operazione;
				if(operazione[0]=='e'){
					elem=operazione[2];
					coda.enqueue(elem);

				}
				else if(operazione[0]=='p'){
					if(operazione[1]=='o'){
						pila.pop();
					}
					else{
						elem=operazione[2];
						pila.push(elem);
					}
				}
				else if(operazione[0]=='t'){
					pila.travaso(coda);
				}
				else if(operazione[0]=='d'){
					coda.dequeue();
				}
				//cout<<coda<<" ah ";
			}
			output<<coda;
			//cout<<" finale "<<coda;
        }
        else if(tipo=="bool"){
            bool elem;
            Pila<bool> pila;
			Coda<bool> coda(numel);
			for(int i=0; i<numel; i++){
				input >> operazione;
				if(operazione[0]=='e'){
					//cout<<"enqu ";
					elem=bool(atoi((operazione.substr(2)).c_str()));
					coda.enqueue(elem);

				}
				else if(operazione[0]=='p'){
					if(operazione[1]=='o'){
						//cout<<"pop ";
						pila.pop();
					}
					else{
						//cout<<"push ";
						elem=bool(atoi((operazione.substr(2)).c_str()));
						pila.push(elem);
					}
				}
				else if(operazione[0]=='t'){
					//cout<<"travaso ";
					pila.travaso(coda);
				}
				else if(operazione[0]=='d'){
					//cout<<"deque ";
					coda.dequeue();
				}
				//cout<<coda<<" ah ";
			}
			output<<coda;
			//cout<<" finale "<<coda;
        }
    }
    output.close();
    input.close();
    return 0;
}
