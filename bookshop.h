#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include"booknode.h"
#include"dynamicqueue.h"
using namespace std;
class BookShop{
private:
		BookNode *root;
		bool CounterIsSet;	// this will keep record of call of load function
		int counter;		// for assigning id
		bool loaded;
////---------------- functions---------------------------------
	void SetCounter();				// done
	void AsignID(BookNode*);		// done
	bool IsEmpty();					// done
	void Link(BookNode* );			// done 
	bool Duplicate(BookNode* );		// done // to check book is already exist or not
	void Display(BookNode* temp);	// done
	void AskLoading();				// done // this function will ask the user to load file
/////-------------------SearchAndDisplay functions----------------
	void SearchAndDisplayById();	// done
	void SearchAndDisplayByName();	// done
	void SearchAndDisplayByType();	// done
	void SearchAndDisplayByAuthor();// done

	void Clear(BookNode *temp);										// done
	void DeleteWithNoChild( BookNode *temp );						// done
	void DeleteWithOneChild( BookNode *temp );						// done
	BookNode* SearchById(BookNode* temp,int i) const;				// done 
	BookNode* SearchByName(BookNode* temp,string el) const;			// done
	BookNode* SearchParent(BookNode *top,BookNode *temp) const ;	// done
	/* to finding a node give adrees of top/root node here */		
//------------------------------------------------------------------------
public: BookShop();							// done
		void Delete(string bn);				// done
		void PrintQueue();					// done
		void Search();						// done
		void Save();						// done
		~BookShop();						// done
		void Display();						// done
		void Load();						// done
		void Insert();						// done
		void Buy(int);						// done
		void Read();						// done
		void IncreaseCopy(int id,int cpy);	// done
		void PriceChange(int id, int np);	// done
/////-------------------------------------------------------------
	//that are not part of this program

		//void Swap(BookNode*,BookNode*); 
		//void PrintLink();
		//void DeleteByID(int i);
//-----------------------------------------------------------------
}; // eof class
BookShop::BookShop()
{ root=0;  counter=0; CounterIsSet=0; loaded=0; }

bool BookShop::IsEmpty() 
{ return root==0?1:0; }
void BookShop::AsignID(BookNode *temp)
{temp->id=++counter;}
void BookShop::Link(BookNode *temp)
{	BookNode *tt=SearchById(root,temp->id);
	if(tt!=0)
		delete temp;
	else
	{temp->left=temp->right=0;
	{if(IsEmpty())
		{root=temp;}
	else 
	{	BookNode *t=root,*pre;
		while(t!=0)
		{ pre=t;
			if(temp->bname<t->bname)
			t=t->left;
		else  if(temp->bname>t->bname)
			t=t->right;
		else if(temp->bname==t->bname)
		{ cout<<"\nBook "<<temp->bname<<" is already exist in stock ";
			break;
			}
		}// eof while
		if(temp->bname<pre->bname && pre->left==0)
			pre->left=temp;
		else if(temp->bname>pre->bname && pre->right==0)
			pre->right=temp;
		else if(temp->bname==t->bname) delete temp;  // for duplicate case	
	}
	}}
}
void BookShop::Delete(string bn) 
{ 	if(!IsEmpty())
	{ BookNode *temp=SearchByName(root,bn);
		if(temp!=0)
		{ 	if ( temp->left==0 && temp->right==0 ) 
				DeleteWithNoChild(temp);
			else if ( ( temp->left==0 && temp->right!=0 ) || ( temp->left!=0 && temp->right==0 ) ) // Eexclusive OR
				DeleteWithOneChild(temp);
			else  // make it delete with one child and then called DeleteByMerging
			{	BookNode *link=temp->left;
				while(link->right!=0)
				link=link->right;
				link->right=temp->right;
				temp->right=0;
				DeleteWithOneChild(temp);		
			}
		}
		else cout<<"\nBook not found it can not be deleted ";
	}
}
void BookShop::Display(BookNode *temp)
{ if(temp!=0)
{ Display(temp->left);
	temp->show();
Display(temp->right);
}
}
void BookShop::Display()
{ if(!IsEmpty())
{cout<<"\nID\tName\t\t\tAuthors\t\tType\t Copies\t\tPrice";
Display(root);}
else cout<<"\nBook List is empty ";
}

BookShop::~BookShop()
{   Save(); // saving all data before deleting
	Clear(root);
}

void BookShop::Load()
{ ifstream obj("shop.txt",ios::binary);
	if(obj.good()) // to check file is good for reading or not 
	{ BookNode *temp;
	//cout<<"\nLoading start "; getch(); ///-----
	temp=new BookNode;
	obj.read(reinterpret_cast<char*>(temp),sizeof(BookNode));
	while(!obj.eof())
	{ if(temp->id>counter)
		{counter=temp->id;}
		Link(temp);
	//cout<<"\nObject Added";	///-----
	//cout<<"\n"<<int(temp->left)<<"\t"<<int(temp)<<"\t"<<temp->right;	///-----
	temp=new BookNode();
	obj.read(reinterpret_cast<char*>(temp),sizeof(BookNode));
	}
	CounterIsSet=true;
	//delete temp;
					// delete the reading of last loop, because last object
					// was read twice but not link in bookshop	
					// by deleting it return memory to os
	obj.close();	
 if(root!=0)	cout<<"\nLoad Successfully\n";
 else cout<<"\n File Is Empty \n";
 loaded=1;  // this flag tells is file loaded or not 
	}
else { obj.close(); 
cout<<"\nFile can not be load please insert some data,then save and load"; }
}

void BookShop::Insert()
{	if(!CounterIsSet)
	SetCounter(); // if left file is not loaded then get highest id from 
					// file and set counter
	BookNode *temp=new BookNode();
	AsignID(temp);
	temp->get();
	Link(temp);
}
void BookShop::SetCounter()
{
ifstream obje("shop.txt",ios::binary);
		if(obje.good())
		{ BookNode *temp;
		temp=new BookNode;
		obje.read(reinterpret_cast<char*>(temp),sizeof(BookNode));
		while(!obje.eof())
		{ if(temp->id>counter)
			counter=temp->id;
		obje.read(reinterpret_cast<char*>(temp),sizeof(BookNode));}
		delete temp; }
		obje.close(); CounterIsSet=1; 
}
void BookShop::Save()
{  if(!loaded)
	{ ifstream obj("shop.txt",ios::binary);
		if(obj.good())
		{ BookNode *temp;
			temp=new BookNode;
	obj.read(reinterpret_cast<char*>(temp),sizeof(BookNode));
	while(!obj.eof())
	{ if((temp->id)>(counter))
		{counter=temp->id;}
		Link(temp);
		temp=new BookNode();
	obj.read(reinterpret_cast<char*>(temp),sizeof(BookNode));
	} CounterIsSet=true;
	delete temp; }
		obj.close(); }
	ofstream tt("shop.txt",ios::out); tt.close();
 
		 // this flag tells is file loaded or not
	// if load is not called then it will upload data and, when save, left
	/// data will not be over writing
	if(root!=0){
	ofstream abj("shop.txt",ios::binary);
	BookNode * temp1=root;
	DynamicQueue<BookNode*> p;
	p.Enqueue(temp1);
	while(!p.IsEmpty())
	{	temp1=p.Dequeue();
		if(temp1->left!=0) p.Enqueue(temp1->left);
		if(temp1->right!=0) p.Enqueue(temp1->right);
		abj.write(reinterpret_cast<char*>(temp1),sizeof(BookNode));
	}
	cout<<"\nSave Successfully\n";
	abj.close(); }
}


void BookShop::AskLoading()
{char c;
	if(!loaded)
{cout<<"\nAll books are not loaded in system if u want to \nload before this operation press y: ";
	 c=getche(); 
	if(c=='y' || c=='Y') Load(); }
}
void BookShop::Search()
{	char c;
	AskLoading();
	cout<<"\nEnter choice for method of searching or any other key to goto main menu ";
	cout<<"\n1- For search by ID ";
	cout<<"\n2- For search by Book Name ";
	cout<<"\n3- For search by Author Name ";
	cout<<"\n4- For search by Type ";
	c=getche();
	switch(c){
	case'1': { SearchAndDisplayById();
			break;}
	case'2': { SearchAndDisplayByName();
			break;}
	case'3': { SearchAndDisplayByAuthor();
			break;}
	case'4': { SearchAndDisplayByType();
			break;}
	}
}
BookNode* BookShop::SearchById(BookNode *temp,int i) const
{ BookNode *ret=0;
	if(temp!=0)
	{
		if(i==temp->id)
		ret=temp;
	  if(ret==0) ret=SearchById(temp->left,i);
	  if(ret==0) ret=SearchById(temp->right,i);
	}
	return ret;

}
void BookShop::SearchAndDisplayById()
{ int i;
	cout<<"\nEnter ID of book to search : ";
 cin>>i;
if(!IsEmpty())
{BookNode *temp=SearchById(root,i) ;
cout<<"\nID\tName\t\t\tAuthors\t\tType\t Copies\t\tPrice";
if(temp!=0) temp->show();
else cout<<"\n\t\tNo record found ";}
}
void BookShop::Buy(int idd)
{	if(root!=0){
	BookNode *temp=SearchById(root,idd);
	
	if(temp!=0 && temp->id==idd)
{
	if(temp->copy>0)
	{ int num=0;
	cout<<"\n Enter \""<<temp->bname<<"\" num of copies which you want to purchase : "; cin>>num;
		if(num>temp->copy) num=temp->copy;
		cout<<"\n "<<num<<" purchased bil is "<<((temp->price)*(num));
		temp->copy-=num;
	}
	else 
	{cin.ignore(1);  cout<<"\nBook is out of stock \nEnter name of coustomer to insert in queue : ";
	string tt; getline(cin,tt);
	cout<<"\nUser Name entered as "<<tt;
	temp->demand.Enqueue(tt);
	}
}
	else cout<<"\nBook does not exist ";}
else cout<<"\nBook Shop is empty or file is not loaded ";
}

void BookShop::PrintQueue()
{ AskLoading();
	if(IsEmpty()) cout<<"\nBookList is empty no book in data ";
	else{ //cin.ignore();
	cout<<"\nEnter name of book to print queue of coustomers : ";
	string tt;  getline(cin,tt);
	BookNode *temp=SearchByName(root,tt); 
	if(temp!=0 && temp->bname==tt )
	{ cout<<"\nQueue for book "<<temp->bname<<" is "; temp->demand.Print(); }
	else cout<<"\n Book is not found in data ";
	}
}
void BookShop::SearchAndDisplayByName()
{	cin.ignore(1);
	cout<<"\nEnter Name of book : "; 
	string st; getline(cin,st);
	if(!IsEmpty())
	{
	bool b=0;
	cout<<"\nID\tName\t\t\tAuthors\t\tType\t Copies\t\tPrice";
	DynamicQueue<BookNode*> p;
	BookNode *temp;
	temp=root;
	p.Enqueue(temp);
	while(!p.IsEmpty())
	{ temp=p.Dequeue();
		if(temp->left!=0) p.Enqueue(temp->left);
		if(temp->right!=0) p.Enqueue(temp->right);
		if(temp->bname.find(st)!=-1)
		{temp->show(); b=1;	}
	}
	if(b==0) cout<<"\n\t\tNo record found ";
	}
	else cout<<"\n\t\tBook List is empty ";
}
void BookShop::SearchAndDisplayByAuthor()
{	cin.ignore(1);
	cout<<"\nEnter Name of author : "; 
	string st; getline(cin,st);
	if(!IsEmpty())
	{
	bool b=0; int i=0;
	cout<<"\nID\tName\t\t\tAuthors\t\tType\t Copies\t\tPrice";
	DynamicQueue<BookNode*> p;
	BookNode *temp=root;
	p.Enqueue(temp);
	while(!p.IsEmpty())
	{ temp=p.Dequeue();
		if(temp->left!=0) p.Enqueue(temp->left);
		if(temp->right!=0) p.Enqueue(temp->right);
		for(i=0;i<(temp->authors);i++)
		if(temp->aname[i].find(st)!=-1)
		{temp->show(); b=1;}
	}
	if(b==0) cout<<"\n\t\tNo record found ";
	}
	else cout<<"\n\t\tBook List is empty ";
}
void BookShop::SearchAndDisplayByType()
{	cin.ignore(1);
	cout<<"\nEnter type of book : "; 
	string st; getline(cin,st);
	if(!IsEmpty())
	{
	bool b=0;
	cout<<"\nID\tName\t\t\tAuthors\t\tType\t Copies\t\tPrice";
	DynamicQueue<BookNode*> p;
	BookNode *temp=root;
	p.Enqueue(temp);
	while(!p.IsEmpty())
	{ temp=p.Dequeue();
		if(temp->left!=0) p.Enqueue(temp->left);
		if(temp->right!=0) p.Enqueue(temp->right);
		if(temp->type.find(st)!=-1)
		{temp->show(); b=1;	}
	}
	if(b==0) cout<<"\n\t\tNo record found ";
	}
	else cout<<"\n\t\tBook List is empty ";
}

void BookShop::Read()
{	SetCounter();
	cout<<"\nPress 1 to know input pattern or any key to continue ";
	char c=getche(); 
	if(c=='1')
	{ cout<<"\nInput pattern, file name should be read.txt ";
	cout<<"\nBook(1):Author1,A2,....A10,:Type:Copies:Price;";
	cout<<"\nBook(2):Author1,A2,....A10,:Type:Copies:Price;";
	cout<<"\n\t.\n\t.\n\t.\n\t.\n\t.\n\t.\n\t.\n\t.";
	cout<<"\nBook(n):Author1,A2,....A10,:Type:Copies:Price;"; }
	int b=0;
	ifstream obj("read.txt");
	if(obj.good())
	{	// cout<<"\nStart Reading data \n"; 
		char ch; BookNode* temp; int i;
		while(!obj.eof())
		{ temp=new BookNode; 		 
		ch=obj.get(); 
		while(ch!=';')
		{  while(ch!=':') // for book name
			{ (temp->bname)+=ch; ch=obj.get(); }
			temp->authors=0; 

			ch=obj.get();
			while(ch!=':') // for authors
			{ while(ch!=',')
				{ temp->aname[temp->authors]+=ch; ch=obj.get();	}
				temp->authors++; 
				ch=obj.get();	}
		
			ch=obj.get();
			while(ch!=':') // for book type
			{ (temp->type)+=ch; ch=obj.get(); }
				
			i=0; ch=obj.get();
			while(ch!=':') // for no of copies
			{ ch-=48; i=(i*10)+ch; ch=obj.get(); }
			temp->copy=i;	
			
			i=0; ch=obj.get();
			while(ch!=':') // for no of price
			{ ch-=48; i=(i*10)+ch; ch=obj.get(); }
			temp->price=i;		
			ch=obj.get(); 
		} ch=obj.get();
		if(!Duplicate(temp))  // if not duplicate then add to tree
		{AsignID(temp); Link(temp); b++;}
		else 
			{ cout<<endl<<temp->bname<<" book already exist in book shop ";
				delete temp;	}
		} // eof while(!obj.eof())
	cout<<"\nReding finish, "; 
	if(b>0){ cout<<b; if(b==1)cout<<" book"; else cout<<" books"; cout<<" add successfully ";}
	else cout<<"No book aded ";	}// eof if
	obj.close();
}
bool BookShop::Duplicate(BookNode *tt)
{	bool dp[3]; int i;
	if(root!=0){
	BookNode *temp=root; 
	DynamicQueue<BookNode*> p;
	p.Enqueue(temp);  
	while(!p.IsEmpty())
	{ temp=p.Dequeue();
		if(temp->left!=0) p.Enqueue(temp->left);
		if(temp->right!=0) p.Enqueue(temp->right);
		for(i=0;i<3;i++) dp[i]=0;
		if(tt->bname==temp->bname)
			dp[0]=1;
	 if (tt->authors==temp->authors)
		 for(i=0;i<(tt->authors);i++)
			if(tt->aname[i]==temp->aname[i])
				dp[1]=1;
			else {dp[1]=0; break;}
	if (tt->type==temp->type)
				dp[2]=1;
	if(dp[0]==1 && dp[1]==1 && dp[2]==1 ) return 1;
	} // eof while
	}
	bool dup=0;
	if (!loaded)
	{ 	ifstream object("shop.txt",ios::binary);
		if(object.good())
		{ BookNode *temp;
		temp=new BookNode;
		object.read(reinterpret_cast<char*>(temp),sizeof(BookNode));
		while(!object.eof())
		{ for(i=0;i<3;i++) dp[i]=0;
			if(tt->bname==temp->bname)
				dp[0]=1;
			if (tt->authors==temp->authors)
				for(i=0;i<tt->authors;i++)
				if(tt->aname[i]==temp->aname[i])
					dp[1]=1;
				else {dp[1]=0; break;}
			if (tt->type==temp->type)
					dp[2]=1;
			if (dp[0]==1 && dp[1]==1 && dp[2]==1 ) {dup=1; break;}
		object.read(reinterpret_cast<char*>(temp),sizeof(BookNode));
		}
		delete temp; 
		object.close(); }
	}
	return dup; 
}
void BookShop::IncreaseCopy(int id, int cpy)
{ BookNode *temp=SearchById(root,id);
		if(temp!=0 && id==temp->id) 
{temp->copy+=cpy; cout<<"\nNow total copies of book "<<temp->bname<<" are "<<temp->copy; }
	else {
		cout<<"\nBook not exist in stock ";
		if(!loaded)
			cout<<"or not loaded from file ";}
}

void BookShop::PriceChange(int id, int np)
{ cin.ignore();
	BookNode *temp=SearchById(root,id);
	if(temp!=0 && id==temp->id) 
	{ cout<<"\nCurrent price of book "<<temp->bname<<" is "<<temp->price; temp->price=np;
	cout<<"\nNew price of book "<<temp->bname<<" is "<<temp->price; }
	else {
		cout<<"\nBook not exist in stock ";
		if(!loaded)
			cout<<"or not loaded from file ";}

}
void BookShop::DeleteWithOneChild(BookNode *temp) // finshed
{if(temp!=0 && ( ( temp->left!=0 && temp->right==0 ) || ( temp->left==0 && temp->right!=0 ) ) )
{		if(temp==root)
	{ if ( root->left!=0 )
			root=root->left;
	  else if( root->right!=0 )
			root=root->right;
			delete temp;	
	}
	else
	{	BookNode *prnt=SearchParent(root,temp);
		if(prnt->left==temp && temp->left!=0)
			prnt->left=temp->left;
		else if(prnt->right==temp && temp->right!=0)
			prnt->right=temp->right;
		else if(prnt->left==temp && temp->right!=0)
			prnt->left=temp->right;
		else if(prnt->right==temp && temp->left!=0)
			prnt->right=temp->left;

			delete temp;		
	}
}
}
void BookShop::DeleteWithNoChild(BookNode *temp) // finshed
{	if(  temp->left==0 && temp->right==0 )
	{	if(temp==root)
			{delete root; root=0; }
		else
		{
			BookNode *prnt=SearchParent(root,temp);
			if(temp==prnt->left)
			prnt->left=0;
			else if(temp==prnt->right)
			prnt->right=0;
			delete temp;
		}
	}
}
BookNode* BookShop::SearchParent(BookNode *top,BookNode *temp) const // finshed
{ if(temp==root || top==0 || temp==0) return 0;
	while(temp!=top->left && temp!=top->right )
	{if(temp->bname<top->bname) top=top->left;
	else if(temp->bname>top->bname) top=top->right;}
	if(temp==top->left || temp==top->right )
	return top;
	else return 0;
}
BookNode* BookShop::SearchByName(BookNode	*temp,string el) const
{	while( temp!=0 && el!=temp->bname)
	 if(el<temp->bname) temp=temp->left;
else if(el>temp->bname) temp=temp->right;
  return temp;
}
void BookShop::Clear(BookNode *temp)
{ if(temp!=0)
	{	Clear(temp->left);
		Clear(temp->right);
		delete temp;	}
}






//---------------------extr function-----------------
/*
void BookShop::Swap(BookNode *t1,BookNode* t2)
{  // member by member changing
	int id=t1->id; t1->id=t2->id; t2->id=id;
	string an; int at=((t1->authors>=t2->authors)?t1->authors:t2->authors);
for(int i=0;i<at;i++)
{an=t1->aname[i]; t1->aname[i]=t2->aname[i]; t2->aname[i]=an; }
at=t1->authors;  t1->authors=t2->authors; t2->authors=at;
string bn=t1->bname; t1->bname=t2->bname; t2->bname=bn;
int copy=t1->copy; t1->copy=t2->copy; t2->copy=copy;
float price=t1->price; t1->price=t2->price; t2->price=price;
string type=t1->type; t1->type=t2->type; t2->type=type;
QueueOfString demand=t1->demand; t1->demand=t2->demand; t2->demand=demand;
}
void BookShop::DeleteByID(int i)
{BookNode *temp=root;
	while(temp!=0 && i!=temp->id)
		temp=temp->right;
	if(temp!=0 && i==temp->id) 
	{ cout<<"\nDo you want to delete "<<temp->bname<<", if yes press y : ";
		char ch=getche();
		if(ch=='y')
		{Delete(temp); cout<<"\nBook Deleted"; }
		else cout<<"\nBook is not deleting";
	}
	else {
		cout<<"\nBook not exist in stock ";
		if(!loaded)
			cout<<"or not loaded from file ";}

}
void BookShop::PrintLink()
		{ cout<<"\nPrint link chain ";
			BookNode *temp=root;
			while(temp!=0)
			{cout<<endl<<int(temp->left)<<"\t"<<int(temp)<<"\t"<<int(temp->right);		
			temp=temp->right;}
			if(IsEmpty()) cout<<"\n Empty";
			}
*/