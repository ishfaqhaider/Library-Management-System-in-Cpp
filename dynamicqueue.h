#include<iostream>
using namespace std;
template<class t> class Node{
public:
	t info;
	Node<t> *next;
	Node()	{next=0;}
	Node(t el, Node *point=0)
	{	info=el; next=point;	}
};
template <class t>
class DynamicQueue{
	Node<t> *rear;	// tail
	Node<t> *front;		// head
public:
	DynamicQueue(): rear(0),front(0){}
	~DynamicQueue() // destructor wil be called auto at the end of program
	{ Node<t> *temp=front;
		while(front!=0)
		{ temp=front;  front=front->next; delete temp; }
	}
	void Clear();
	void Enqueue(t el);
	t Dequeue();	
	bool IsEmpty();
};
template <class t>
void DynamicQueue<t>::Clear()
{Node<t> *temp=front;
		while(front!=0)
		{temp=front; 
		front=front->next; 
		delete temp; }	
		front=temp=0;
}
template <class t>
bool DynamicQueue<t>::IsEmpty()
{ if(front==0) return 1;
		else return 0; 
}

template <class t>
void DynamicQueue<t>::Enqueue(t el)
{ Node<t> *temp=new Node<t>(el,0);
	if(IsEmpty())
	front=rear=temp;
	else 
	{rear->next=temp;
	rear=temp;}
}

template<class t>
t DynamicQueue<t>::Dequeue()
{ Node<t> *temp;
  t ret;
	if(!IsEmpty())
	{ ret=front->info;
		temp=front;
		front=front->next;
		delete temp;
		return ret;
	}
	else
		cout<<"\nDynamic Queue is empty returning zero ";
		ret=0; return ret;
}
