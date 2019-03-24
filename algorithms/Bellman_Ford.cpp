#include<fstream>
#include<cstdlib>
#include<iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

#define W 0
#define G 1
#define B 2
#define inf INT_MAX-1
#define negcycle INT_MAX


void stampa(int a[], int n){
	for(int i=0; i<n; i++){
		if (a[i]==inf) cout << "inf | ";
		else cout << a[i] << " | ";
	}
	cout << endl;
}

template<class H>
class MGraph{
	private:
		int len, n, m;
		int **M;
		H *K;
		int current_root;
		int t;
		int *d, *pi;
		
		int findIndex(H x){
			for(int i=0; i<n; i++){
				if(K[i]==x) return i;
			}
			return -1;
		}
	public:
		MGraph(int len){
			this->len=len;
			n=m=0;
			M=new int*[len];
			for(int i=0; i<len; i++){
				M[i]=new int[len];
				for(int j=0; j<len; j++){
					M[i][j]=inf;
				}
			}
			K=new H[len];
			d=new int[len];
			pi=new int[len];
			for(int i=0; i<len; i++) K[i]=0;
		}
		MGraph<H>* addNode(H k){
			if (n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n]=k;
			n++; return this;
		}
		MGraph<H>* addEdge(H x, H y, int peso){
			int i=findIndex(x);
			int j=findIndex(y);
			if(i<0 || j<0) return this;
			if(M[i][j]==inf){
				M[i][j]=peso;
				m++;
			}
			return this;
		}
    void print() {
      for (int i=0; i<n; i++) {
        cout << "(" << i << ", " << K[i] << ") : ";
        for (int j=0; j<n; j++) {
          if (M[i][j]!=inf) cout << K[j] << " "; // stampa solo gli elementi presenti
        }
        cout << endl;
      }
    }
    void Initialize_Single_Source(H sorgente){
    	for(int i=0; i<n; i++){
    		d[i]=inf;
    		pi[i]=-1;
		}
		d[findIndex(sorgente)]=0;
	}
	void Relax1(H u, H v){
		if(d[findIndex(u)]+M[findIndex(u)][findIndex(v)] < d[findIndex(v)]){
			d[findIndex(v)]=d[findIndex(u)]+ M[findIndex(u)][findIndex(v)];
			pi[findIndex(v)]=findIndex(u);
		}
	}
	void Relax(int u, int v){
		if(d[u]!=inf && d[u]+M[u][v] < d[v]){
	//		cout << "Sto rilassando l'arco: " << K[u] << " , " << K[v] << endl;
			d[v]=d[u]+M[u][v];
			pi[v]=u;
		}
	}
	int Bellman_Ford(H s, H dest){
		Initialize_Single_Source(s);
		for(int i=1; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					if(M[j][k]!=inf) Relax(j,k);
				}
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(M[i][j]!=inf && d[i]!=inf && d[j]>d[i]+M[i][j]) return negcycle;
			}
		}
	//	cout << "Array d: " << endl;
	//	stampa(d,n);
	//	cout << "Array pi: " << endl;
	//	stampa(pi,n);
		return d[findIndex(dest)];
	}
};

int main(){
	ifstream read;
	ofstream write;
	read.open("input.txt");
	if (read.fail())
	{
		cout<< "Apertura input.txt fallita!\n";
		exit(1);
	}
	write.open("output.txt");
	if(write.fail())
	{
		cout << "Non sono riuscito a scrivere l'output.txt!'\n";
		exit(1);
	}
	int n, m;
	string tipodato;
	string nodo1, peso;
	while(!read.eof()){
		read >> n >> m;
		read >> tipodato;
		if(tipodato=="int"){
			int elem;
			int nodo2;
			int sorgente, destinazione;
			MGraph<int> grafo(n);
			for(int i=0; i<n; i++){
				read >> elem;
				grafo.addNode(elem);
			}
			for(int i=0; i<m; i++){
				read >> nodo1 >> nodo2 >> peso;
				grafo.addEdge(atoi(nodo1.substr(1).c_str()), nodo2, atoi((peso.substr(0, peso.length()-1)).c_str()));
		//		cout << "Arco: " << atoi(nodo1.substr(1).c_str()) << " a " << nodo2 << endl;
			}
		//	grafo.print();
			read >> sorgente >> destinazione;
			int mindist=grafo.Bellman_Ford(sorgente, destinazione);
	//		cout << "sesamo";
			if(mindist==inf) write << "inf.";
			else if(mindist==negcycle) write << "undef.";
			else write << mindist;
			write << endl;
		}
		else if(tipodato=="double"){
			double elem;
			double nodo2;
			double sorgente, destinazione;
			MGraph<double> grafo(n);
			for(int i=0; i<n; i++){
				read >> elem;
				grafo.addNode(elem);
			}
			for(int i=0; i<m; i++){
				read >> nodo1 >> nodo2 >> peso;
				grafo.addEdge(atof(nodo1.substr(1).c_str()), nodo2, atof((peso.substr(0, peso.length()-1)).c_str()));
			}
			read >> sorgente >> destinazione;
			int mindist=grafo.Bellman_Ford(sorgente, destinazione);
	//		cout << "sesamo";
			if(mindist==inf) write << "inf.";
			else if(mindist==negcycle) write << "undef.";
			else write << mindist;
			write << endl;
		}
	}
	read.close();
	write.close();
	return 0;
}
