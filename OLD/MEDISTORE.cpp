#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <fstream.h>
#include <process.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <iomanip.h>
class store                 //class for MediStore
{
	int ino;
	char iname[20];
	float price;
	int stock;
	int qty;
public:
	int retino();
	void input();
	void output();
	void addstock();
	void sale(int k);
	void purchase();
	void bill(int n);
	void moditem();void delitem();
	void dispstock();
	void dispdetails();
	store()
	{
		stock=0;
	}
}p;

class staff                  //class for staff
{
	char sname[20];
	char pw[10];
	char admn[20];
	char admnpw[20];
public:
	void in();
	void compare();
}a;

int store::retino()          //function for returning item no.
{
	return ino;
}
void store::input()          //function to input item details
{
	cout<<"Enter item no.: ";
	cin>>ino;
	cout<<"Enter item name: ";
	gets(iname);
	cout<<"Enter item price: ";
	cin>>price;
	cout<<"Enter stock: ";
	cin>>stock;
}
void store::output()         //function to display item details
{
	cout<<ino<<setw(20)<<iname<<setw(15)<<price<<endl;
}
void store::addstock()       //function to increment stock value
{
	int no,n,z=0;
	cout<<"Enter item no. in which stock has to be added: ";
	cin>>no;
	cout<<"Enter quantity to be added: ";
	cin>>n;
	fstream g("store.txt",ios::binary|ios::in|ios::out);
	g.read((char*)&p,sizeof(p));
	while(!g.eof())
	{
		if(no==retino())
		{
			z=1;
			break;
		}
		else
			z=0;
		g.read((char*)&p,sizeof(p));
	}
	if(z==1)
	{
		stock=stock+n;
		int pos=-1*sizeof(p);
		g.seekp(pos,ios::cur);
		g.write((char*)&p,sizeof(p));
		cout<<"Stock added\n";
		dispstock();
	}
	else
		cout<<"Item doesn't exist\n";
}
void store::sale(int k)                //function to decrement stock value
{
	int n,z=0;
	cout<<"Enter quantity: ";
	cin>>n;
	fstream g("store.txt",ios::binary|ios::in|ios::out);
	g.read((char*)&p,sizeof(p));
	while(!g.eof())
	{
		if(k==retino())
		{
			z=1;
			break;
		}
		else
			z=0;
		g.read((char*)&p,sizeof(p));
	}
	if(z==1)
	{
		stock=stock-n;
		int pos=-1*sizeof(p);
		g.seekp(pos,ios::cur);
		g.write((char*)&p,sizeof(p));
		cout<<"\nItem(s) added to list\n";
		price=n*price;
		qty=n;
	}
	else
		cout<<"Item doesn't exist\n";
}

void store::dispstock()               //function to display stock of item
{
	cout<<"\n\tItem no.: "<<ino<<endl;
	cout<<"\tItem name: ";
	puts(iname);
	cout<<"\tNew stock: "<<stock<<endl;
}

void store::moditem()                 //function to modify item details
{
	clrscr();
	int no,z=0;
	cout<<"Enter item no. to be modified: ";
	cin>>no;
	fstream o("store.txt",ios::binary|ios::in|ios::out);
	o.read((char*)&p,sizeof(p));
	while(!o.eof())
	{
		if(no==retino())
		{
			z=1;
			break;
		}
		else
			z=0;
		o.read((char*)&p,sizeof(p));
	}
	if(z==1)
	{
		int bn,st,pos;
		char in[20];
		float ct;
		cout<<"Found\n";
		pos=o.tellg();
		o.seekg(pos-sizeof(p));
		cout<<"Enter new data\n";
		cout<<"Enter new item no.: ";
		cin>>bn;
		ino=bn;
		cout<<"Enter new item name: ";
		gets(in);
		strcpy(iname,in);
		cout<<"Enter new price: ";
		cin>>ct;
		price=ct;
		cout<<"Enter new stock: ";
		cin>>st;
		stock=st;
		o.write((char*)&p,sizeof(p));
		o.close();
		cout<<"Data modified\n";
	}
	else
		cout<<"Not found\n";
}



void store::purchase()            //function to purchase and invoke sale()
{
	clrscr();
	cout<<"Itemno."<<setw(15)<<"Item name"<<setw(15)<<"Price\n";
	ifstream k("store.txt",ios::binary);
	k.read((char*)&p,sizeof(p));
	while(!k.eof())
	{
		p.output();
		k.read((char*)&p,sizeof(p));
	}
	char s='y';
	int total=0;
	while(s=='y')
	{
	cout<<"Enter the item no. you would like to purchase: ";
	int no,z=0;
	cin>>no;
	ifstream l("store.txt",ios::binary);
	l.read((char*)&p,sizeof(p));
	while(!l.eof())
	{
		if((no==retino())&&(stock>0))
		{
			z=1;
			break;
		}
		else
			z=0;
		l.read((char*)&p,sizeof(p));
	}
	if(z==1)
	{
		ofstream o("bill.txt",ios::binary|ios::app);
		cout<<"found\n";
		p.output();
		sale(no);
		total=total+price;
		o.write((char*)&p,sizeof(p));
		o.close();
	}
	else
	{
		cout<<"Not found\n";
		exit(0);
	}
	cout<<"Do you want to purchase anything else: ";
	cin>>s;
	}
	bill(total);
	getch();
}

void store::bill(int n)            //function to display the cash memo
{
	clrscr();
	cout<<"\t\t\t\tCASH MEMO\n\t\t";
	cout<<"Itemno."<<setw(15)<<"Item name"<<setw(10)<<"Qty"<<setw(10)<<"Price\n\t\t";
	ifstream y("bill.txt",ios::binary);
	y.read((char*)&p,sizeof(p));
	while(!y.eof())
	{
		cout<<ino<<setw(20)<<iname<<setw(10)<<qty<<setw(7)<<price<<endl;
		cout<<"\t\t";
		y.read((char*)&p,sizeof(p));
	}
	cout<<"\n\n\t\tTotal=  "<<n;
	cout<<"\n\n\t\t\t\tThanks for visit\n\t\t\t\t  Visit Again";
	remove("bill.txt");
	getch();
}

void staff::in()
{
	char aname[20],apw[20];
	strcpy(admn,"Kiner Shah");
	strcpy(admnpw,"mediismine");
	ofstream j("staff.txt",ios::binary|ios::app);
	cout<<"Who are you? Enter your name: ";
	gets(aname);
	cout<<"Enter your password: ";
	gets(apw);
	if((strcmp(aname,admn)==0)&&(strcmp(apw,admnpw)==0))
	{
		cout<<"Enter name of staff to be added: ";
		gets(sname);
		cout<<"Assign the entered staff a password: ";
		gets(pw);
		cout<<"Staff member Added";
		j.write((char*)&a,sizeof(a));
	}
	else
		cout<<"You are not allowed to add staff members!";
}
void staff::compare()
{
	char b[20],c[10];
	cout<<"Enter your name: ";
	gets(b);
	cout<<"Enter your password: ";
	gets(c);
	int z=0;
	ifstream k("staff.txt",ios::binary);
	k.read((char*)&a,sizeof(a));
	while(!k.eof())
	{
		if((strcmp(b,sname)==0)&&(strcmp(c,pw)==0))
		{
			z=1;
			break;
		}
		else
			z=0;
		k.read((char*)&a,sizeof(a));
	}
	if(z==1)
		cout<<"Found\n";
	else
		exit(0);
}

void store::dispdetails()
{
	clrscr();
	ifstream l("store.txt",ios::binary);
	cout<<"Item no."<<setw(15)<<"Item name"<<setw(10)<<"Price"<<setw(10)<<"Stock"<<endl;
	l.read((char*)&p,sizeof(p));
	while(!l.eof())
	{
		cout<<ino<<setw(20)<<iname<<setw(10)<<price<<setw(10)<<stock<<endl;
		l.read((char*)&p,sizeof(p));
	}
	getch();
}

void main()                                 //main function
{
	clrscr();
	int no;
	char un[20],t='y';
	cout<<"\n\n\n\n\n\n\n\n\t\t\tWelcome to MediStore....24 hrs service\n";
	cout<<"\t\t\t\t(press Any key)\n";
	getch();
	while(t=='y')
	{
		clrscr();
		int n,m;
		cout<<"\n1.Customer\n2.Staff member\n3.Exit\n";
		cin>>m;
		switch(m)
		{
		case 1:
			clrscr();
			char c='y';
			while(c=='y')
			{
				cout<<"\n1.Purchase\n2.Return to main menu\n3.Exit\n";
				cout<<"\nEnter your choice: ";
				cin>>n;
				switch(n)
				{
				case 1:p.purchase();
				break;
				case 2: break;
				case 3: exit(0);
				break;
				default: cout<<"Wrong Input";
				break;
				}
				cout<<"\nDo you want to continue: ";
				cin>>c;
			}
			getch();
		break;
		case 2:
			clrscr();
			char x='y';
			int z;
			while(x=='y')
			{
			cout<<"\n1.Sign in\n2.Add staff members\n3.Exit\n";
			cout<<"\nEnter your choice: ";
			cin>>z;
			switch(z)
			{
			case 1: a.compare();
				clrscr();
				char d;
				while(1)
				{
				cout<<"\n1.Add item\n2.Add stock\n3.Modify item\n4.Display item\n5.Delete item\n6.Exit\n";
				cout<<"\nEnter your choice: ";
				cin>>n;
				switch(n)
				{
				case 1:
					ofstream h("store.txt",ios::binary|ios::app);
					p.input();
					h.write((char*)&p,sizeof(p));
					h.close();
				break;
				case 2: p.addstock();
				break;
				case 3: p.moditem();
				break;
				case 4: p.dispdetails();
				break;
				case 5: p.delitem();
				break;
				case 6: exit(0);
				break;
				default: cout<<"Wrong Input";
				break;
				}
				cout<<"Do you want to continue: ";
				cin>>d;
				if(d=='y')
					continue;
				else
					break;
				}
				getch();
			break;
			case 2: a.in();
			break;
			case 3: exit(0);
			break;
			default: cout<<"Wrong input";
			break;
			}
			clrscr();
			cout<<"Do you want to continue: ";
			cin>>x;
			getch();
			}
			getch();
		break;
		case 3: exit(0);
		break;
		default: cout<<"wrong input";
		break;
		}
		getch();
		clrscr();
		cout<<"Do you want to continue: ";
		cin>>t;
		getch();
	}
	getch();
}
void store::delitem()
{
	clrscr();
	int no;
	cout<<"Enter item no. to be deleted: ";
	cin>>no;
	ofstream l("delitem.txt",ios::binary);
	ifstream k("store.txt",ios::binary);
	k.read((char*)&p,sizeof(p));
	while(!k.eof())
	{
		if(no==retino())
			cout<<"found\n";
		else
			l.write((char*)&p,sizeof(p));
		k.read((char*)&p,sizeof(p));
	}
	k.close();
	l.close();
	remove("store.txt");
	rename("delitem.txt","store.txt");
	getch();
}
