#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
#include <iomanip>

#include <fstream>
#include <cstdlib>
#include <sstream>

#include <unistd.h>

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
    sleep(1);
}

void main_platform()
{
    while(1)
    {
        system("clear");
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
            break;
        }
        else
        {
            cout << "The number you inputed is wrong. Please check it."<<endl;
            sleep(1);
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
        sleep(1);
        Administrator_main();
    }
    else
    {
        system("clear");
        cout << "Wrong password! Please check your name or password."<<endl;
        sleep(1);
    }
}

void User_register()
{
    string id,name,tele,password1,password2,addr,last_str_id,all_content;

    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
    }
    else
    {
        while (!in.eof() )
        {
            string buffer1,buffer2;
            getline(in,buffer1);// main info except address;
            getline(in,buffer2);//address

            all_content += buffer1; all_content += "\n";
            all_content += buffer2; all_content += "\n";

            istringstream is(buffer1);
            is >> last_str_id; 
        }
        in.close();
        int last_num_id = stoi(last_str_id.substr(1,3));
        id = "U" + to_string(last_num_id + 1);
        cout << "Please input your name."<<endl;
        cin >> name;
        cout << "Please input your telephone number."<<endl;
        cin >> tele;
        cout << "Please input your address:"<<endl;
        getline(cin,addr);//cin do not work here; 
        getline(cin,addr);//another getline is a necessity here.
        cout << "Please input your password."<<endl;
        cin >> password1;
        cout << "Please input your password again."<<endl;
        cin >> password2;

        while(password1 != password2)
        {
            cout << "Please check your password and input it correctly."<<endl;
            cin >> password1;
            cout << "Please input your password again."<<endl;
            cin >> password2;
        }

        cout<<"======================================="<<endl;
        cout<<"ID:"<<id<<endl;
        cout<<"Name:"<<name<<endl;
        cout<<"Tele:"<<tele<<endl;
        cout<<"Password:"<<password1<<endl;
        cout<<"Address:"<<addr<<endl;
        cout<<"======================================="<<endl<<endl;

        string to_confirm;
        cout << "Press 'y' to confirm your information, or press any key except 'y' to abort."<<endl;
        cin >> to_confirm;
        if(to_confirm == "y" || to_confirm == "Y")
        {
            all_content += id; all_content += " ";
            all_content += name; all_content += " ";
            all_content += tele; all_content += " ";
            all_content += password1; all_content += " ";
            all_content += "0 ";
            all_content += "ACTIVE\n";
            all_content += addr;
            ofstream out("user_info.txt");
            out.flush();
            out << all_content;
            out.close();

            cout << "You have successfully register a new user."<<endl;
            sleep(1);
        }
        else
        {
            cout << "You have successfully abort this operation."<<endl;
            sleep(1);
        }

    }
}

void User_login()
{

}

void Administrator_main()
{
    while(1)
    {
        cout <<"==========================================="<<endl;
        cout <<"1: Check all the commodities"<<endl;
        cout <<"2: Search for commodities"<<endl;
        cout <<"3: Remove commodities"<<endl;
        cout <<"4: Check all the orders"<<endl;
        cout <<"5: Check all the users"<<endl;
        cout <<"6: Ban users"<<endl;
        cout <<"7: Exit"<<endl;
        cout <<"==========================================="<<endl<<endl;

        string input;
        cout << "Input the number of the operation you want."<<endl<<endl;
        cin >> input;
        if(input == "1")
        {
            p2ad->Check_commodity();
        }
        else if(input == "2")
        {
            p2ad->Search_commodity();
        }
        else if(input == "3")
        {
            p2ad->Remove_commodity();
        }
        else if(input == "4")
        {
            p2ad->Check_order();
        }
        else if(input == "5")
        {
            p2ad->Check_user();
        }
        else if(input == "6")
        {
            p2ad->Ban_user();
        }
        else if(input == "7")
        {
            break;
        }
        else
        {
            cout << "The number you inputed is wrong. Please check it."<<endl<<endl;
            sleep(1);
            system("clear");
        }
    }
}