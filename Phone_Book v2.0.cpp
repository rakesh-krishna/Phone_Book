#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<ctime>
#include<stdlib.h>
using namespace std;
fstream file;

class Contact
{
	long long int Phone;
	char Fname[30];
	char Sname[30];
	char Email[40];
	char DOC[50];
	Contact *next;
	public:
		Contact()
		{
			Phone=0;
			next=NULL;
		}
		void importfile(Contact arr[]);
		void exportfile(Contact x,char name[]);
		void setData();
		void setfile();
		void getfile(Contact arr[]);
		void freefile(Contact arr[]);
		int findcount(Contact x);
		void getData();
		void getData1();
		void dispData(Contact arr[]);
		void dispData1(Contact arr[]);
        void dispData2(Contact arr[]);
        void dispData3(Contact arr[],int y);
		void insert(Contact arr[],Contact x);
		void insertfull(Contact x);
		void storeData();
        friend void get_phone(long long int x,Contact z,int fl);
        friend void get_fname(string x,Contact z,int fl);
        friend void get_sname(string x,Contact z,int fl);
        friend void get_email(string x,Contact z,int fl);
        void edit();
        void loadhistory(Contact x);
        void dispHistory();
        void clearHistory();
        void deleteContact();

};

void Contact::deleteContact()
{
    fstream fd;
    fstream ft;
//fd.open("contact.dat",ios::in|ios::out|ios::binary);
    int flagd=0;
    char conf='y';
    Contact ed;
    cout<<"\t\tEnter Phone number to delete:";
    string enodel; cin>>enodel;
    fd.open("contact.dat",ios::in|ios::out|ios::binary);
    while(!fd.eof())
    {
        fd.read((char*)&ed,sizeof(class Contact));
        if(ed.Fname==enodel)
        {
            flagd=1;
    //ft.open("temp.dat",ios::app|ios::binary);
    //ft.write((char*)&ed,sizeof(class Contact));
    //ft.close();
        }
        else
        {
            ft.open("temp.dat",ios::app|ios::binary);
            ft.write((char*)&ed,sizeof(class Contact));
            ft.close();
        }
    }
    fd.close();
    if(flagd==0)
        cout<<"specified Phone number not found ";
    fd.close();
    fd.open("contact.dat",ios::out|ios::binary);
    fd.close();
//fd.open("contact.dat",ios::app|ios::binary);
    ft.open("temp.dat",ios::out|ios::in|ios::binary);
    while(ft.read((char *)&ed,sizeof(class Contact)))
    {
        fd.open("contact.dat",ios::app|ios::binary);
        fd.write((char*)&ed,sizeof(class Contact));
        fd.close();
    }
    ft.close();
//fd.close();
    cout<<"process complete";
}
void Contact::clearHistory()
{
    file.open("history.dat",ios::out|ios::binary);
    file.close();
}
void Contact::dispHistory()
{
    //Contact x;
    file.open("history.dat",ios::in|ios::binary);

    while(file.read((char *)&*this,sizeof(class Contact)))
    {
        cout<<"\n\t"<<this->Fname<<"\t\t|\t"<<this->Sname<<"\t\t|\t"<<this->Phone<<"\t\t|\t"<<this->Email<<"\t\t|\t"<<this->DOC;
    }
    file.close();
}
void Contact::loadhistory(Contact x)
{
    file.open("history.dat",ios::app|ios::binary);
    file.write((char *)&x,sizeof(class Contact));
    file.close();
}

void Contact::edit()
{
    Contact x;
    int k=0;
    long long int phone;
    string name;
    cout<<"Enter the name of contact to edit";
    cin>>name;
    file.open("contact.dat",ios::in|ios::binary);
	while(file.read((char *)&x,sizeof(class Contact)))
	{
		if(x.Fname==name||x.Sname==name)
		{
			cout<<"\n\t"<<x.Fname<<"\t\t|\t"<<x.Sname<<"\t\t|\t"<<x.Phone<<"\t\t|\t"<<x.Email<<"\t\t|\t"<<x.DOC;
			while(1)
			{
			//y.viewCandidate();
                cout<<"Enter the new phone ::";
                cin>>phone;
                fstream c;
                c.open("contact.dat",ios::out|ios::in|ios::binary);
                c.seekp(sizeof(class Contact)*k,ios::beg);
                x.Phone=phone;
                c.write((char *)&x,sizeof(class Contact));
                c.close();
                file.close();
                cout<<"Contact has been updated"<<endl;
                return;
			}
		}
		k++;
		//x.getfile(arr);
	}
}
void Contact::exportfile(Contact x,char name[])
{
	file.open(name,ios::out|ios::app);
	file<<x.Phone<<","<<x.Fname<<","<<x.Sname<<","<<x.Email<<","<<x.DOC<<"\n";
	file.close();
}

void delete_file()
{
    file.open("contact.dat",ios::out|ios::binary);
    file.close();
}
void Contact::freefile(Contact arr[])
{
    for(int i=0;i<10;i++)
    {
        arr[i].Phone=0;
        arr[i].next=NULL;
    }
}
void Contact::setfile()
{
    file.open("contact.dat",ios::app|ios::binary);
    file.write((char *)&*this,sizeof(class Contact));
    file.close();
}
void Contact::getfile(Contact arr[])
{
    //string x;
    freefile(arr);
    file.open("contact.dat",ios::in|ios::binary);
    //getline(file,x);
    //cout<<x;
    while(file.read((char *)&*this,sizeof(class Contact)))
    {
        insert(arr,*this);
    }
    file.close();
}
void Contact::importfile(Contact arr[])
{
	ifstream csv("contact.csv");
	string a,b,c,d;
	Contact x;
	while(csv.good())
	{
		getline(csv,a,',');
		getline(csv,b,',');
		getline(csv,c,',');
		getline(csv,d,'\n');
		strcpy(x.Fname,a.c_str());
		strcpy(x.Sname,b.c_str());
		strcpy(x.Email,c.c_str());
        for(int w=0;w<strlen(x.Fname);w++)
            x.Fname[w]=tolower(x.Fname[w]);
        for(int w=0;w<strlen(x.Sname);w++)
            x.Sname[w]=tolower(x.Sname[w]);
		//cout<<"\n"<<d;
        time_t t = time(0);
        strcpy(x.DOC,ctime(&t));
		x.Phone=stoll(d);
		x.setfile();
	}
	csv.close();
	this->freefile(arr);
	this->getfile(arr);
}
int Contact::findcount(Contact x)
{
	if(x.Phone==0)
        return 0;
    {
        if(x.next==NULL)
            return 1;
        else
            return 1+findcount(*x.next);
	}
}
void Contact::dispData(Contact arr[])
{
    cout<<"Index |   Count   |                                                Phone No.\n";
    cout<<"------|-----------|---------------------------------------------------------------------------------------------------------------------------------";
	for(int i=0;i<10;i++)
	{
		cout<<"\n"<<"( "<<i<<" ) | ";
		cout<<"--> ( "<<findcount(arr[i])<<" ) |";
		arr[i].getData();
	}
	cout<<endl;
}
void Contact::dispData1(Contact arr[])
{
	for(int i=0;i<10;i++)
	{
		arr[i].getData1();
	}
	cout<<endl;
}
void Contact::insert(Contact arr[],Contact x)
{
	int k;
	k=x.Phone%10;
	if(arr[k].Phone==0)
	{
		arr[k]=x;
		return;
	}
	else
	{
		arr[k].insertfull(x);
	}
}string lname[600];
void Contact::insertfull(Contact x)
{
	if(this->next==NULL)
	{
		this->next=new Contact;
		*this->next=x;
		return;
	}
	else
	{
		this->next->insertfull(x);
		return;
	}
}string fname[600];
int countDigit(long long int n)
{
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}
bool name_check(char *x)
{
    for(int w=0;x[w]!='\0';w++)
    {
        if(isdigit(x[w]) || ((x[w]>=33 && x[w]<=47)  || (x[w]>=58 && x[w]<=64) || (x[w]>=91 && x[w]<=96) || (x[w]>=123 && x[w]<=126)))
            return true;
    }
}
int countLetter(string x)
{
   // return strlen(x);
   return x.size();
}
void Contact::setData()
{
    string p;
    int a=0,b=0,c=0;
    //long long int p=0;
    time_t t = time(0);
    char f[30],s[30],e[30];
	while(a==0)
    {
        try
        {
            cout<<"\tEnter First Name ::";
            cin>>f;
            //cout<<f;
            cout<<"\tEnter Last Name ::";
            cin>>s;
            //transform(s.begin(), s.end(), s.begin(), ::tolower);
            if(name_check(s) || name_check(f))
                throw "Enter a valid Name";
            a=1;
        }
		catch(const char* msg)
        {
            cout<<"\n\t\t@@@@@"<<msg<<"@@@@@@\n";
        }
    }
    cout<<"\tEnter Email Id ::";
    cin>>e;
    while(b==0)
    {
        try
        {
            cout<<"\tEnter Phone Number :: ";
            cin>>p;
            //p=stoi(pp);
            //cout<<p.size();
            //cout<<p+1;
            if(countLetter(p)!=10)
                throw "Enter a valid Phone Number";
            b=1;
        }
        	catch(const char* msg)
            {
                cout<<"\n\t\t@@@@@"<<msg<<"@@@@@@\n";
            }
    }
    if(a==1 && b==1)
    {
        for(int w=0;w<strlen(f);w++)
            f[w]=tolower(f[w]);
        for(int w=0;w<strlen(s);w++)
            s[w]=tolower(s[w]);
        strcpy(DOC,ctime(&t));
        strcpy(this->Fname,f);
        strcpy(this->Sname,s);
        strcpy(this->Email,e);
        this->Phone=stoll(p);
    }
	return;
}long long int phone[600];
void Contact::getData()
{
	if(Phone!=0)
	{
        cout<<"-->"<<Phone;
        if(next==NULL)
            return;
        else
        {
            next->getData();
            return;
        }
        cout<<"\n"<<endl;
	}
}string email[600];
int count;
void Contact::getData1()
{
	if(Phone!=0)
	{
        cout<<"\n\t\t\tName          ::"<<Fname<<"  "<<Sname<<endl;
        cout<<"\t\t\tPhone Number  ::"<<Phone<<endl;
        cout<<"\t\t\tEmail Id      ::"<<Email<<endl;
        cout<<"\t\t\tDate          ::"<<DOC<<endl;
        if(next==NULL)
            return;
        else
        {
            next->getData1();
            return;
        }
	}
}
template <typename T>
void merge(T arr[], int l, int m, int r)
{
    int i,j,k;
    int n1=m-l+1;
    int n2= r-m;
    T L[n1],R[n2];
    for (i=0;i<n1;i++)
        L[i]=arr[l+i];
    for (j=0;j<n2;j++)
        R[j]=arr[m+1+j];
    i=0;
    j=0;
    k=l;
    while (i<n1&&j<n2)
    {
        if (L[i]<=R[j])
        {
            arr[k]=L[i];
            i++;
        }
        else
        {
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while (i<n1)
    {
        arr[k]=L[i];
        i++;
        k++;
    }
    while (j<n2)
    {
        arr[k]=R[j];
        j++;
        k++;
    }
}
template <typename T>
void mergeSort(T arr[], int l, int r)
{
    if (l<r)
    {
        int m=l+(r-l)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}
void Contact::dispData2(Contact arr[])
{
	for(int i=0;i<10;i++)
	{
		arr[i].storeData();
	}
}
void Contact::storeData()
{
	if(Phone!=0)
	{
	    phone[count]=Phone;
	    fname[count]=Fname;
	    lname[count]=Sname;
	    email[count]=Email;
	    count++;
        if(next==NULL)
            return;
        else
        {
            next->storeData();
            return;
        }
	}
}
template <typename T>
void Display(T x[])
{
    for(int i=0;i<count;i++)
        cout<<"\n\t\t\t\""<<x[i]<<"\"";
}
char name[30];
void get_phone(long long int x,Contact z,int fl)
{
    //cout<<"4";
	if(z.Phone!=0)
	{
        if(z.Phone==x)
        {
        	if(fl==1)
                z.exportfile(z,name);
            cout<<"\n\t"<<z.Fname<<"\t\t|\t"<<z.Sname<<"\t\t|\t"<<z.Phone<<"\t\t|\t"<<z.Email<<"\t\t|\t"<<z.DOC;
            if(fl==0)
            {
                z.loadhistory(z);
                cout<<"saved to history "<<endl;
            }
            return;
        }
        if(z.next==NULL)
            return;
        else
        {
            get_phone(x,*z.next,fl);
            return;
        }
	}
}
void get_fname(string x,Contact z,int fl)
{
    //cout<<"4";
	if(z.Phone!=0)
	{
        if(z.Fname==x)
        {
        	if(fl==1)
                z.exportfile(z,name);
            cout<<"\n\t"<<z.Fname<<"\t\t|\t"<<z.Sname<<"\t\t|\t"<<z.Phone<<"\t\t|\t"<<z.Email<<"\t\t|\t"<<z.DOC;
             if(fl==0)
            {
                z.loadhistory(z);
                cout<<"saved to history "<<endl;
            }
            return;
        }
        if(z.next==NULL)
            return;
        else
        {
            get_fname(x,*z.next,fl);
            return;
        }
	}
}
void get_sname(string x,Contact z,int fl)
{
    //cout<<"4";
	if(z.Phone!=0)
	{
        if(z.Sname==x)
        {
        	if(fl==1)
                z.exportfile(z,name);
            cout<<"\n\t"<<z.Fname<<"\t\t|\t"<<z.Sname<<"\t\t|\t"<<z.Phone<<"\t\t|\t"<<z.Email<<"\t\t|\t"<<z.DOC;
            if(fl==0)
            {
                z.loadhistory(z);
                cout<<"saved to history "<<endl;
            }
            return;
        }
        if(z.next==NULL)
            return;
        else
        {
            get_sname(x,*z.next,fl);
            return;
        }
	}
}
void get_email(string x,Contact z,int fl)
{
    //cout<<"4";
	if(z.Phone!=0)
	{
        if(z.Email==x)
        {
        	if(fl==1)
                z.exportfile(z,name);
            cout<<"\n\t"<<z.Fname<<"\t\t|\t"<<z.Sname<<"\t\t|\t"<<z.Phone<<"\t\t|\t"<<z.Email<<"\t\t|\t"<<z.DOC;
             if(fl==0)
            {
                z.loadhistory(z);
                cout<<"saved to history "<<endl;
            }
            return;
        }
        if(z.next==NULL)
            return;
        else
        {
            get_email(x,*z.next,fl);
            return;
        }
	}
}
void Contact::dispData3(Contact arr[],int y)
{
	string yes,temp;
	int z;
	try
	{
        cout<<"\t\t\tDo you want to Export the data after sorting ::(Y/N):";
        cin>>temp;
        if((temp=="y"||temp=="Y"||temp=="n"||temp=="N"))
                yes=temp;
        else
                throw "Enter a valid option next time";
	}
	catch(const char *msg)
	{
	    cout<<"\n\t\t\t@@@@@@@"<<msg<<"@@@@@@@\n";
	}
	if(yes=="y"|yes=="Y")
	{
	 z=1;
	 cout<<"\t\t\tEnter the file name with extension(.csv)::";
	 cin>>name;
	}
	else if(yes=="n"|yes=="N")
        z=0;
   // else
     //   cout<<"\t\tEnter a valid option next Time\n";

    cout<<"\n\tFirst-Name\t|\tLast-Name\t|\tPhone No.\t\t|\tEmail-Id\t\t\t|\tDOC"<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    for(int j=0;j<count;j++)
    {
        if(y==1)
        {

            for(int i=0;i<10;i++)
            {
                get_phone(phone[j],arr[i],z);
            }
        }
        if(y==2)
        {
            for(int i=0;i<10;i++)
            {
                get_fname(fname[j],arr[i],z);
            }
        }
        if(y==3)
        {
            for(int i=0;i<10;i++)
            {
               get_sname(lname[j],arr[i],z);
            }
        }
        if(y==4)
        {
            for(int i=0;i<10;i++)
            {
                get_email(email[j],arr[i],z);
            }
        }
    }
}

int count_char(char *x)
{
    int c=0;
    for(int w=0;x[w]!='\0';w++)
        c++;
    cout<<"###############"<<c;
}
int main()
{
	Contact arr[11];
	Contact x;
	Contact y;
	string op,op1,op2,op3;
	x.getfile(arr);
	//delete_file();
	while(1)
	{
        cout<<endl;
        cout<<"|________________________________________________+++++++++++++++++++++OPTIONS++++++++++++++++++++++++__________________________________________________________________|\n";
 		cout<<"|                                                [    1.Add new Contact                             ]                                                                  |\n";
		cout<<"|                                                [    2.View Caller Details                         ]                                                                  |\n";
		cout<<"|                                                [    3.Display Sorted Details                      ]                                                                  |\n";
		cout<<"|                                                [    4.Edit Contact                                ]                                                                  |\n";
		cout<<"|                                                [    5.Search Contact                              ]                                                                  |\n";
		cout<<"|                                                [    6.Display Search History                      ]                                                                  |\n";
		cout<<"|                                                [    7.Clear Search History                        ]                                                                  |\n";
		cout<<"|                                                [    8.Delete Contact                              ]                                                                  |\n";
		cout<<"|                                                [    9.Exit                                        ]                                                                  |\n";
		cout<<"|                                                ++++++++++++++++++++++++++++++++++++++++++++++++++++                                                                  |\n";
        cout<<"|______________________________________________________________________________________________________________________________________________________________________|\n";
		//cout<<"|                                                                                                                                                       |\n";
		cout<<"|    \tEnter your Option  : ";
        cin>>op;
        cout<<"|_______________________________________________________________________________________________________________________________________________________|\n\n\n\n";
		//count_char(op);
		//switch()
		//{
            if(op=="1")
            {
                x.setData();
                x.setfile();
                x.getfile(arr);
                //break;
            }
            else if(op=="10")
            {
                x.importfile(arr);
                cout<<"\t\t\t\t\t\t\t\tImported Successfully\n";
            }
            else if(op=="2")
            {
                cout<<"|________________________________________________+++++++++++++++++++++OPTIONS++++++++++++++++++++++++__________________________________________________________________|\n";
                cout<<"|                                                [    1.Display Hashing Table                       ]                                                                  |\n";
                cout<<"|                                                [    2.Display All Caller Details                  ]                                                                  |\n";
                cout<<"|                                                ++++++++++++++++++++++++++++++++++++++++++++++++++++                                                                  |\n";
                cout<<"|______________________________________________________________________________________________________________________________________________________________________|\n";
                //cout<<"|                                                                                                                                                       |\n";
                cout<<"|    \tEnter your Option  : ";
                cin>>op2;
                cout<<"|_______________________________________________________________________________________________________________________________________________________|\n\n\n\n";
		//count_char(op);                cin>>op2;
                //switch(op2)
                //{
                if(op2=="1")
                    y.dispData(arr);
                    //break;
                else if(op2=="2")
                    y.dispData1(arr);
                    //break;
                else
                    cout<<"\n\t\t\t\t\t\t\t$$$$$$$  Enter A Valid Option  $$$$$$$$$\n";
                //}
                //break;
            }
            else if(op=="3")
            {
                count=0;
                cout<<"|________________________________________________+++++++++++++++++++++OPTIONS++++++++++++++++++++++++__________________________________________________________________|\n";
                cout<<"|                                                [    1.Sort By Phone No.                           ]                                                                  |\n";
                cout<<"|                                                [    2.Sort By First Name                          ]                                                                  |\n";
                cout<<"|                                                [    3.Sort By Last Name                           ]                                                                  |\n";
                cout<<"|                                                [    4.Sort By Email ID                            ]                                                                  |\n";
                cout<<"|                                                ++++++++++++++++++++++++++++++++++++++++++++++++++++                                                                  |\n";
                cout<<"|______________________________________________________________________________________________________________________________________________________________________|\n";
                //cout<<"|                                                                                                                                                       |\n";
                cout<<"|    \tEnter your Option  : ";
                cin>>op1;
                cout<<"|_______________________________________________________________________________________________________________________________________________________|\n\n\n\n";
		//count_char(op);                cin>>op2;                cin>>op1;
                //switch(op1)
                //{
                    if(op1=="1")
                    {
                        y.dispData2(arr);
                        mergeSort(phone,0,count-1);
                        y.dispData3(arr,1);
                        //break;
                    }
                    else if(op1=="2")
                    {
                        y.dispData2(arr);
                        mergeSort(fname,0,count-1);
                        y.dispData3(arr,2);
                        //break;
                    }
                    else if(op1=="3")
                    {
                        y.dispData2(arr);
                        mergeSort(lname,0,count-1);
                        y.dispData3(arr,3);
                    }
                    else if(op1=="4")
                    {
                        y.dispData2(arr);
                        mergeSort(email,0,count-1);
                        y.dispData3(arr,4);
                        //break;
                    }
                    else
                        cout<<"\n\t\t\t\t\t\t\t$$$$$$$  Enter A Valid Option  $$$$$$$$$\n";

                //}
                //break;
            }
            else if(op=="9")
            {
                cout<<"\n#\t#\t#\t#\t#\t#\t#\t#\t#\t#  THANK YOU  #\t#\t#\t#\t#\t#\t#\t#\t#\t#\n\n";
                exit(1);
            }
            else if(op=="4")
            {
                y.edit();
                y.getfile(arr);
            }
            else if(op=="5")
            {
                cout<<"|________________________________________________+++++++++++++++++++++OPTIONS++++++++++++++++++++++++__________________________________________________________________|\n";
                cout<<"|                                                [    1.Search By Phone No.                         ]                                                                  |\n";
                cout<<"|                                                [    2.Search By First Name                        ]                                                                  |\n";
                cout<<"|                                                [    3.Search By Last Name                         ]                                                                  |\n";
                cout<<"|                                                [    4.Search By Email ID                          ]                                                                  |\n";
                cout<<"|                                                ++++++++++++++++++++++++++++++++++++++++++++++++++++                                                                  |\n";
                cout<<"|______________________________________________________________________________________________________________________________________________________________________|\n";
                //cout<<"|                                                                                                                                                       |\n";
                cout<<"|    \tEnter your Option  : ";
                cin>>op3;
                cout<<"|_______________________________________________________________________________________________________________________________________________________|\n\n\n\n";
                if(op3=="1")
                {
                    long long int p_n;
                    cout<<"\tEnter Phone number:";
                    cin>>p_n;
                    for(int i=0;i<10;i++)
                    {
                        get_phone(p_n,arr[i],0);
                    }
                }
                else if(op3=="2")
                {
                    string f_name;
                    cout<<"\tEnter the First Name:";
                    cin>>f_name;
                    for(int i=0;i<10;i++)
                    {
                        get_fname(f_name,arr[i],0);
                    }
                }
                else if(op3=="3")
                {
                    string l_name;
                    cout<<"\tEnter Last Name:";
                    cin>>l_name;
                    for(int i=0;i<10;i++)
                    {
                        get_sname(l_name,arr[i],0);
                    }
                }
                else if(op3=="4")
                {
                    string e_mail;
                    cout<<"\tEnter Email:";
                    cin>>e_mail;
                    for(int i=0;i<10;i++)
                    {
                        get_email(e_mail,arr[i],0);
                    }
                }
            }
            else if(op=="6")
            {
                y.dispHistory();
            }
            else if(op=="7")
            {
                y.clearHistory();
            }
            else if(op=="8")
            {
                y.deleteContact();
                y.getfile(arr);
            }
            else
                        cout<<"\n\t\t\t\t\t\t\t$$$$$$$  Enter A Valid Option  $$$$$$$$$\n";
		}
	return 0;
}

