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
        Node(T el,Node<T>* p=NULL){
            succ=p;
            elem=el;
        }
        void setsucc(Node<T>* p){succ=p;}
};

template<class T>
class Stack{
	protected:
		Node<T>* top;
	public:
		Stack():top(0){}
		~Stack(){
			Node<T> iter=top;
			while (iter){
				iter=top;
				top=top->succ;
				delete iter;
			}
		}
		bool Vuota()const{return !top;}
		Node<T>* getop()const{return top;}
		T Primoelem()const{if(top)return top->elem;else return 0;}
		virtual Stack<T>* push(T el){
			if(!top){
				top=new Node<T>(el);
				return this;
			}
			Node<T>* nuovo=new Node<T>(el,top);
			top=nuovo;
			return this;
		}
		virtual T pop(){
			if(!top){
				return 0;
			}
			T out=top->elem;
			Node<T>* elim=top;
			top=top->succ;
			delete elim;
			return out;	
		}
		bool operator<=(const Stack<T>& dx){
			return(Primoelem()<dx.Primoelem());
		}
		bool operator>(const Stack<T>& dx){
			return dx<=*this;
		}
		friend ofstream& operator <<(ofstream& str,const Stack<T>& dx ){
			Node<T>* iter=dx.getop();
			while(iter){
				str<<iter->elem<<" ";
				iter=iter->succ;
			}
			return str;
		}
};

template<class T>
class ordStack:public Stack<T>{
	public:
		Stack<T>* push(T el)override{
			if(!this->top){
				this->top=new Node<T>(el);
				return this;
			}
			if(el<=this->top->elem){
				Node<T>* nuovo=new Node<T>(el,this->top);
				this->top=nuovo;
				return this;
			}
			Node<T>* iter=this->top,*prec=NULL;
			while(iter && el>iter->elem){
				prec=iter;
				iter=iter->succ;
			}
			Node<T>* nuovo=new Node<T>(el,prec->succ);
			prec->succ=nuovo;
			return this;
		}
		void rearrange(){
			T rea=this->pop();
			this->push(rea);
		}
		/*void rearrange(Node<T>* el){
			Node<T>* iter=this->top,*prec=NULL;
			if(el){
				T valore=el->Primoelem();
				while(iter && valore>iter->elem){
					prec=iter;
					iter=iter->succ;
				}
				if(!prec){
					el->setsucc(top);
					this->top=el;
				}
				else{
					el->setsucc(prec->succ);
					prec->succ=el;
				}
			}
			
		}*/
};

template<class T>
class MultiStack: public ordStack<Stack<T> >{
	public:
	ordStack<Stack<T> >* push(T el)override{
			if(this->top){
				this->top->push(el);
	        	rearrange() ;
	        	return this;
			}
			else{
				Stack<T> nuo;
				nuo.push(el);
				this->
			}
		}	
	T pop()override{
		T out=this->top->elem.pop();
		if(this->top->elem.Vuota()){
			Node<Stack<T> >* elim=this->top;
			this->top=this->top->succ;
			delete elim;
			return out;
		}
		Node<Stack<T> >* riarrangia=this->top;
		this->top=this->top->succ;
		rearrange(riarrangia);
		return out;
		
	}
};



int main( ){
	return 0;
}

