//faro è un pisello e non ha messo la virgola quindi ciao

#include<algorithm>
#include<string>
#include<iostream>
#include<fstream>
#define W 0
#define G 1
#define Bla 2
#define inf len+1

using namespace std;

enum color{White,Grey,Black};

template <class T>
class Node {
	public:
	    T value;
		unsigned distance;
    	Node *father;
	    Node *left;
    	Node *right;
		color pergrafo;

	    Node(T val) {
    	    this->value = val;
			right=left=father=NULL;
			this->pergrafo=White;
			this->distance=unsigned(-1);
	    }

    	Node(unsigned distance,Node<T>* right=NULL, Node<T>* left=NULL,Node<T>* father=NULL,T val=0,color c=White) {
        	this->value = val;
	        this->left = left;
    	    this->right = right;
			this->father=father;
			this->pergrafo=c;
			this->distance=distance;
	    }
};

template<class T>
class Deque{
    T* arr;
    int head,tail,numel,MAX;
    public:
    int gethead()const{return head;}
    int gettail()const{return tail;}
    int getnumel()const{return numel;}
    bool Vuoto()const{return !numel;}
    bool Pieno()const{return numel==MAX;}
    Deque(unsigned size){
        head=tail=numel=0;
        MAX=size;
        arr=new T[size];
    }
    ~Deque(){
        delete [] arr;
    }
    Deque<T>* enqueue(T el){
        if(Pieno())return this;
        arr[tail]=el;
        tail=(tail+1)%MAX;
        numel++;
        return this;
    }
    T dequeue(){
        if(Vuoto())exit(0);
        T out=arr[head];
        head=(head+1)%MAX;
        numel--;
        return out;
    }
    friend ostream& operator <<(ostream& str,const Deque<T>& dx){
            for(int i=0;i<dx.getnumel();i++){
                str<<dx.arr[(i+dx.head)%dx.MAX]<<" ";
            }
            str<<endl;
            return str;
        }
};

template<class T>
class Stack{
    Node<T>* top;
    public:
        bool Vuoto(){return !top;}
        Node<T>* getop(){return top;}
        Stack():top(0){}
        ~Stack(){
            Node<T>* iter=top;
            while(iter){
                top=top->succ;
                delete iter;
                iter=top;
            }
        }
        void push(T el){
            Node<T>* nuovo=new Node<T>(el,top);
            top=nuovo;
        }
        T pop(){
            if(Vuoto())exit(0);
            T out=top->elem;
            Node<T>* elim=top;
            top=top->succ;
            delete elim;
            return out;
        }
        friend ostream& operator <<(ostream& str,const Stack<T>& dx){
            Node<T>* iter=dx.top;
            while(iter){
                str<<iter->elem<<" ";
                iter=iter->succ;
            }
            str<<endl;
            return str;
        }
};

void sorttop(int *arr,unsigned numver,int *f){
    int j;
    for(unsigned i=1;i<numver;i++){
        j=i-1;
        while(j>=0 && f[arr[j+1]]>f[arr[j]]){
            swap(arr[j],arr[j+1]);
            j--;
        }
    }
}

template<class  T>
class Mgraph{
    protected:
		T** K;
		short ** M;
		int len,numver,numarc,tim,current_root,numcycles;
		int* predecessore,*distance,*discovered,*finished,*roots,*coloDFS;
		int _findindex(T el){
			for(int i=0;i<numver;i++){
				if(*K[i]==el)return i;
			}
			return -1;
		}
	public:
		int getcycles(){return numcycles;}
		Mgraph(unsigned l){
			len=l;
			numarc=numver=0;
			K=new T*[len];
			M=new short*[len];
			distance=new int[len];
			predecessore=new int[len];
			discovered=new int[len];
			finished=new int[len];
			roots=new int[len];
			coloDFS=new int[len];
			for(int i=0;i<len;i++){
				M[i]=new short[len];
				K[i]=NULL;
				for(int j=0;j<len;j++){
					M[i][j]=0;
				}
			}
		}
		~Mgraph(){
			for(int i=0; i<len;i++){
				delete K[i];
				delete [] M[i];
			}
			delete [] K;
			delete [] M;
			delete [] distance;
			delete [] predecessore;
			delete [] discovered;
			delete [] finished;
			delete [] coloDFS;
		}
		Mgraph<T>* addNode(T el){
			if(numver==len) return this;
			if(_findindex(el)>=0) return this;
			K[numver]=new T(el);
			numver++;
			return this;
		}
		Mgraph<T>* addEdge(T el1,T el2){
			int i=_findindex(el1),j=_findindex(el2);
			if(i<0||j<0)return this;
			if(!M[i][j]){
				M[i][j]=1;
				numarc++;
			}
			return this;
		}
		void BFS(int p){
			int colo[len];
			Deque<int> coda(len);
			for(unsigned i=0;i<numver;i++){
				colo[i]=W;
				predecessore[i]=-1;
				distance[i]=inf;
			}
			colo[p]=G;
			//predecessore[p]=p;
			distance[p]=0;
			coda.enqueue(p);
			while(!coda.Vuoto()){
				int u=coda.dequeue();
				for(unsigned i=0;i<numver;i++){
					if(M[u][i]){
						if(colo[i]==W){
							colo[i]=G;
							coda.enqueue(i);
							distance[i]=distance[u]+1;
							predecessore[i]=u;
						}
					}
				}
				colo[u]=Bla;
			}
			for(int i=0; i<numver; i++) {
				cout << "[" << i << "]->";
				if(distance[i]==inf) cout << "inf." << endl;
				else cout << distance[i] << endl;
			}
			cout << endl;
		}
		int DFSvisit(int p){
			int cycle=0;
			discovered[p]=++tim;
			coloDFS[p]=G;
			roots[p]=current_root;
			for(int i=0;i<numver;i++)
				if(M[p][i]){
					if(coloDFS[i]==W){
						predecessore[i]=p;
						cycle|=DFSvisit(i);
					}
					if(coloDFS[i]==G) {
						numcycles++;
						cycle=1;
					}
				}
			coloDFS[p]=Bla;
			finished[p]=tim++;	
			return cycle;	
		}
		int DFS(){
			tim=0;
			int cycle=0;
			numcycles=0;
			for(int i=0;i<numver;i++){
				coloDFS[i]=W;
				predecessore[i]=-1;
			}
			for(int i=0;i<numver;i++){
				if(coloDFS[i]==W){
					current_root=i;
					cycle |= DFSvisit(i);
				}
			}
			return cycle;
		}
		void topsort(){
			int cycle=DFS();
			if(cycle){
				cout<<"il grafo contiene un ciclo";
				return;
			}
			int *arr= new int[numver];
			for(int i=0;i<numver;i++)arr[i]=i;
			sorttop(arr,numver,finished);
			for(int i=0;i<numver;i++){
				cout<<"("<<arr[i]<<","<<finished[arr[i]]<<")";
			}
			cout<<endl;
			delete [] arr;

		}
		void print(){
			/*for(int i=0; i<numver; i++){
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0;j<numver;j++)
					if(M[i][j]) cout<<*K[j]<<" ";
				cout<<endl;	
				}*/
			for(int i=0; i<numver; i++){
				cout << "("<<*K[i];
				for(int j=0;j<numver;j++)
					if(M[i][j]){
					 	cout<<","<<*K[j];
					}
				cout<<") ";	
				}	
				cout<<endl;	
		}	
		void print(ofstream& str){
			/*for(int i=0; i<numver; i++){
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0;j<numver;j++)
					if(M[i][j]) cout<<*K[j]<<" ";
				cout<<endl;	
				}*/
			for(int i=0; i<numver; i++){
				str << "("<<*K[i];
				for(int j=0;j<numver;j++)
					if(M[i][j]){
					 	str<<","<<*K[j];
					}
					str<<") ";	
				}	
				str<<endl;	
		}
		void printPath(int x) {
			if(distance[x]==0){ cout << *K[x];return;}				//caso base se si calcola la distanza tra il nodo e se stesso
			if(predecessore[x]==-1) cout << "no path";    //caso no path
			else {									//print del predecessore dopo aver richiamato printpath in modo da avere il percorso dal nodo in cui si sta calcolando la distanza e quello in cui si Ã¨ invocata printpath
				printPath(predecessore[x]);
				cout << "->" << *K[x]; 
			}
		}
		void printPath(T el1,T el2) {
				if(_findindex(el1)<0 || _findindex(el2)<0) {cout<<"elementi non trovati";return;}
				BFS(_findindex(el1));
				printPath(_findindex(el2));
		}
        void topsort(ofstream& str){
            int cycle=DFS();
			if(cycle){
				str<<"il grafo contiene un ciclo";
				return;
			}
			int *arr=new int[numver];
			for(int i=0;i<numver;i++)arr[i]=i;
			sorttop(arr,numver,finished);
			for(int i=0;i<numver;i++){
				str<<*K[arr[i]]<<" ";
			}
			str<<endl;
			delete [] arr;
        }
        friend ofstream& operator<<(ofstream& str, Mgraph& dx){
        	dx.topsort(str);
        	return str;
		}
		friend ostream& operator<<(ostream& str, Mgraph& dx){
        	dx.topsort();
        	return str;
		}
};

template<class T>
void insertionSortPointers(T** arr,int numver){
	T* numb;
	for(int i=1;i<numver;i++){
		int j=i-1;
		numb=arr[i];
		while (j>= 0 && *arr[j] > *numb){
           	arr[j+1]=arr[j];
           	j--;
       	}
       	arr[j+1]=numb;
	}
}

template<class T>
class MgraphSorted:public Mgraph<T>{
	public:
		MgraphSorted(unsigned numv):Mgraph<T>(numv){}
		MgraphSorted<T>* addNode(T el){
			Mgraph<T>::addNode(el);
			insertionSortPointers(this->K,this->numver);
			return this;
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
    cout<<"ciao ";
    string tipo,arco1,arco2;
    unsigned numver,numar;
	while(!input.eof()){
		//cout<<"hei";
        input>>numver>>numar>>tipo;
        arco1=arco2="";
        //cin>>arco1;
        if(tipo=="int"){
            int aux,aux2;
            MgraphSorted<int> grafo(numver);
            for(unsigned i=0;i<numver;i++){
            	input>>aux;
            	cout<<aux<<" ";
            	grafo.addNode(aux);
			}
			//cout<<"\n";
			//cout<<" grafo"<<grafo;
			grafo.print();
			for(unsigned i=0;i<numar;i++){
            	input>>arco1>>arco2;
            	//input>>arco1;
            	string nod2="";
            	/*string nod1="",nod2="";
            	int cosa=0;
            	for(unsigned i=1;(arco1[i]!=',');i++){
            		nod1+=arco1[i];
            		cosa=i+1;
				}
				//cout<<nod1<<" ";
            	for(unsigned i=cosa+1;(arco1[i]!=')');i++){
            		nod2+=arco1[i];
				}*/
				for(unsigned i=0;(arco2[i]!=')');i++){
            		nod2+=arco2[i];
				}
				//cout<<nod2<<endl;
				aux=atoi((arco1.substr(1)).c_str());
				//aux=atoi(nod1.c_str());
				aux2=atoi(nod2.c_str());
				cout<<aux<<" "<<aux2<<"\n";
            	grafo.addEdge(aux,aux2);
			}
			//grafo.DFS();
			//output<<grafo.getcycles()<<endl;
			grafo.print();
			grafo.print(output);
			//output<<grafo;
        }
        else if(tipo=="char"){
            char aux;
            MgraphSorted<char> grafo(numver);
            for(unsigned i=0;i<numver;i++){
            	input>>aux;
            	grafo.addNode(aux);
			}
			//cout<<"\n";
			for(unsigned i=0;i<numar;i++){
            	input>>arco1>>arco2;
            	//input>>arco1;
            	char nod1=arco1[1],nod2=arco2[0];
            	//char nod1=arco1[1],nod2=arco1[3];
            	grafo.addEdge(nod1,nod2);
			}
			//grafo.DFS();
			//output<<grafo.getcycles()<<endl;
			grafo.print();
			grafo.print(output);
			//output<<grafo;
        }
        else if(tipo=="double"){
            double aux,aux2;
            MgraphSorted<double> grafo(numver);
            for(unsigned i=0;i<numver;i++){
            	input>>aux;
            	grafo.addNode(aux);
			}
			//cout<<" grafo"<<grafo;
			for(unsigned i=0;i<numar;i++){
            	input>>arco1>>arco2;
            	//input>>arco1;
            	string nod2="";
            	//string nod1="",nod2="";
            	/*int cosa=0;
            	for(unsigned i=1;(arco1[i]!=',');i++){
            		nod1+=arco1[i];
            		cosa=i+1;
				}
				//cout<<nod1<<" ";
            	for(unsigned i=cosa+1;(arco1[i]!=')');i++){
            		nod2+=arco1[i];
				}*/
				for(unsigned i=0;(arco2[i]!=')');i++){
            		nod2+=arco2[i];
				}
				//cout<<nod2<<endl;
				aux=atof((arco1.substr(1)).c_str());
				//aux=atof(nod1.c_str());
				aux2=atof(nod2.c_str());
				//cout<<aux<<" "<<aux2<<"\n";
            	grafo.addEdge(aux,aux2);
			}
			//grafo.DFS();
			//output<<grafo.getcycles()<<endl;
			grafo.print();
			grafo.print(output);
			//output<<grafo;
        }
        //output<<endl;
    }
    output.close();
    input.close();
	return 0;
}
