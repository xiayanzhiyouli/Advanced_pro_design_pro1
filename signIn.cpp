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
#include "user.h"

using namespace std;

void Administrator_login();
void Administrator_main();
void User_register();
void User_login();
void User_main();
void Buyer_main();
void Seller_main();
void Personal_information();
void Personal_recharge();
void Personal_change();


Admin* p2ad = new Admin;
User* p2us = new User;

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
    string log_id,log_password;
    cout << "Please input your user ID."<<endl;
    cin >> log_id;
    cout << "Please input your password."<<endl;
    cin >> log_password;

    string id,name,tele,password,balance,state,addr;

    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
    }
    else
    {
        bool find_user = false;
        while (!in.eof() )
        {
            string buffer1,buffer2;
            getline(in,buffer1);// main info except address;
            getline(in,buffer2);//address

            istringstream is(buffer1);
            is >> id; 
            if(id == log_id)
            {
                find_user = true;
                is >> name; is >> tele; is >> password; is >> balance; is >> state; 
                addr = buffer2;
                break;
            }      
        }
        in.close();
        if(find_user == false)
        {
            cout << "Fail to find your ID!"<<endl;
            sleep(1);
        }
        else if(password != log_password)
        {
            cout << "Wrong password!"<<endl;
            sleep(1);
        }
        else if(state != "ACTIVE")
        {
            cout << "You have been banned!"<<endl;
            sleep(1);
        }
        else
        {
            p2us->Set_id(id);
            p2us->Set_name(name);
            p2us->Set_tele(tele);
            p2us->Set_password(password);
            p2us->Set_balance(stod(balance));
            p2us->Set_addr(addr);
            cout << "Login successfully!"<<endl;
            sleep(1);
            User_main();
        }

    }
}

void User_main()
{
    while(1)
    {
        system("clear");
        cout <<"======================"<<endl;
        cout <<"1 :I am a buyer."<<endl;
        cout <<"2 :I am a seller."<<endl;
        cout <<"3 :Personal information."<<endl;
        cout <<"4 :Exit."<<endl;
        cout <<"======================"<<endl;
        string input;
        cout << "Input the number you want."<<endl;
        cin >> input;
        if(input == "1")
        {
            Buyer_main();
        }
        else if(input == "2")
        {
            Seller_main();
        }
        else if(input == "3")
        {
            Personal_information();
        }
        else if(input == "4")
        {
            break;
        }
        else 
        {
            cout << "Wrong number!"<<endl;
            sleep(1);
        }
    }
}

void Buyer_main()
{
    while(1)
    {
        system("clear");
        cout <<"=============================="<<endl;
        cout <<"1 :Check all the commodities."<<endl;
        cout <<"2 :Buy the commodities."<<endl;
        cout <<"3 :Search for commodities."<<endl;
        cout <<"4 :Check my order."<<endl;
        cout <<"5 :Check commodity's detailed information."<<endl;
        cout <<"6 :Exit."<<endl;
        cout <<"=============================="<<endl;
        string input;
        cout <<"Input the number you want."<<endl;
        cin >> input;
        if(input == "1")
        {
            p2us->Buyer_check_com();
        }
        else if(input == "2")
        {
            p2us->Buyer_buy_com();
        }
        else if(input == "3")
        {
            p2us->Buyer_search_com();
        }
        else if(input == "4")
        {
            p2us->Buyer_check_order();
        }
        else if(input == "5")
        {
            //TO DO
        }
        else if(input == "6")
        {
            break;
        }
        else 
        {
            cout <<"Wrong number!"<<endl;
            sleep(1);
        }
    }
}

void Seller_main()
{
    while(1)
    {
        system("clear");
        cout <<"=============================="<<endl;
        cout <<"1 :Release commodities."<<endl;
        cout <<"2 :Check the commodities."<<endl;
        cout <<"3 :Change commodities's information."<<endl;
        cout <<"4 :Remove commodity."<<endl;
        cout <<"5 :Check my order."<<endl;
        cout <<"6 :Exit."<<endl;
        cout <<"=============================="<<endl;
        string input;
        cout <<"Input the number you want."<<endl;
        cin >> input;
        if(input == "1")
        {
            p2us->Seller_release_com();
        }
        else if(input == "2")
        {
            p2us->Seller_check_com();
        }
        else if(input == "3")
        {
            p2us->Seller_change_com();
        }
        else if(input == "4")
        {
            p2us->Seller_remove_com();
        }
        else if(input == "5")
        {
            p2us->Seller_check_order();
        }
        else if(input == "6")
        {
            break;
        }
        else 
        {
            cout <<"Wrong number!"<<endl;
            sleep(1);
        }
    }
}

void Personal_information()
{
    while(1)
    {
        system("clear");
        cout <<"======================="<<endl;
        cout <<"1 :Check personal information."<<endl;
        cout <<"2 :Chage personal information."<<endl;
        cout <<"3 :Recharge."<<endl;
        cout <<"4 :Exit."<<endl;
        cout <<"======================="<<endl;
        string input;
        cout << "Input the number you want"<<endl;
        cin >>input;

        if(input == "1")
        {
            p2us->PrintAll();
            cout <<"Press any key to back."<<endl;
            string any_key;
            cin >> any_key;
        }
        else if(input == "2")
        {
            Personal_change();
        }
        else if(input == "3")
        {
            Personal_recharge();
        }
        else if(input == "4")
        {
            break;
        }
        else 
        {
            cout <<"Wrong number!"<<endl;
            sleep(1);
        }
    }
}

void Personal_change()
{
    while(1)
    {
        system("clear");
        p2us->PrintAll();
        cout << endl;
        cout <<"1: Change user's name."<<endl;
        cout <<"2: Change user's tele."<<endl;
        cout <<"3: Change user's password."<<endl;
        cout <<"4: Change user's address."<<endl;
        cout <<"5: Exit."<<endl;
        cout<<"Input the number you want"<<endl;
        string input,all_content;
        bool success = true;
        cin >> input;
        if(input == "1")
        {
            cout <<"Please input your new name."<<endl;
            string temp;
            cin >> temp;
            p2us->Set_name(temp);
        }
        else if(input == "2")
        {
            cout <<"Please input your new tele."<<endl;
            string temp;
            cin >> temp;
            p2us->Set_tele(temp);
        }
        else if(input == "3")
        {
            cout <<"Please input your old password."<<endl;
            string temp;
            cin >> temp;
            if(temp == p2us->Get_password())
            {
                cout <<"Please input your new password."<<endl;
                cin >> temp;
                p2us->Set_password(temp);
            }
            else
            {
                success = false;
                cout << "Wrong password!"<<endl;
            }
            
        }
        else if(input == "4")
        {
            cout <<"Please input your new address."<<endl;
            string temp;
            getline(cin,temp);
            getline(cin,temp);
            p2us->Set_addr(temp);
        }
        else if(input == "5")
        {
            break;
        }
        else 
        {
            success = false;
            cout <<"Wrong number!"<<endl;
        }

        if(success == false)
            sleep(1);
        else
        {
            cout <<"You have change your personal information successfully."<<endl;
            sleep(1);

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
                    string buffer1,buffer2,temp;
                    getline(in,buffer1);// main info except address;
                    getline(in,buffer2);//address

                    istringstream is(buffer1);

                    is >> temp;//id
                    if(temp == p2us->Get_id())
                    {
                        all_content += p2us->Get_id();all_content += " ";
                        all_content += p2us->Get_name();all_content += " ";
                        all_content += p2us->Get_tele();all_content += " ";
                        all_content += p2us->Get_password();all_content += " ";
                        string long_balance = to_string(p2us->Get_balance());
                        all_content += long_balance.substr(0,long_balance.length() - 5);all_content += " ";
                        all_content += "ACTIVE";all_content += '\n';
                    }
                    else
                    {
                        all_content += buffer1;
                        all_content += '\n';
                    }
                    all_content += buffer2;
                    all_content += '\n';
                }
            
                in.close();

                all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
                ofstream out("user_info.txt");
                out.flush();
                out << all_content;
                out.close();
            }
        }     
    }   
}

void Personal_recharge()
{
    cout << "Please input the amount of money."<<endl;
    double charge;
    cin >> charge;
    p2us->Set_balance(p2us->Get_balance() + charge);
    cout <<"Charge successfully!"<<endl;
    cout <<"Your balance is :"<<p2us->Get_balance()<<endl;

    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
    }
    else
    {
        string all_content;
        while (!in.eof() )
        {
            string buffer1,buffer2,temp;
            getline(in,buffer1);// main info except address;
            getline(in,buffer2);//address

            istringstream is(buffer1);

            is >> temp;//id
            if(temp == p2us->Get_id())
            {
                all_content += temp;all_content += " ";
                is >> temp;all_content += temp;all_content += " ";
                is >> temp;all_content += temp;all_content += " ";
                is >> temp;all_content += temp;all_content += " ";
                string long_balance = to_string(p2us->Get_balance());
                all_content += long_balance.substr(0,long_balance.length() - 5);all_content += " ";
                all_content += "ACTIVE";all_content += '\n';
            }
            else
            {
                all_content += buffer1;
                all_content += '\n';
            }
            all_content += buffer2;
            all_content += '\n';
        }
       
        in.close();

        all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
        ofstream out("user_info.txt");
        out.flush();
        out << all_content;
        out.close();
    }
    sleep(1);
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