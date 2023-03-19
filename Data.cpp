//reading medicines data and storing in a file
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    ofstream f("medicines.txt");
    char name[20];
    int cnt, cost;
    cout<<"Enter details of 10 medicines"<<endl;
    for(int i = 0; i < 10; i ++)
    {
        cout<<"Enter name of the medicine: ";
        cin>>name;
        cout<<"Enter quantity: ";
        cin>>cnt;
        cout<<"Enter the cost of one unit: ";
        cin>>cost;
        cout<<name<<" "<<cnt<<" "<<cost<<endl;
        f<<name<<" "<<cnt<<" "<<cost<<endl;
    }
    f.close();
}
