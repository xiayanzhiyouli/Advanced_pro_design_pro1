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
#include "signIn.h"
#include "refresh.h"

using namespace std;



extern Admin* p2ad;
extern User* p2us;

void signin()
{
    cout << "  Commodity Trading Plattform  "<<endl;
    cout << "  Xia Yan 201220077 NJUCS"<<endl;
    cout << endl<<endl;
    my_RefreshIntention();
    sleep(1);
}

void main_platform()
{
    while(1)
    {
        system("clear");
        my_RefreshIntention();
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
        return;
    }

    while (!in.eof() )
    {
        string buffer1,buffer2;
        getline(in,buffer1);// main info except address;
        if(buffer1.length() == 0)
        {
            last_str_id = "None";
            break;
        }
        getline(in,buffer2);//address

        all_content += buffer1; all_content += "\n";
        all_content += buffer2; all_content += "\n";

        istringstream is(buffer1);
        is >> last_str_id; 
    }
    in.close();

    if(last_str_id == "None")
        id = "U001";
    else
    {
        int last_num_id = stoi(last_str_id.substr(1,3));
        id = "U" + to_string(last_num_id + 1);
    }

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
        return;
    }

    cout << "You have successfully abort this operation."<<endl;
    sleep(1);
    return;  
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
        return;
    }

    bool find_user = false;
    while (!in.eof() )
    {
        string buffer1,buffer2;
        getline(in,buffer1);// main info except address;
        if(buffer1.length() == 0)
        {
            cout<<endl;
            cout << "No User!"<<endl<<endl;
            sleep(1);
            in.close();
            return;
        }
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
        return;
    }

    if(password != log_password)
    {
        cout << "Wrong password!"<<endl;
        sleep(1);
        return;
    }
    
    if(state != "ACTIVE")
    {
        cout << "You have been banned!"<<endl;
        sleep(1);
        return;
    }

    p2us->Set_id(id);
    p2us->Set_name(name);
    p2us->Set_tele(tele);
    p2us->Set_password(password);
    p2us->Set_balance(stod(balance));
    p2us->Set_addr(addr);
    cout << "Login successfully!"<<endl;
    sleep(1);
    User_main();

    return;
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
    string buffer;
    while(1)
    {
        system("clear");
        cout <<"=============================="<<endl;
        cout <<"1 :Check all the commodities."<<endl;
        cout <<"2 :Buy the commodities."<<endl;
        cout <<"3 :Search for commodities."<<endl;
        cout <<"4 :Check my order."<<endl;
        cout <<"5 :Check commodity's detailed information."<<endl;
        cout <<"6 :Cancel purchase intention."<<endl;
        cout <<"7 :Change purchase intention."<<endl;
        cout <<"8 :Write comments."<<endl;
        cout <<"9 :Exit."<<endl;
        cout <<"=============================="<<endl;
        string input;
        cout <<"Input the number you want."<<endl;
        cin >> input;
        my_RefreshIntention();
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
            p2us->Buyer_check_com_detailed();        
        }
        else if(input == "6")
        {
            p2us->Buyer_cancel_intention();        
        }
        else if(input == "7")
        {
            p2us->Buyer_change_intention();        
        }
        else if(input == "8")
        {
            p2us->Buyer_write_comment();        
        }
        else if(input == "9")
        {
            break;
        }
        else 
        {
            cout <<"Wrong number!"<<endl;
        }
        cout <<"Input any key to continue."<<endl;
        cin >> buffer;
    }
}

void Seller_main()
{
    string buffer;
    while(1)
    {
        system("clear");
        cout <<"=============================="<<endl;
        cout <<"1 :Release commodities."<<endl;
        cout <<"2 :Check the commodities."<<endl;
        cout <<"3 :Change commodities's information."<<endl;
        cout <<"4 :Remove commodity."<<endl;
        cout <<"5 :Check my order."<<endl;
        cout <<"6 :Check commodity's comments."<<endl;
        cout <<"7 :Exit."<<endl;
        cout <<"=============================="<<endl;
        string input;
        cout <<"Input the number you want."<<endl;
        cin >> input;
        my_RefreshIntention();
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
            p2us->Seller_check_comment();
        }
        else if(input == "7")
        {
            break;
        }
        else 
        {
            cout <<"Wrong number!"<<endl;
        }
        cout <<"Input any key to continue."<<endl;
        cin >> buffer;
    }
}

void Personal_information()
{
    string buffer;
    while(1)
    {
        system("clear");
        cout <<"======================="<<endl;
        cout <<"1 :Check personal information."<<endl;
        cout <<"2 :Change personal information."<<endl;
        cout <<"3 :Recharge."<<endl;
        cout <<"4 :Exit."<<endl;
        cout <<"======================="<<endl;
        string input;
        cout << "Input the number you want"<<endl;
        cin >>input;
        my_RefreshIntention();
        if(input == "1")
        {
            p2us->PrintAll();
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
        }
        cout <<"Input any key to continue."<<endl;
        cin >> buffer;
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
        my_RefreshIntention();
        string tempName,tempTele,tempPassword,tempAddr;
        tempName = p2us->Get_name();
        tempTele = p2us->Get_tele();
        tempPassword = p2us->Get_password();
        tempAddr = p2us->Get_addr();
        if(input == "1")
        {
            cout <<"Please input your new name."<<endl;
            string temp;
            cin >> temp;
            tempName = temp;
        }
        else if(input == "2")
        {
            cout <<"Please input your new tele."<<endl;
            string temp;
            cin >> temp;
            tempTele = temp;
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
                tempPassword = temp;
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
            tempAddr = temp;
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
                    if(buffer1.length() == 0)
                    {
                        cout<<endl;
                        cout << "No User!"<<endl<<endl;
                        sleep(1);
                        return;
                    }
                    getline(in,buffer2);//address

                    istringstream is(buffer1);

                    is >> temp;//id
                    if(temp == p2us->Get_id())
                    {
                        all_content += p2us->Get_id();all_content += " ";
                        all_content += tempName;all_content += " ";
                        all_content += tempTele;all_content += " ";
                        all_content += tempPassword;all_content += " ";
                        string long_balance = to_string(p2us->Get_balance());
                        all_content += long_balance.substr(0,long_balance.length() - 5);all_content += " ";
                        all_content += "ACTIVE";all_content += '\n';
                        all_content += tempAddr;all_content += '\n';
                    }
                    else
                    {
                        all_content += buffer1;
                        all_content += '\n';
                        all_content += buffer2;
                        all_content += '\n';
                    }
                }
            
                in.close();

                all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
                                
                cout <<"Do you really want to do this?"<<endl;
                string to_comfirm;
                cout <<"Press y to comfirm, otherwise to cancel."<<endl;
                cin >> to_comfirm;
                if(to_comfirm != "Y" && to_comfirm != "y")
                {
                    cout <<"You have cancelled it!"<<endl;
                    return;
                }
                ofstream out("user_info.txt");
                out.flush();
                out << all_content;
                out.close();
                p2us->Set_name(tempName);
                p2us->Set_tele(tempTele);
                p2us->Set_password(tempPassword);
                p2us->Set_addr(tempAddr);
                cout <<"You have change your personal information successfully."<<endl;
                sleep(1);
            }
        }     
    }   
}

void Personal_recharge()
{
    cout << "Please input the amount of money."<<endl;
    double charge;
    cin >> charge;
    if(charge <= 0)
    {
        cout <<"It must be bigger than 0!"<<endl;
        return;
    }
    my_RefreshIntention();

    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }

    string all_content;
    while (!in.eof() )
    {
        string buffer1,buffer2,temp;
        getline(in,buffer1);// main info except address;
        if(buffer1.length() == 0)
        {
            cout<<endl;
            cout << "No User!"<<endl<<endl;
            in.close();
            sleep(1);
            return;
        }
        getline(in,buffer2);//address

        istringstream is(buffer1);

        is >> temp;//id
        if(temp == p2us->Get_id())
        {
            all_content += temp;all_content += " ";
            is >> temp;all_content += temp;all_content += " ";
            is >> temp;all_content += temp;all_content += " ";
            is >> temp;all_content += temp;all_content += " ";
            string long_balance = to_string(p2us->Get_balance() + charge);
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

    cout <<"Do you really want to do this?"<<endl;
    string to_comfirm;
    cout <<"Press y to comfirm, otherwise to cancel."<<endl;
    cin >> to_comfirm;
    if(to_comfirm != "Y" && to_comfirm != "y")
    {
        cout <<"You have cancelled it!"<<endl;
        return;
    }

    ofstream out("user_info.txt");
    out.flush();
    out << all_content;
    out.close();
    
    p2us->Set_balance(p2us->Get_balance() + charge);
    cout <<"Charge successfully!"<<endl;
    cout <<"Your balance is :"<<p2us->Get_balance()<<endl;
    sleep(1);
}

void Administrator_main()
{
    string buffer;
    while(1)
    {
        system("clear");
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
        my_RefreshIntention();
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
        }
        cout <<"Input any key to continue."<<endl;
        cin >> buffer;
    }
}