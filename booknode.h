#include<iostream>
#include<string>
using namespace std;
#define size 10
class QueueOfString
{public:
	int in,out; // input from in, and output from out
	string arr[size];

	QueueOfString () { in=-1; out=-1;
	for(int i=0;i<size;i++)
		arr[i]="";
	}
	void Print()
	{ if(!IsEmpty())
	{int temp=out;
		while(temp!=in)
		{ if(temp==size-1  )
			{cout<<endl<<arr[temp]; temp=0; }
		else	cout<<endl<<arr[temp++];
		}
		cout<<endl<<arr[temp++];}
		else cout<<" empty";	
	}
	bool IsEmpty ()
	{ return out==-1?1:0; }
	
	bool Full()
	{  return ((in+1)%size==out)?1:0; }

	void Clear()
	{ in=out=-1; }

	void Enqueue (string temp)
	{ if(!Full())
	{ if(in==-1 || in==size-1)
		{arr[0]=temp; in=0;
		if(out==-1)
			out=0;}
	else { in=(in+1);  arr[in]=temp; } 
	}
	else 
		cout<<" Queue is Full";
	}

	string Dequeue ()
	{	if(!IsEmpty())
		{ string temp=arr[out];
			if(in==out)
			{in=-1; out=-1;}
		else if(out==size-1  )
				out=0;
		else	out=out++;
			return temp;
		}
	else return ""; }
};


class Book{
public:	int id,copy;
		float price;
		string bname , type;
		QueueOfString demand;
		string aname[10];
		unsigned int authors;
		Book()
{ authors=10;
	id=0;
	bname="";
	for(int i=0;i<authors;i++)
		{aname[i]="";}
	type="";
	copy=0;
	price=0;
}
	void get()
	{	cin.ignore(1);
		cout<<"\nEnter Book Name : "; 
		getline(cin,bname); cout<<endl;
abc:	cout<<"Enter total number of authors : ";
		cin>>authors; 
		if(authors>10) 
		{ cout<<"\nAuthors can not be more than 10\nRe "; goto abc; }
		cin.ignore(1);
		for(int i=0;i<authors;i++)
		{cout<<"\nEnter Author "<<i+1<<" Name : ";
		getline(cin,aname[i]);}
		cout<<"\nEnter Book Type : ";
		getline(cin,type);
		cout<<"\nEnter Number of copies : ";
		cin>>copy;
		cout<<"\nEnter Price : ";
		cin>>price;
	}
void show()
{
int idd=8; if(id<10) idd-=1; else if(id<100) idd-=2; else if(id<1000) idd-=3; else idd=5;
int bb=bname.length(); bb=24-bb; int aa=aname[0].length(); aa=16-aa;
int tt=type.length(); tt=11-tt; 
int cc=14; if(copy<10) cc-=1; else if(copy<100) cc-=2; else if(copy<1000) cc-=3; else cc-=4;
cout<<"\n-----------------------------------------------------------------------------";
cout<<"\n"<<id; Space(idd);  cout<<bname;
	Space(bb); cout<<aname[0];  Space(aa);
cout<<type; Space(tt);  cout<<copy;
 Space(cc); cout<<price; 
for(int i=1;i<authors;i++)
{ cout<<endl; Space(32); cout<<aname[i]; }

} 
private: void Space(int n)
{ for(int i=0;i<n;i++)
	cout<<" ";}
};

class BookNode : public Book
{public: 	BookNode *left, *right;
BookNode()
{	id=0;
	authors=10;
	bname="";
	for(int i=0;i<authors;i++)
	aname[i]="";
	type="";
	copy=0;
	price=0;
	right=0; left=0;
}
};
