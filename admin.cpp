#include "user.h"
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

#define Out(X,Y);  cout.width(X);cout.flags(ios::left);cout << Y;

void Admin::Check_commodity()
{
    ifstream in("commodity_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        cout<<"======================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Seller ID  Added Date           State"<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,temp;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);
            //description need to be read in order to move the pionter of file, without printed;
            istringstream is(buffer1);

            is >> temp;Out(10,temp);//id
            Out(30,buffer2); //name 
            is >> temp;Out(10,temp);//price
            is >> temp;Out(8,temp);//number
            is >> temp;Out(11,temp);//seller id
            is >> temp;Out(21,temp);//date
            is >> temp;Out(12,temp);//state
            cout << endl;  
        }
        cout<<"======================================================================================================="<<endl;
        cout<<endl<<endl;
        in.close();
    }
}

void Admin::Search_commodity()
{
    ifstream in("commodity_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        string target;
        bool find = false;
        cout << "Input the name of the commodity you want."<<endl;
        cin >> target;
        cout<<"======================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Seller ID  Added Date           State"<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,temp;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description 

            if(strstr(buffer2.c_str(),target.c_str()) != NULL)
            {
                find = true;
                istringstream is(buffer1);

                is >> temp;Out(10,temp);//id
                Out(30,buffer2); //name 
                is >> temp;Out(10,temp);//price
                is >> temp;Out(8,temp);//number
                is >> temp;Out(11,temp);//seller id
                is >> temp;Out(21,temp);//date
                is >> temp;Out(12,temp);//state
                cout << endl;
            }   
        }
        cout<<"======================================================================================================="<<endl;
        if(find == false)
            cout<<"Fail to find the commodity you want. Please check the name."<<endl;
        else
            cout <<"Here are all the commodities that match the name you gave."<<endl;
        cout<<endl<<endl;
        in.close();
    }
}

void Admin::Remove_commodity()
{
    ifstream in("commodity_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
    }
    else
    {
        cout << "Enter the ID of the commodity you want to remove."<<endl;
        string id,all_content;
        string target[7];
        bool find_com = false,removed_com = false;
        cin >> id;

        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,temp;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description

            istringstream is(buffer1);

            is >> temp;//id
            if(temp == id)
            {
                find_com = true;
                target[0] = temp;
                all_content += temp;
                all_content += " ";
                for(int i = 0;i < 4;++i)
                {
                    is >> temp;
                    target[i + 1] = temp;
                    all_content += temp;
                    all_content += " ";
                }
                target[5] = buffer2;
                target[6] = buffer3;
                is >> temp;
                if(temp == "REMOVED")
                    removed_com = true;
                all_content += "REMOVED";
                all_content += '\n';
            }
            else
            {
                all_content += buffer1;
                all_content += '\n';
            }
            all_content += buffer2;
            all_content += '\n';
            all_content += buffer3;
            all_content += '\n';
        }
        if(find_com == false)
        {
            cout << "Can not find this commodity! Please check commodity's ID."<<endl;
            in.close();
        }
        else if(removed_com == true)
        {
            cout << "This commodity has been removed! Please check commodity's ID."<<endl;
            in.close();
        }
        else
        {
            in.close();
            cout <<"================================================================================"<<endl;
            cout <<"ID:          "<<target[0]<<endl;
            cout <<"Price:       "<<target[1]<<endl;
            cout <<"Number:      "<<target[2]<<endl;
            cout <<"Seller ID:   "<<target[3]<<endl;
            cout <<"Added Date:  "<<target[4]<<endl;
            cout <<"Name:        "<<target[5]<<endl;
            cout <<"Description: "<<target[6]<<endl;
            cout <<"================================================================================"<<endl;
            cout<<"Do you want to remove this?"<<endl;
            cout<<"Press 'y' to confirm, or it will not be removed."<<endl;
            string confirm_str;
            cin >> confirm_str;
            if(confirm_str == "y" || confirm_str == "Y")
            {
                all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
                ofstream out("commodity_info.txt");
                out.flush();
                out << all_content;
                out.close();
                cout << "You have successfully removed the commodity you wanted."<<endl;
            }
            else
                cout << "You have deleted this removing operation."<<endl;
        }
    }
}

void Admin::Check_order()
{
    ifstream in("order_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        cout<<"================================================================================="<<endl;
        cout <<"Order ID  Com id  Price     Number    Date                 Seller ID  Buyer ID"<<endl; 
        while (!in.eof() )
        {
            string buffer,temp;
            getline(in,buffer);
            istringstream is(buffer);

            is >> temp;Out(10,temp);//Order id
            is >> temp;Out(8,temp);//Commodity id
            is >> temp;Out(10,temp);//Price
            is >> temp;Out(10,temp);//Number
            is >> temp;Out(21,temp);//Date
            is >> temp;Out(11,temp);//Seller ID
            is >> temp;Out(10,temp);//Buyer ID
            cout << endl;
        }
        cout<<"================================================================================="<<endl;
        cout<<endl<<endl;
    }
    in.close();
}

void Admin::Check_user()
{
    ifstream in("user_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        cout<<"==================================================================================================================="<<endl;
        cout <<"ID    Name        Tele                  Passport              Balance     State     Address"<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,temp;
            getline(in,buffer1);// main info except address;
            getline(in,buffer2);//address

            istringstream is(buffer1);

            is >> temp;Out(6,temp);//id 
            is >> temp;Out(12,temp);//name
            is >> temp;Out(22,temp);//tele
            is >> temp;Out(22,temp);//passport
            is >> temp;Out(12,temp);//balance
            is >> temp;Out(10,temp);//state
            Out(40,buffer2); //name
            cout << endl;
        }
        cout<<"==================================================================================================================="<<endl;
        cout<<endl<<endl;
    }
    in.close();
}

void Admin::Ban_user()
{
    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
    }
    else
    {
        cout << "Enter the ID of the user you want to ban."<<endl;
        string id,all_content;
        bool find_user = false,inact_user = false;
        cin >> id;

        string target[6];
        while (!in.eof() )
        {
            string buffer1,buffer2,temp;
            getline(in,buffer1);// main info except address;
            getline(in,buffer2);//address

            istringstream is(buffer1);

            is >> temp;//id
            if(temp == id)
            {
                target[0] = temp;
                find_user = true;
                all_content += temp;
                all_content += " ";
                for(int i = 0;i < 4;++i)
                {
                    is >> temp;
                    target[i + 1] = temp;
                    all_content += temp;
                    all_content += " ";
                }
                target[5] = buffer2;
                is >> temp;
                if(temp == "INACTIVE")
                    inact_user = true;
                all_content += "INACTIVE";
                all_content += '\n';
            }
            else
            {
                all_content += buffer1;
                all_content += '\n';
            }
            all_content += buffer2;
            all_content += '\n';
        }
        if(find_user == false)
        {
            cout << "Can not find this user! Please check user's ID."<<endl;
            in.close();
        }
        else if(inact_user == true)
        {
            cout << "This user has been banned! Please check user's ID."<<endl;
            in.close();
        }
        else
        {
            in.close();
            cout <<"================================================================="<<endl;
            cout << "ID      :"<<target[0]<<endl;
            cout << "Name    :"<<target[1]<<endl;
            cout << "Tele    :"<<target[2]<<endl;
            cout << "Balance :"<<target[4]<<endl;
            cout << "Address :"<<target[5]<<endl;
            cout <<"================================================================="<<endl;
            cout<<"Do you want to ban this user?"<<endl;
            cout<<"Press 'y' to confirm, or he/she will not be banned."<<endl;
            string confirm_str;
            cin >> confirm_str;
            if(confirm_str == "y" || confirm_str == "Y")
            {
                all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
                ofstream out("user_info.txt");
                out.flush();
                out << all_content;
                out.close();
                cout << "You have successfully banned the user you wanted."<<endl;
            }
            else
                cout << "You have deleted this banning operation."<<endl;
        }
    }
}
