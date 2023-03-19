#include<iostream>
#include<fstream>
#include<string.h>
#include <windows.h>
#include<iomanip>
using namespace std;

class pharmacy
{
protected:
    struct medicine{
    char medname[20];
    int qty;
    int price;
    }s[10],s1[10];
    int qtyFromCustomer[10];
public:
    void getmedicines();
    void updatemedicines();
};

class customer;
class shopkeeper: public pharmacy
{
    float bill;
    int index;
public:
    void printreciept(customer);
    void reciepttofile(customer);
    void readmedicines();
};

class customer:public pharmacy
{
    char name[30],gender;
    int age;
public:
    void readcustomerdetails();
    friend class shopkeeper;

};

//getting medicines from file and storing it in a structure
void pharmacy::getmedicines()
{
    ifstream fin("medicines.txt");
    for(int i=0;i<10;i++)
    {
    fin>>s[i].medname>>s[i].qty>>s[i].price;
    }
    fin.close();
}

void customer::readcustomerdetails()
{
	cout<<"Enter patient's name: ";
	cin>>name;
	cout<<"Enter patient's age: ";
	cin>>age;
	cout<<"Enter patient's gender: ";
	cin>>gender;
}

void shopkeeper::readmedicines()
{
    int i=0;
    index = 0;
    char op;
    do
    {
        char m[30];
        int q;
        cout<<"Enter medicine name: ";
        cin>>m;
        int flag = 0;
        for(i = 0; i < 10; i ++)
        {
            if(strcmpi(s[i].medname, m) == 0)
            {
            	cout<<"Enter qty for "<<m<<": ";
              cin>>q;
                if(s[i].qty >= q)
                {
                    s1[index] = s[i];
                    s1[index].qty = q;
                    s[i].qty -= q;
                    index ++;
                    break;
                }
                else
                {
                    cout<<"Insufficient quantity"<<endl;
                    break;
                }
            }
        }
        if(i >= 10)
            cout<<"Medicine not available"<<endl;
        cout<<"Do you have more medicines to order?Enter Y/N"<<endl;
        cin>>op;
    }while(op!='n' && op!='N');
}

void shopkeeper::printreciept(customer obj)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	cout<<"---------------------------------------------------------------------------\n";
	cout<<setw(40)<<setfill(' ')<<"RECIEPT"<<endl;
	cout<<"---------------------------------------------------------------------------\n";
	cout<<setw(45)<<setfill(' ')<<"ARSV PHARMACY \n";
	cout<<setw(22)<<setfill(' ')<<"Name  :   "<<obj.name<<endl;
	cout<<setw(21)<<setfill(' ')<<"Age  :   "<<obj.age<<"             ";
	cout<<setw(22)<<setfill(' ')<<"Time  :   "<<setw(2)<<setfill('0')<<st.wHour<<":"<<setw(2)<<setfill('0')<< st.wMinute<<endl;
  	cout<<endl;
	int i,cost=0;
    cout<<setw(20)<<setfill(' ')<<"MEDICINE"<<setw(10)<<setfill(' ')<<"QTY"<<setw(20)<<setfill(' ')<<"COST PER MEDICINE"<<setw(15)<<setfill(' ')<<"TOTAL COST"<<endl;
    for(i = 0; i < index; i ++)
    {
    	cost+=s1[i].qty*s1[i].price;
        cout<<setw(20)<<setfill(' ')<<s1[i].medname<<setw(10)<<setfill(' ')<<s1[i].qty<<setw(20)<<setfill(' ')<<s1[i].price<<setw(15)<<setfill(' ')<<s1[i].qty*s1[i].price<<endl;
    }
    cout<<endl;
    cout<<setw(30)<<setfill(' ')<<"TOTAL AMOUNT   :  "<<cost<<endl;
    cout<<"---------------------------------------------------------------------------\n";
    int q=1;
    char w=q;
    cout<<setw(20)<<setfill(' ')<<"\t   "<<w<<" THANK YOU! VISIT AGAIN!! "<<w<<endl;
    cout<<"---------------------------------------------------------------------------\n";
    cout<<endl<<endl<<endl<<endl<<endl;
}
void shopkeeper::reciepttofile(customer obj)
{
	ofstream fout("medreceipt.txt");
	SYSTEMTIME st;
	GetLocalTime(&st);
	fout<<"---------------------------------------------------------------------------\n";
	fout<<setw(40)<<setfill(' ')<<"RECIEPT"<<endl;
	fout<<"---------------------------------------------------------------------------\n";
	fout<<setw(45)<<setfill(' ')<<"ARSV PHARMACY \n";
	fout<<setw(22)<<setfill(' ')<<"Name  :   "<<obj.name<<endl;
	fout<<setw(21)<<setfill(' ')<<"Age  :   "<<obj.age<<"             ";
	fout<<setw(22)<<setfill(' ')<<"Time  :   "<<setw(2)<<setfill('0')<<st.wHour<<":"<<setw(2)<<setfill('0')<< st.wMinute<<endl;
  	fout<<endl;
	int i,cost=0;
    fout<<setw(20)<<setfill(' ')<<"MEDICINE"<<setw(10)<<setfill(' ')<<"QTY"<<setw(20)<<setfill(' ')<<"COST PER MEDICINE"<<setw(15)<<setfill(' ')<<"TOTAL COST"<<endl;
    for(i = 0; i < index; i ++)
    {
    	cost+=s1[i].qty*s1[i].price;
        fout<<setw(20)<<setfill(' ')<<s1[i].medname<<setw(10)<<setfill(' ')<<s1[i].qty<<setw(20)<<setfill(' ')<<s1[i].price<<setw(15)<<setfill(' ')<<s1[i].qty*s1[i].price<<endl;
    }
    fout<<endl;
    fout<<setw(30)<<setfill(' ')<<"TOTAL AMOUNT   :  "<<cost<<endl;
    fout<<"---------------------------------------------------------------------------\n";
    int q=1;
    char w=q;
    fout<<setw(20)<<setfill(' ')<<"\t   "<<w<<" THANK YOU! VISIT AGAIN!! "<<w<<endl;
    fout<<"---------------------------------------------------------------------------\n";
}

void pharmacy::updatemedicines(){
	ofstream fout("medicines.txt");
	for(int i=0;i<10;i++){
		fout<<s[i].medname<<" "<<s[i].qty<<" "<<s[i].price<<endl;
	}
	fout.close();
}

int main()
{
	cout<<"WELCOME TO OUR PHARMACY\n";
	cout<<"---------------------------------------------------------------------------\n";
    shopkeeper obj;
    obj.getmedicines();
    customer cus;
    cus.readcustomerdetails();
    obj.readmedicines();
    obj.printreciept(cus);
    obj.reciepttofile(cus);
    obj.updatemedicines();
    return 0;
}
