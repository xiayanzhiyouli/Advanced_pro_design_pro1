#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
#include <iomanip>

#include <fstream>
#include <cstdlib>
#include <sstream>

#include "admin.h"

using namespace std;

void Administrator_login();
void User_register();
void User_login();
void Administrator_main();

Admin* p2ad = new Admin;

void signin()
{
    cout << "  Commodity Trading Plattform  "<<endl;
    cout << "  Xia Yan 201220077 NJUCS"<<endl;
    cout << endl<<endl;
}

void main_platform()
{
    while(1)
    {
        cout <<"==========================================="<<endl;
        cout <<"1: Administrator Login"<<endl;
        cout <<"2: User Register"<<endl;
        cout <<"3: User Login"<<endl;
        cout <<"4: Exit"<<endl;
        cout <<"==========================================="<<endl;

        string input;
        cout << "Input the number of the operation you want."<<endl;
        cin >> input;
        if(input == "1")
        {
            Administrator_login();
        }
        else if(input == "2")
        {
            User_register();
        }
        else if(input == "3")
        {
            User_login();
        }
        else if(input == "4")
        {
            system("clear");
            break;
        }
        else
        {
            system("clear");
            cout << "The number you inputed is wrong. Please check it."<<endl;
        }
    }
}

void Administrator_login()
{
    string name,password;
    cout << "Please input the name of the administrator."<<endl;
    cin >> name;
    cout << "Please input the password of the administrator."<<endl;
    cin >> password;

    if(p2ad->Get_name() == name && p2ad->Get_password() == password)
    {
        system("clear");
        cout << "-------Login successfully-------"<<endl;
        cout <<endl<<endl;
        Administrator_main();
    }
    else
    {
        system("clear");
        cout << "Wrong password! Please check your name or password."<<endl;
    }
}

void User_register()
{

}

void User_login()
{

}

void Administrator_main()
{
    while(1)
    {
        cout <<"==========================================="<<endl;
        cout <<"1: "<<endl;
        cout <<"2: User Register"<<endl;
        cout <<"3: User Login"<<endl;
        cout <<"4: Exit"<<endl;
        cout <<"==========================================="<<endl;

        string input;
        cout << "Input the number of the operation you want."<<endl;
        cin >> input;
        if(input == "1")
        {
            Administrator_login();
        }
        else if(input == "2")
        {
            User_register();
        }
        else if(input == "3")
        {
            User_login();
        }
        else if(input == "4")
        {
            system("clear");
            break;
        }
        else
        {
            system("clear");
            cout << "The number you inputed is wrong. Please check it."<<endl;
        }
    }
}