
#include<iostream>
#include<istream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <unordered_map>
#include<windows.h>
#include<ctime>

using namespace std;

class Library
{
    private:
        struct NodeB                        //Books
        {
            int id;
            string name ,author,publisher;
            NodeB* nextB;
        };

        struct NodeMember                       //Members
        {
            int Mid;
            string Mname ,MNIC,Maddress;
            NodeMember *nextM;
        };

    public:
        NodeB*head=NULL;             //Book pointer
        NodeMember *headM=NULL;          //Member Pointer
        unordered_map<int, pair<string, time_t>> issuedBooks;  // Maps book ID to customer ID and return date


        void log();
        void login();
        void registerA();
        void memberMenu();
        void bookMenu();
        void adminD();
        void printHeader(); 
        void issueBook();
        void showIssuedBooks();  // Function to display issued books

        //members methods..
        void addM();
        void searchM();
        void updateM();
        void deleteM();
        void sortM();
        void showM();

        //books methods..
        void insert();
        void search();
        void update();
        void del();
        void sort();
        void show();

};

 void Library::issueBook() {
    printHeader();
    if (head == NULL) {
        cout << "\n\nNo records found!";
        return;
    }

    int bookId;
    string customerId;
    int days;
    cout << "Enter Book ID to issue: ";
    cin >> bookId;
    cout << "Enter Customer ID: ";
    cin >> customerId;
    cout << "Enter Time Limit (in days): ";
    cin >> days;

    NodeB *ptr = head, *prev = NULL;
    while (ptr != NULL) {
        if (ptr->id == bookId) {
            // Book found
            cout << "Issuing book:" << endl;
            cout << "Book ID: " << ptr->id << endl;
            cout << "Author: " << ptr->author << endl;
            cout << "Title: " << ptr->name << endl;
            cout << "Publisher: " << ptr->publisher << endl;

            // Calculate return date
            time_t now = time(0);
            time_t returnDate = now + days * 86400; // 86400 seconds per day

            // Add to issuedBooks map
            issuedBooks[bookId] = {customerId, returnDate};

            // Delete book from library
            if (ptr == head) {
                head = head->nextB;
            } else {
                prev->nextB = ptr->nextB;
            }
            delete ptr;

            cout << "Book issued successfully!\n";
            return;
        }
        prev = ptr;
        ptr = ptr->nextB;
    }

    cout << "Book with ID " << bookId << " not found!" << endl;
}

void Library::showIssuedBooks() {
    printHeader();
    if (issuedBooks.empty()) {
        cout << "\n\nNo books have been issued.";
        cout << "\nPress Enter to return to the main menu...";
        cin.ignore();
        cin.get();
        bookMenu();
        return;
         
    }

    cout << "Issued Books:\n";
    for (const auto& issuedBook : issuedBooks) {
        int bookId = issuedBook.first;
        string customerId = issuedBook.second.first;
        time_t returnDate = issuedBook.second.second;

        // Convert return date to readable format
        char returnDateStr[20];
        strftime(returnDateStr, sizeof(returnDateStr), "%Y-%m-%d", localtime(&returnDate));

        cout << "Book ID: " << bookId << endl;
        cout << "Customer ID: " << customerId << endl;
        cout << "Return Date: " << returnDateStr << endl;
        cout << "------------------------------------------" << endl;
    }
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
    bookMenu();


}

HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

void Library::printHeader() {

    SetConsoleTextAttribute(h, 5);
    cout << "\n\n\t\t\t\t\t=====================================================";
    SetConsoleTextAttribute(h, 1);
    cout << "\n\n\t\t\t\t\t========***** LIBRARY MANAGEMENT SYSTEM *****========";
    cout << "\n\n\t\t\t\t\t=============== THE KNOWLEDGE CORNER ================";
    SetConsoleTextAttribute(h, 5);
    cout << "\n\n\t\t\t\t\t=====================================================\n\n";
    SetConsoleTextAttribute(h, 15);  // Reset to default color

}

void Library::memberMenu()
{
        y:
        system("cls");
        int sl;

        printHeader(); 
        SetConsoleTextAttribute(h,10);
        cout<<"\n\n\t\t\t\t\t      =======**** Member Section ****=======";
        SetConsoleTextAttribute(h,15);
        cout<<"\n\n\n\t\t\t\t\t\t 1. Add New Member";
        cout<<"\n\n\t\t\t\t\t\t 2. Search Member";
        cout<<"\n\n\t\t\t\t\t\t 3. Update Member";
        cout<<"\n\n\t\t\t\t\t\t 4. Delete Member";
        cout<<"\n\n\t\t\t\t\t\t 5. Show All Members";
        cout<<"\n\n\t\t\t\t\t\t 6. Go To Main Menu";
        cout<<"\n\n\t\t\t\t\t\t 7. Exit";
        cout<<"\n\n\n\t\t\t\t\t\t Enter Your Choice :";
        cin>>sl;

        switch(sl)
        {
        case 1:
            addM();
            break;

        case 2:
            searchM();
            break;

        case 3:
            updateM();
            break;

        case 4:
            deleteM();
            break;

        case 5:
            sortM();
            showM();
            break;

        case 6:
            adminD();
            break;

        case 7:
            exit(0);
        default:
            cout<<"Invalid Input!..........";
        }

        getch();
        goto y;
}

void Library::addM()
{
    system("cls");
        printHeader(); 

        NodeMember *new_NodeMember=new NodeMember;

        SetConsoleTextAttribute(h,15);
        cout<<"\n\n Member ID : ";
        cin>>new_NodeMember -> Mid;

        cout<<"\n\n Member Name : ";
        cin>>new_NodeMember -> Mname;

        cout<<"\n\n Member NIC : ";
        cin>>new_NodeMember -> MNIC;

        cout<<"\n\n Member Address : ";
        cin>>new_NodeMember -> Maddress;

        new_NodeMember -> nextM=NULL;

        if(headM==NULL)
        {
            headM=new_NodeMember;
        }
        else
        {
            NodeMember *ptrm=headM;
            while(ptrm -> nextM !=NULL)
            {
                ptrm=ptrm -> nextM;
            }
            ptrm->nextM=new_NodeMember;
        }
        cout<<"\n\n\t\t\ New Member Registered Successfully....";
}

void Library::searchM()
{
        system("cls");

        int t_Mid,foundM=0;

        printHeader();

        SetConsoleTextAttribute(h,2);
        if(headM==NULL)
        {
            cout<<"\n\n Linked List is Empty....";
        }
        else
        {
            cout<<"\n\n Member ID : ";
            cin>>t_Mid;
            NodeMember *ptrm =headM;

            while(ptrm !=NULL)
            {
                if(t_Mid==ptrm -> Mid)
                {
                    system("cls");

                    printHeader(); 

                    SetConsoleTextAttribute(h,15);
                    cout<<"\n\n\t Member ID : "<<ptrm -> Mid;
                    cout<<"\n\n Member Name : "<<ptrm -> Mname;
                    cout<<"\n\n Member NIC : "<<ptrm -> MNIC;
                    cout<<"\n\n Member Address : "<<ptrm -> Maddress;
                    foundM++;
                }
                ptrm =ptrm -> nextM;

            }
            if(foundM==0)
            {
                SetConsoleTextAttribute(h,2);
                cout<<"\n\n\t\t Member ID is Invalid....";
            }
        }

}

void Library::updateM()
{
    system("cls");

        int t_Mid,foundM=0;

       printHeader(); 

        if(headM==NULL)
        {
            cout<<"\n\n Linked List is Empty....";
        }
        else
        {
            SetConsoleTextAttribute(h,15);
            cout<<"\n\n Member ID : ";
            cin>>t_Mid;
            NodeMember *ptrm =headM;

            while(ptrm !=NULL)
            {
                if(t_Mid==ptrm -> Mid)
                {
                    system("cls");

                    printHeader(); 

                    cout<<"\n\n\t Member ID : ";
                    cin>>ptrm -> Mid;
                    cout<<"\n\n Member Name : ";
                    cin>>ptrm -> Mname;
                    cout<<"\n\n Member NIC : ";
                    cin>>ptrm -> MNIC;
                    cout<<"\n\n Member Address : ";
                    cin>>ptrm -> Maddress;
                    foundM++;

                    SetConsoleTextAttribute(h,2);
                    cout<<"\n\n\t\t\t Member Updated Successfully....";
                }
                ptrm =ptrm -> nextM;

            }
            if(foundM==0)
            {
                cout<<"\n\n\t\t Member ID is Invalid....";
            }
        }

}

void Library::deleteM()
{
        system("cls");

        int t_Mid,foundM=0;
        SetConsoleTextAttribute(h,5);

        printHeader(); 

        SetConsoleTextAttribute(h,2);

        if(headM == NULL)
        {
            cout<<"\n\n Linked List is Empty....";
        }
        else
        {
            SetConsoleTextAttribute(h,15);
            cout<<"\n\n Member ID : ";
            cin>>t_Mid;
            if(t_Mid==headM->Mid)
            {
                NodeMember *ptrm=headM;
                headM =headM ->nextM;
                delete ptrm;
                SetConsoleTextAttribute(h,2);
                cout<<"\n\n Member Deleted Successfully....";

                foundM++;
            }
            else
            {
                NodeMember *prem=headM;
                NodeMember*ptrm=headM;

                while(ptrm !=NULL)
                {
                    if(t_Mid==ptrm->Mid)
                    {
                        prem->nextM=ptrm->nextM;
                        delete ptrm;
                        cout<<"\n\n  Member Deleted Successfully....";
                        foundM++;
                        break;
                    }
                    prem=ptrm;
                    ptrm=ptrm->nextM;
                }

            }
            if(foundM==0)
            {
                cout<<"\n\n Member ID is Invalid.....";
            }
        }
}

void Library::sortM()
{
    if(headM==NULL)
    {
        system("cls");

        printHeader(); 

        SetConsoleTextAttribute(h,2);

        cout<<"\n\n Linked List is Empty....";
        getch();
        memberMenu();
    }
    int countM=0,t_Mid;
    string t_Mname,t_MNIC,t_Maddress;
    NodeMember *ptrm=headM;

    while(ptrm !=NULL)
    {
        countM++;
        ptrm =ptrm -> nextM;
    }
    for(int i=1;i<=countM;i++)
    {
        NodeMember *ptrm=headM;
        for(int j=1;j<countM;j++)
        {
            if(ptrm -> Mid > ptrm -> nextM ->Mid)
            {
                //save data into temporary variables..
                t_Mid=ptrm ->Mid;
                t_Mname=ptrm ->Mname;
                t_MNIC=ptrm ->MNIC;
                t_Maddress=ptrm ->Maddress;

                //save data into current Node..
                ptrm->Mid=ptrm->nextM->Mid;
                ptrm->Mname=ptrm->nextM->Mname;
                ptrm->MNIC=ptrm->nextM->MNIC;
                ptrm->Maddress=ptrm->nextM->Maddress;

                //save data into next Node..
                ptrm->nextM->Mid=t_Mid;
                ptrm->nextM->Mname=t_Mname;
                ptrm->nextM->MNIC=t_MNIC;
                ptrm->nextM->Maddress=t_Maddress;
            }
            ptrm=ptrm ->nextM;
        }

    }
}

void Library::showM()
{
    system("cls");

        printHeader(); 

        NodeMember *ptrm =headM;

        while(ptrm !=NULL)
        {
            cout<<"\n\n -> Member ID : "<<ptrm -> Mid;
            cout<<"\n\n ->Member Name : "<<ptrm -> Mname;
            cout<<"\n\n ->Member NIC : "<<ptrm -> MNIC;
            cout<<"\n\n ->Member Address : "<<ptrm -> Maddress;
            cout<<"\n\n ================================================";

            ptrm =ptrm -> nextM;
        }

}

void Library::bookMenu()
{
    p:
        system("cls");
        int choice;

       printHeader(); 

        cout<<"\n\n\n\t\t\t\t\t\t 1. Insert New Record";
        cout<<"\n\n\t\t\t\t\t\t 2. Search Record";
        cout<<"\n\n\t\t\t\t\t\t 3. Update Record";
        cout<<"\n\n\t\t\t\t\t\t 4. Delete Record";
        cout<<"\n\n\t\t\t\t\t\t 5. Show All Record";
        cout<<"\n\n\t\t\t\t\t\t 6. Issue Book";
        cout<<"\n\n\t\t\t\t\t\t 7. Show All Issued books";
        cout<<"\n\n\t\t\t\t\t\t 8. Go To Main Menu";
        cout<<"\n\n\t\t\t\t\t\t 9. Exit";
        cout<<"\n\n\n\t\t\t\t\t\t Enter Your Choice :";

        cin>>choice;

        switch(choice)
        {
        case 1:
            insert();
            break;

        case 2:
            search();
            break;

        case 3:
            update();
            break;

        case 4:
            del();
            break;

        case 5:
            sort();
            show();
            break;

        case 6:
            issueBook();
            break;

        case 7:
            showIssuedBooks();
            exit(0);
        
        case 8:
            adminD();
            break;
        
        case 9:
            exit;
        default:

            cout<<"\n\n Invalid Choice!....Please Try Again!.......";
        }
        getch();
        goto p;
}

void Library::insert()
{
        system("cls");

        printHeader(); 

        NodeB* new_NodeB=new NodeB;

        cout<<"\n\n Book ID : ";
        cin>>new_NodeB-> id;

        cout<<"\n\n Book Name : ";
        cin>>new_NodeB-> name;

        cout<<"\n\n Author Name : ";
        cin>>new_NodeB-> author;

        cout<<"\n\n Publisher Name : ";
        cin>>new_NodeB-> publisher;
        new_NodeB-> nextB=NULL;

        if(head==NULL)
        {
            head=new_NodeB;
        }
        else
        {
            NodeB*ptr=head;
            while(ptr -> nextB !=NULL)
            {
                ptr=ptr -> nextB;
            }
            ptr->nextB=new_NodeB;
        }
        SetConsoleTextAttribute(h,2);
        cout<<"\n\n\t\t\ New Book Inserted Successfully....";

}

void Library::search()
{
        system("cls");

        int t_id,found=0;

        printHeader(); 

        if(head==NULL)
        {
            cout<<"\n\n The Linked List is Empty!....";
        }
        else
        {
            SetConsoleTextAttribute(h,15);
            cout<<"\n\n Book ID : ";
            cin>>t_id;
            NodeB*ptr =head;

            while(ptr !=NULL)
            {
                if(t_id==ptr -> id)
                {
                    system("cls");

                    printHeader(); 

                    SetConsoleTextAttribute(h,15);
                    cout<<"\n\n -> Book ID : "<<ptr -> id;
                    cout<<"\n\n -> Book Name : "<<ptr -> name;
                    cout<<"\n\n -> Author Name : "<<ptr -> author;
                    cout<<"\n\n -> Publisher Name : "<<ptr -> publisher;
                    found++;
                }
                ptr =ptr -> nextB;

            }
            if(found==0)
            {
                SetConsoleTextAttribute(h,2);
                cout<<"\n\n\t\t Book ID is Invalid....";
            }
        }

}
void Library::update()
{
        system("cls");

        int t_id,found=0;

        printHeader(); 

        if(head==NULL)
        {
            cout<<"\n\n Linked List is Empty....";
        }
        else
        {
            SetConsoleTextAttribute(h,15);
            cout<<"\n\n Book ID : ";
            cin>>t_id;
            NodeB*ptr =head;

            while(ptr !=NULL)
            {
                if(t_id==ptr -> id)
                {
                    system("cls");

                    printHeader(); 

                    SetConsoleTextAttribute(h,15);

                    cout<<"\n\n\t Book ID : ";
                    cin>>ptr -> id;
                    cout<<"\n\n Book Name : ";
                    cin>>ptr -> name;
                    cout<<"\n\n Author Name : ";
                    cin>>ptr -> author;
                    cout<<"\n\n Publisher Name : ";
                    cin>>ptr -> publisher;
                    found++;
                    SetConsoleTextAttribute(h,2);
                    cout<<"\n\n\t\t\t Book Updated Successfully!....";
                }
                ptr =ptr -> nextB;

            }
            if(found==0)
            {
                cout<<"\n\n\t\t Book ID is Invalid....";
            }
        }

}

void Library::del()
{
        system("cls");

        int t_id,found=0;
        printHeader(); 

        if(head == NULL)
        {
            cout<<"\n\n The Linked List is Empty....";
        }
        else
        {
            SetConsoleTextAttribute(h,15);
            cout<<"\n\n Book ID : ";
            cin>>t_id;
            if(t_id==head->id)
            {
                NodeB*ptr=head;
                head =head ->nextB;
                delete ptr;
                SetConsoleTextAttribute(h,2);
                cout<<"\n\n  Book Deleted Successfully....";
                found++;
            }
            else
            {
                NodeB*pre=head;
                NodeB*ptr=head;

                while(ptr !=NULL)
                {
                    if(t_id==ptr->id)
                    {
                        pre->nextB=ptr->nextB;
                        delete ptr;
                        cout<<"\n\n Delete Book Successfully....";
                        found++;
                        break;
                    }
                    pre=ptr;
                    ptr=ptr->nextB;
                }

            }
            if(found==0)
            {
                cout<<"\n\n Book ID is Invalid.....";
            }
        }
}

void Library::sort()
{

    if(head==NULL)
    {
        system("cls");

        printHeader(); 

        cout<<"\n\n\t\t\t\t The Linked List is Empty....";
        getch();
        bookMenu();
    }
    int count=0,t_id;
    string t_name,t_author,t_publisher;
    NodeB*ptr=head;

    while(ptr !=NULL)
    {
        count++;
        ptr =ptr -> nextB;
    }
    for(int i=1;i<=count;i++)
    {
        NodeB*ptr=head;
        for(int j=1;j<count;j++)
        {
            if(ptr -> id > ptr -> nextB ->id)
            {
                //save data into temporary variables..
                t_id=ptr ->id;
                t_name=ptr ->name;
                t_author=ptr ->author;
                t_publisher=ptr ->publisher;

                //save data into current Node..
                ptr->id=ptr->nextB->id;
                ptr->name=ptr->nextB->name;
                ptr->author=ptr->nextB->author;
                ptr->publisher=ptr->nextB->publisher;

                //save data into next Node..
                ptr->nextB->id=t_id;
                ptr->nextB->name=t_name;
                ptr->nextB->author=t_author;
                ptr->nextB->publisher=t_publisher;
            }
            ptr=ptr ->nextB;
        }

    }

}
void Library::show()
{
        system("cls");

        printHeader(); 

        SetConsoleTextAttribute(h,2);

        NodeB*ptr =head;

        while(ptr !=NULL)
        {
            SetConsoleTextAttribute(h,15);
            cout<<"\n\n -> Book ID : "<<ptr -> id;
            cout<<"\n\n -> Book Name : "<<ptr -> name;
            cout<<"\n\n -> Author Name : "<<ptr -> author;
            cout<<"\n\n -> Publisher Name : "<<ptr -> publisher;
            cout<<"\n\n =============================================";

            ptr =ptr -> nextB;
        }


}
void Library::log()
{
    int ch;
    SetConsoleTextAttribute(h,5);
    cout<<"\n\t\t\t   .....................................................................";
    cout<<"\n\n\t\t\t  ---------------********** U S E R -L O G I N **********---------------";
    cout<<"\n\n\t\t\t   .....................................................................";
    SetConsoleTextAttribute(h,15);
    cout<<"\n\n\n\n\t\t\t\t\t\t            1.LOGIN ";
    cout<<"\n\n\t\t\t\t\t\t            2.REGISTER";
    SetConsoleTextAttribute(h,15);
    cout<<"\n\n\n\n\t\t\t\t\t\t     Enter Your Choice: ";
    cin>>ch;

    switch(ch)
    {
    case 1:
        login();
        break;

    case 2:
        registerA();
        break;

    default:

        system("cls");
        cout<<"\n\n\n\n\t\t\t\t\t\t     Invalid Choice....";
        log();
    }

}

void Library::registerA()
{
    string reg_user,reg_pass;
    system("cls");
    cout<<"\n\n\n\n\t\t\t\t\t\t     -> Enter the Username: ";
    cin>>reg_user;
    cout<<"\n\n\n\n\t\t\t\t\t\t     -> Enter the Password: ";
    cin>>reg_pass;

    ofstream reg("login.txt", ios::app);
    reg<<reg_user<<' '<<reg_pass<<endl;
    system("cls");
    cout<<"\n\n\n\n\t\t\t\t\t        Registration successful!.....";
    log();
}

void Library::login()
{
    int exist=0;
    string user,pass,u,p;
    system("cls");
    cout<<"\n\n\n\n\t\t\t\t\t\t     -> Enter the Username: ";
    cin>>user;
    cout<<"\n\n\n\n\t\t\t\t\t\t     -> Enter the Password: ";
    cin>>pass;

    ifstream input("login.txt");

    while(input>>u>>p)
    {
        if(u == user && p == pass)
        {
            exist=1;
        }
    }
    input.close();

    if(exist == 1)
    {
        x:
        int slc;
        system("cls");
       printHeader(); 
        SetConsoleTextAttribute(h,7);

        cout<<"\n\n\t\t\t\t\t\t            1. Library Member ";
        cout<<"\n\n\t\t\t\t\t\t            2. Library Books ";
        cout<<"\n\n\n\n\t\t\t\t\t\t     Select Your Choice : ";
        cin>>slc;
        cout<<"\n\n\t\t\t\t\t\t===================***************=================";

        switch(slc)
        {
        case 1:
            memberMenu();
            break;

        case 2:
            bookMenu();
            break;

        default:
            system("cls");
            cout<<"\n\n\t\t\t\t\t .....Invalid Input.....";
        }

        getch();
        goto x;

    }
    else
    {
        system("cls");
        cout<<"\n\n\n\n\t\t\t\t\t\t     Login Error...";
        cout<<"\n\n\n\n\t\t\t\t\t      Invalid Username or Password...";
        log();
    }
}

void Library::adminD()
 {
        z:
        int slc;
        system("cls");
        SetConsoleTextAttribute(h,14);
        cout<<"\n\n\t\t\t\t\t\=====================================";
        cout<<"\n\n\t\t\t\t\t\===== LIBRARY MANAGEMENT SYSTEM =====";
        cout<<"\n\n\t\t\t\t\t\=====================================";
        SetConsoleTextAttribute(h,2);

        cout<<"\n\n\n\n\t\t\t\t\t\t\ 1. Library Member ";
        cout<<"\n\n\t\t\t\t\t\t\ 2. Library Books ";
        cout<<"\n\n\n\n\n\t\t\t\t\t\tSelect Your Choice : ";
        cin>>slc;
        cout<<"\n\n\t\t\t\t\t\t====================================";

        switch(slc)
        {
        case 1:
            memberMenu();
            break;

        case 2:
            bookMenu();
            break;

        default:
            system("cls");
            cout<<"\n\n\t\t\t\t\t .....Invalid Input.....";
        }

        getch();
        goto z;

    }

int main()
{
    Library obj;
    obj.log();

    return 0;
}









