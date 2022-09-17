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
        cout<<"================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Seller ID  Added Date  State"<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,temp;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name

            istringstream is(buffer1);

            is >> temp;Out(10,temp);//id
            Out(30,buffer2); //name 
            is >> temp;Out(10,temp);//price
            is >> temp;Out(8,temp);//number
            is >> temp;Out(11,temp);//seller id
            is >> temp;Out(12,temp);//date
            is >> temp;Out(12,temp);//state
            cout << endl;
            
            getline (in,buffer1);
            //description need to be read in order to move the pionter of file, without printed;
        }
        cout<<"================================================================================================="<<endl;
        cout<<endl<<endl;
    }
}

void Admin::Search_commodity()
{

}

void Admin::Remove_commodity()
{

}

void Admin::Check_order()
{
    ifstream in("order_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        cout<<"==========================================================================="<<endl;
        cout <<"Order ID  Com id  Price     Number    Date        Seller ID  Buyer ID"<<endl; 
        while (!in.eof() )
        {
            string buffer,temp;
            getline(in,buffer);
            istringstream is(buffer);

            is >> temp;Out(10,temp);//Order id
            is >> temp;Out(8,temp);//Commodity id
            is >> temp;Out(10,temp);//Price
            is >> temp;Out(10,temp);//Number
            is >> temp;Out(12,temp);//Date
            is >> temp;Out(11,temp);//Seller ID
            is >> temp;Out(10,temp);//Buyer ID
            cout << endl;
        }
        cout<<"==========================================================================="<<endl;
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
        cout<<"============================================================================================================="<<endl;
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
        cout<<"============================================================================================================="<<endl;
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
        int line_count = 0;
        while (!in.eof() )
        {
            string buffer1,buffer2,temp;
            getline(in,buffer1);// main info except address;
            getline(in,buffer2);//address

            istringstream is(buffer1);

            is >> temp;//id
            if(temp == id)
            {
                find_user = true;
                all_content += temp;
                all_content += " ";
                for(int i = 0;i < 4;++i)
                {
                    is >> temp;
                    all_content += temp;
                    all_content += " ";
                }
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
            ofstream out("user_info.txt");
            out.flush();
            out << all_content;
            out.close();
            cout << "You have successfully banned the user you wanted."<<endl;
        }
    }
}
