
#define _CRT_SECURE_NO_WARNINGS

#include<iostream> 
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<string.h>

using namespace std;

void write_book();
void write_student();
void display_spb(char []);
void display_sps(char []);
void modify_book();
void modify_student();
void delete_student();
void delete_book();
void display_alls();
void display_allb();
void book_issue();
void book_deposit();
void intro();
void admin_menu();

fstream fp,fp1;
char character[1];

class book
{
    char bno[6];
    char bname[30];
    char aname[30];

    public:
        void create_book()
        {
            cout<<"\nNEW BOOK ENTRY...\n";
            cout<<"\nEnter the book number.\n";
            cin>>bno;
            cout<<"\nEnter the name of the book..\n";
            cin.getline(character,1);
            cin.getline(bname,30);
            cout<<"\nEnter the Author's name.\n";
            cin.getline(aname,30);

            cout<<"\nBOOK CREATED...\n";
        }

        void show_book()
        {
            cout<<"\nBook number. : "<<bno;
            cout<<"\nBook Name. :";
            puts(bname);
            cout<<"\nAuthor Name. :";
            puts(aname);
        }

        void modify_book()
        {
            cout<<"\nBook number.  ;"<<bno;
            cout<<"\nEnter Modified Book Name. : ";
            cin.getline(character,1);
            cin.getline(bname,30);
            cout<<"\nEnter Modified Author Name. :";
            cin.getline(aname,30);
        }

        char* retbno()
        {
            return bno;
        }

        void report()
        {
            cout<<bno<<setw(25)<<bname<<setw(25)<<aname<<endl;
        }
};

class student
{
    char admno[6];
    char name[30];
    char stbno[6];
    int token;

public:
    void create_student()
    {
        cout << "\033[2J\033[1;1H";
        cout<<"\nNEW STUDENT ENTRY...\n";
        cout<<"\nEnter the admission number. :";
        cin>>admno;
        cout<<"\nEnter the name of the student. :";
        cin.getline(character,1);
        cin.getline(name,30);
        token=0;
        cout<<"\nSTUDNT RECORD CREATED...";
    } 
    void show_student()
    {
        cout<<"\nAdmission number. :"<<admno;
        cout<<"\nStudent name. :";
        puts(name);
        cout<<"\nNumber of books issued. :"<<token;
        if(token==1)
            cout<<"\nBook number. :"<<stbno;
    }   

    void modify_student()
    {
        cout<<"\nAdmission number. :"<<admno;
        cout<<"Enter Modified student name. :";
        cin.getline(character,1);
        cin.getline(name,30);
    }

    char* retadmno()
    {
        return admno;
    }

    char* retstbno()
    {
        return admno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token=1;
    }

    void resettoken()
    {
        token=0;
    }

    void getstbno(char t[])
    {
        strcpy(stbno,t);
    }

    void report()
    {
        cout<<"\n"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;
    }
};

book bk;
student st;


void write_book()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
        cout << "\033[2J\033[1;1H";
        bk.create_book();
        fp.write((char*)&bk,sizeof(book));
        cout<<"\nDo you want to add more record..(y/n)?";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st,sizeof(student));
        cout<<"\nDo you want to add more record..(y/n)?";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void display_spb(char n[])
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmp(bk.retbno(),n)==0)
        {
            bk.show_book();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<"\nBook does not exist";

    printf("\nEnter any character to exit followed by enter.");        
    cin>>character;
}

void display_sps(char n[])
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmp(st.retadmno(),n)==0)
        {
            st.show_student();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
        cout<<"\nStudent does not exist.";
  
    printf("\nEnter any character to exit followed by enter.");
    cin>>character;
}

void modify_book()
{
    char n[6];
    int found=0;
    cout << "\033[2J\033[1;1H";
    cout<<"\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\tEnter The book number of The book";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmp(bk.retbno(),n)==0)
        {
            bk.show_book();
            cout<<"\nEnter The New Details of book"<<endl;
            bk.modify_book();
            int temp=sizeof(bk);
            int pos=-temp;
            fp.seekp(pos,ios::cur);
            fp.write((char*)&bk,sizeof(book));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n Record Not Found ";
        
    printf("\nEnter any character to exit followed by enter.");        
    cin>>character;
}

void modify_student()
{
    char n[6];
    int found=0;
    cout << "\033[2J\033[1;1H";
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The admission number of The student";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmp(st.retadmno(),n)==0)
        {
            st.show_student();
            cout<<"\nEnter The New Details of student"<<endl;
            st.modify_student();
            int temp=sizeof(st);
            int pos=-temp;
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    
    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    
    printf("\nEnter any character to exit followed by enter.");
    cin>>character;
}

void delete_student()
{
    char n[6];
    int flag=0;    
    cout << "\033[2J\033[1;1H";
    cout<<"\n\n\n\tDELETE STUDENT...";
    cout<<"\n\nEnter The admission number of the Student You Want To Delete : ";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
     while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmp(st.retadmno(),n)!=0)
                 fp2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }
        
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    if(flag==1)
        cout<<"\n\n\tRecord Deleted ..";
    else
    cout<<"\n\nRecord not found";
    
    printf("\nEnter any character to exit followed by enter.");
    cin>>character;
}

void delete_book()
{
    char n[6];
    int flag=0;
    cout << "\033[2J\033[1;1H";
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book number of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmp(bk.retbno(),n)!=0)  
        {
            fp2.write((char*)&bk,sizeof(book));
        }
        else
               flag=1;
    }
        
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    if(flag==1)
        cout<<"\n\n\tRecord Deleted ..";
    else
    cout<<"\n\nRecord not found";
    
    printf("\nEnter any character to exit followed by enter.");
    cin>>character;
}

void display_alls()
{
    cout << "\033[2J\033[1;1H";
    fp.open("student.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        printf("\nEnter any character to exit followed by enter.");
        cin>>character;
        return;
    }

    cout<<"\n\t\tSTUDENT LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"\tAdmission No."<<setw(20)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }
         
    fp.close();
    printf("\nEnter any character to exit followed by enter.");
    cin>>character;
}

void display_allb()
{
    cout << "\033[2J\033[1;1H";
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        printf("\nEnter any character to exit followed by enter.");
        cin>>character;
        return;
    }

    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(20)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    printf("\nEnter any character to exit followed by enter.");
    cin>>character;
}

void book_issue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
    cout << "\033[2J\033[1;1H";
    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter The student's admission number";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
    if(strcmp(st.retadmno(),sn)==0)
    {
        found=1;
        if(st.rettoken()==0)
        {
            cout<<"\n\n\tEnter the book number ";
            cin>>bn;
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmp(bk.retbno(),bn)==0)
            {
                bk.show_book();
                flag=1;
                st.addtoken();
                st.getstbno(bk.retbno());
                int temp=sizeof(st);
                int pos=-temp;
                fp.seekp(pos,ios::cur);
                fp.write((char*)&st,sizeof(student));
                cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";   
            }
            }
           if(flag==0)
                cout<<"Book no does not exist";
        }
        else
           cout<<"You have not returned the last book ";

    }
    }
    if(found==0)
    cout<<"Student record not exist...";
    printf("\nEnter any character to exit followed by enter.");
    cin>>character;
    fp.close();
    fp1.close();
}

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    cout << "\033[2J\033[1;1H";
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student's admission number";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmp(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmp(bk.retbno(),st.retstbno())==0)
            {
                bk.show_book();
                flag=1;
                cout<<"\n\nBook deposited in number of days";
                cin>>day;
                if(day>15)
                {
                   fine=(day-15)*1;
                   cout<<"\n\nFine has to deposited Rs. "<<fine;
                }
                    st.resettoken();
                    int temp=sizeof(st);
                    int pos=-temp;
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\n\n\t Book deposited successfully";
            }
            }
          if(flag==0)
            cout<<"Book no does not exist";
            }
        else
            cout<<"No book is issued..please check!!";
        }
       }
    if(found==0)
    cout<<"Student record not exist...";
    printf("\nEnter any character to exit followed by enter.");
    cin>>character;
    fp.close();
    fp1.close();
  }

void intro()
{
    cout << "\033[2J\033[1;1H";
    cout<<"LIBRARY";
    cout<<"MANAGEMENT";
    cout<<"SYSTEM";
    cout<<"\n\nMADE BY : YOUR NAME";
    cout<<"\n\nSCHOOL : SCHOOL NAME";
    system("pause");
}


void admin_menu()
{
    cout << "\033[2J\033[1;1H";
    int ch2;
    cout<<"\n\n\n\tADMINISTRATOR MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.CREATE BOOK ";
    cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
    cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout<<"\n\n\t9.MODIFY BOOK ";
    cout<<"\n\n\t10.DELETE BOOK ";
    cout<<"\n\n\t11.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
    cin>>ch2;
    switch(ch2)
    {
            case 1: cout << "\033[2J\033[1;1H";
                write_student();break;
            case 2: display_alls();break;
            case 3:
                   char num[6];
                   cout << "\033[2J\033[1;1H";
                   cout<<"\n\n\tPlease Enter The Admission No. ";
                   cin>>num;
                   display_sps(num);
                   break;
              case 4: modify_student();break;
              case 5: delete_student();break;
        case 6: cout << "\033[2J\033[1;1H";
            write_book();break;
        case 7: display_allb();break;
        case 8: {
                   char num[6];
                   cout << "\033[2J\033[1;1H";
                   cout<<"\n\n\tPlease Enter The book No. ";
                   cin>>num;
                   display_spb(num);
                   break;
            }
              case 9: modify_book();break;
              case 10: delete_book();break;
             case 11: return;
              default:cout<<"\a";
    }
    admin_menu();
}

int main()
{
    cout << "\033[2J\033[1;1H";
    char ch;
    intro();
    do
    {
        cout << "\033[2J\033[1;1H";
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. BOOK ISSUE";
        cout<<"\n\n\t02. BOOK DEPOSIT";
          cout<<"\n\n\t03. ADMINISTRATOR MENU";
          cout<<"\n\n\t04. EXIT";
          cout<<"\n\n\tPlease Select Your Option (1-4) ";
          cin>>ch;
          switch(ch)
          {
            case '1':cout << "\033[2J\033[1;1H";
                 book_issue();
                    break;
              case '2':book_deposit();
                     break;
              case '3':admin_menu();
                 break;
              case '4':exit(0);
              default :cout<<"\a";
        }
        }while(ch!='4');
}
