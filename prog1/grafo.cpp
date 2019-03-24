#include <iostream>
#include<climits>

#define inf 9999999

using namespace std;

template<class T>
class MGraph{
	int numver,numarc,max;
	T **K;
	int **M,**dist,**pred;
	int find_index(T el){
		for(int i=0;i<numver;i++){
			if(*K[i]==el){return i;}		
		}
		return -1; 
	}	
	public:
		MGraph(int n){
			max=n;
			numver=numarc=0;
			K= new T*[n];
			M=new int*[n];
			dist=new int*[n];
			pred=new int*[n];
			for(int i=0;i<n;i++){
				M[i]=new int[n];
				dist[i]=new int[n];
				pred[i]=new int[n];		
				for(int j=0;j<n;j++){
					M[i][j]=inf;
					pred[i][j]=-1;					
				}			
			}
			for(int j=0;j<n;j++){
				M[j][j]=0;					
			}
		}
		void addnode(T el){
			if(numver==max)return; 
			if(find_index(el)>=0)return;
			K[numver]=new T(el);
			numver++; 
		}
		void addedge(T el1,T el2,int peso){
			int i=find_index(el1);
			int j=find_index(el2);
			if(i<0 || j<0)return;
			M[i][j] =peso;
			pred[i][j]=i;
		}
		int floydWarshall (T sorge,T dest){ 
    			int i, j, k; 
    			for (i = 0; i < numver; i++) 
       	 			for (j = 0; j < numver; j++) 
            				dist[i][j] = M[i][j]; 
    			for (k = 0; k < numver; k++) { 
        			for (i = 0; i < numver; i++) { 
            				for (j = 0; j < numver; j++) { 
                				if (dist[i][k] + dist[k][j] < dist[i][j]){ 
									pred[i][j]=pred[k][j];                    				
									dist[i][j]=dist[i][k] + dist[k][j]; 
								}
            				} 
       			 	} 
    			} 
    			return dist[find_index(sorge)][find_index(dest)];
		} 
		void stamparicorsiva(int sorge,int dest){
			if(*K[sorge]==*K[dest]) cout<<*K[sorge]<<" ";
			else{
				if(pred[sorge][dest]==-1){
					cout<<"non esiste nessun cammino";			
				}			
				else{
					stamparicorsiva(sorge,pred[sorge][dest]);
					cout<<*K[dest]<<" ";		
				}
			}
		}
		void stampacammino(T sorge, T dest){
			int s=find_index(sorge),d=find_index(dest);
			if(s<0 || d<0)return;	
			stamparicorsiva(s,d);	
		}
};


int main(){	
	MGraph<int> grafo(4);
	grafo.addnode(1);grafo.addnode(4);grafo.addnode(7);grafo.addnode(3);
	grafo.addedge(1,3,50);grafo.addedge(4,7,30);grafo.addedge(7,1,20);grafo.addedge(3,4,70);
	cout<<"distanza minima "<<grafo.floydWarshall(1,7)<<endl;
	cout<<"cammino :";
	grafo.stampacammino(1,7);

}
