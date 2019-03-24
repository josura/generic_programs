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
        Node(T el){
            right=left=prec=succ=NULL;
            elem=el;
        }
        void setsucc(Node<T>* p){succ=p;}
};
template<class T>
class Pilanodo{
    private:
        Node<T>* top;
        unsigned numel;
    public:
        Pilanodo<T>* succ;
        Pilanodo<T>* getSucc(){return succ;}
        Pilanodo(){
            top=NULL;
            succ=NULL;
            numel=0;
        }
        void setsucc(Pilanodo<T>* p){succ=p;}
        /*~Pilanodo(){
            Node<T>* iter=top;
            while(top){
                iter=top->succ;
                delete top;
                top=iter;
            }
        }*/
        bool Vuota(){return !top;}
        Pilanodo<T>* push(T el){
            if(Vuota()){
                //cout<<" metto in pila in testa"<<el<<" ";
                top=new Node<T>(el);
                numel++;
                return this;
            }
            Node<T>* nuovo=new Node<T>(el);
            //cout<<" metto in pila"<<el<<" ";
            nuovo->succ=top;
            top=nuovo;
            numel++;
            return this;
        }
        T pop(){
            if(Vuota()){
                cerr<<"pila vuota";
                return 0;
            }
            T out=top->elem;
            Node<T>* elim=top;
            top=elim->succ;
            delete elim;
            numel--;
            return out;
        }
        T PrimoElemento(){if(top) return top->elem; else return 0;}
        void stampapila(ofstream& stream){
            Node<T>* iter=top;
            while (iter){
                stream<<iter->elem<<" ";
                iter=iter->succ;
            }    
        }
        void stampapila(){
            Node<T>* iter=top;
            cout<<"{";
            while (iter){
                cout<<iter->elem<<" ";
                iter=iter->succ;
            }
            cout<<"}";    
        }

};

template<class T>
class Multistack{
    Pilanodo<T>* top;
    public:
        Multistack(){top=NULL;}
        ~Multistack(){ 
            Pilanodo<T>* iter=top;
            while(top){
                iter=top->succ;
                delete top;
                top=iter;
            }
        }
        void Rearrange(Pilanodo<T>* temp){
    	    Pilanodo<T>* x=top, *y=NULL; 
    	    if (temp) {
	    	    T valore=temp->PrimoElemento(); 
		        while ((x!=NULL) && (valore > x->PrimoElemento()))	{
		    	    y=x; 
        			x=x->getSucc(); 
    	    	}
		        if (y!=NULL) 	{
    			    temp->setsucc(x); 
	        		y->setsucc(temp); 
	    	    }
    		    else 	{
			        temp->setsucc(top); 
			        top=temp;
		        }
	        } 
        }
        T pop(){
        	if(!top)return 0;
            T out=top->pop();
            Pilanodo<T>* temp=top;
            if(top->Vuota()){
                top=top->succ;
                delete temp;
            }
            else{
                top=top->succ;
                Rearrange(temp);
            }
            return out;
        }
        void push(T x)	{
	        top->push(x);
	        Pilanodo<T>* temp=top; 
    	    top=top->succ; 
	        Rearrange(temp); 
        }
        void Newpush(T x){
            Pilanodo<T>* nuovo=new Pilanodo<T>;
            nuovo->push(x);
            if(!top){
                top=nuovo;
            }
            else Rearrange(nuovo);
        }
        void stampamulti(ofstream& stream){
            Pilanodo<T>* iter=top;
            while(iter){
                iter->stampapila(stream);
                iter=iter->succ;
            }
        }
        void stampamulti(){
            Pilanodo<T>* iter=top;
            while(iter){
                iter->stampapila();
                iter=iter->succ;
            }
        }
};

int main(){
    string tipo,oppiudato;
    unsigned numel;
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
    while(!input.eof()){
        input>>tipo>>numel;
        //cout<<" hey ciao sto funzionando"<<tipo<<numel<<endl;
        if(tipo=="int"){
            Multistack<int> mulsta;
            for(unsigned i=0;i<numel;i++){
                input>>oppiudato;
                //cout<<" è queso?";
                if(oppiudato[0]=='n'){
                    mulsta.Newpush(atoi((oppiudato.substr(2)).c_str()));
                    //cout<<oppiudato<<" opiudato newpush \n";
                }
                else if(oppiudato[0]=='p'){
                    if(oppiudato=="pop"){
                        
                        mulsta.pop();
                        //cout<<oppiudato<<" opiudato pop \n";
                    }
                    else{
                        mulsta.push(atoi((oppiudato.substr(2)).c_str()));
                        
                        //cout<<oppiudato<<" opiudato push \n";
                    }
                }
                //cout<<" sono arrivato qui";
                //mulsta.stampamulti();
                //cout<<endl;
				//cout<<" i miei dubbi";
                //cout<<endl;
            }
			mulsta.stampamulti(output);  
			output<<"\n";
        }
        else if(tipo=="double"){
            Multistack<double> mulsta;
            for(unsigned i=0;i<numel;i++){
                input>>oppiudato;
                //cout<<" e qui";
                 if(oppiudato[0]=='n'){
                    mulsta.Newpush(atof((oppiudato.substr(2)).c_str()));
                    //cout<<oppiudato<<" opiudato newpush \n";
                }
                else if(oppiudato[0]=='p'){
                    if(oppiudato=="pop"){
                        
                        mulsta.pop();
                        //cout<<oppiudato<<" opiudato pop \n";
                    }
                    else{
                        mulsta.push(atof((oppiudato.substr(2)).c_str()));
                        
                        //cout<<oppiudato<<" opiudato push \n";
                    }
                }
                //mulsta.stampamulti();
                //cout<<endl;
            }
            mulsta.stampamulti(output);  
        	output<<endl;
        }
    }
    input.close();
    output.close();
}
