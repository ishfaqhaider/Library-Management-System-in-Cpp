// DSA Book Shop In BST Project 

// Submited to: Sir Usman

// ---------IIUI---------

// 1418-BSSE/F11-A Ishfaq Haider

// 1414-BSSE/F11-A Abdul Aziz

// 11-12-2012
#include<iostream>
#include<conio.h>
#include"bookshop.h"
using namespace std;
void main()
{ BookShop bs;
char c; int i,cp; string dl;
do{	i=cp=0;  // two variables for pasing argument in some function
	cout<<"\n\nI- for Inserting new book in the system"		// working
		<<"\nS- for Searching a book"	// working
		<<"\nD- for Displaying all books"	// working
		<<"\nF- for Saving all data in a file"	// working
		<<"\nL- for Loading data from a file"	// working
		<<"\nB- for Buy a book "	// working
		<<"\nQ- for Displaying Queue for a book. "	// working
		<<"\nR- for READING a batch of books from a file"	// working
		<<"\nE- for -----Exit----- "
		<<"\n1- for Increasing Copies of Book in stock"
		<<"\n2- for Deleting a book "
		<<"\n3- for changing price of a book  ";

	c=getche(); //cin.ignore(1);
	if(c=='i' || c=='I' )	
	{bs.Insert();}
	else if(c=='S' || c=='s' )	
	{ bs.Search();	}
	else if(c=='D' || c=='d' )	
	{bs.Display();}
	else if(c=='F' || c=='f' )	
	{ bs.Save(); }
	else if(c=='L' || c=='l' )	
	{bs.Load();}
	else if(c=='B' || c=='b' )	
	{ cout<<"\nEnter id of book to purchase ";
	cin>>i; //cin.ignore(1);
	bs.Buy(i);
	}
	else if(c=='Q' || c=='q' )	
	{ bs.PrintQueue();}
	else if(c=='R' || c=='r' )
	{bs.Read();}
else if(c=='1')
	{ cout<<"\nEnter ID of book to increase copies ";  cin>>i;
		cout<<"\nEnter no of copies to add this book ";  cin>>cp;
		bs.IncreaseCopy(i,cp);	}
else if(c=='2' )
	{ cout<<"\nEnter complete name of book to delete ";
		getline(cin,dl);
bs.Delete(dl);	}
else if(c=='3')
{ cout<<"\nEnter ID of book to change price : "; cin>>i;
cout<<"\nEnter new price for this book : "; cin>>cp;
	bs.PriceChange(i,cp); }
/*else if(c=='')
	{}*/
}while ( c!='e' && c!='E' );
}
