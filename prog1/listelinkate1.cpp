#include<iostream>

using namespace std;

template<typename T>
struct Node
  {
    T data;
    Node *next;
  };	
  
template<typename T>  
class LList{
	public:
		LList ():head(NULL),tail(NULL){}
		~LList();
		void create();
		void display();
		Node<T>* getNode();
		void append(Node<T>* );
		void insert(Node<T>* pos, T pos);
		void rtraverse();
		void deleteNode(T deletePos);
	private:
		Node<T> *head, *tail;
};

template<typename T> 
LList :: ~LList ()
{
	Node<T> *current,*temp;
	current = head;
	temp = head;
	while(current != NULL) {
		current = current->next;
		delete temp;
		temp = current;
	}
}
