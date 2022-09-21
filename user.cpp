#include "user.h"
#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
#include <iomanip>

#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

#define is_num(X) (X >= '0' && X <= '9')

#define Out(X,Y);  cout.width(X);cout.flags(ios::left);cout << Y;

bool User::Set_id(string str) 
{
	if(str.length()== 4 && str[0] == 'U' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		user_id = str; 
		return true;
	}
	return false;
}

void User::Set_name(string str) 
{
	user_name = str; 
}

void User::Set_tele(string str) 
{
	user_tele = str; 
}

void User::Set_addr(string str) 
{
	user_addr = str; 
}

void User::Set_password(string str) 
{
	user_password = str; 
}
	
bool User::Set_balance(double balance) 
{
	if(balance >= 0 && ((int)(balance * 100))  % 10 == 0)
	{
		user_balance = balance;
		return true;
	}
	return false;
}

void User::Set_state(UserState us) 
{
	user_state = us; 
}

void User::PrintAll()
{
	cout << "==========================================="<<endl;
	cout << "User ID       : "<< user_id <<endl;
	cout << "User Name     : "<< user_name <<endl;
	cout << "User Tele     : "<< user_tele <<endl;
	cout << "User Address  : "<< user_addr <<endl;
	cout << "User Balance  : "<< user_balance <<endl;
	if(user_state == ACTIVE)
		cout << "User State    : "<< "ACTIVE" <<endl;
	else
		cout << "User State    : "<< "INACTIVE" <<endl;
	cout << "==========================================="<<endl;
}

void User::Seller_release_com()
{
    string id,price,number,name,description,all_content,last_str_id;
    ifstream in("commodity_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description 

            all_content += buffer1; all_content += "\n";
            all_content += buffer2; all_content += "\n";
            all_content += buffer3; all_content += "\n";

            istringstream is(buffer1);
			is >> last_str_id;
        }
        in.close();

        cout << "Input "<<endl;

        int last_num_id = stoi(last_str_id.substr(1,3));
        id = "M" + to_string(last_num_id + 1);

        all_content += id; all_content += " ";
        all_content += price; all_content += " ";
        all_content += number; all_content += " ";
        all_content += user_id; all_content += " ";
        all_content += "ONAUCTION"; all_content += "\n";
        all_content += name; all_content += "\n";
        all_content += description;
    }
}

void User::Seller_check_com()
{
	ifstream in("commodity_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        bool find = false;
        cout<<"================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Added Date  State"<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,id,price,num,seller,addedDate,state;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description 

            istringstream is(buffer1);
			is >> id;is >> price;is >> num;is >> seller;is >> addedDate;is >> state;
			
            if(seller == user_id)
            {
                find = true;
                Out(10,id);
                Out(30,buffer2);//name
                Out(10,price);
                Out(8,num);
                //Out(11,seller);
                Out(12,addedDate);
                Out(12,state);
                cout << endl;
            }   
        }
        cout<<"================================================================================================="<<endl;
        if(find == false)
            cout <<"Fail to find your commodity."<<endl;
        else
            cout <<"Here are all your commodities."<<endl;
        cout<<endl<<endl;
        in.close();
    }
}

void User::Seller_change_com()
{
    ifstream in("commodity_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
    }
    else
    {
        cout << "Enter the ID of the commodity you want to change."<<endl;
        string id;
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
                target[0] = temp;
                for(int i = 0;i < 4;++i)
                {
                    is >> temp;
                    target[i + 1] = temp;
                }
				if(target[3] == user_id)
					find_com = true;
                target[5] = buffer2;
                target[6] = buffer3;
                is >> temp;
                if(temp == "REMOVED")
                    removed_com = true;
            }
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
            cout <<"=========================================================================="<<endl;
            cout <<"ID:          "<<target[0]<<endl;
            cout <<"Price:       "<<target[1]<<endl;
            cout <<"Number:      "<<target[2]<<endl;
            cout <<"Seller ID:   "<<target[3]<<endl;
            cout <<"Added Date:  "<<target[4]<<endl;
            cout <<"Name:        "<<target[5]<<endl;
            cout <<"Description: "<<target[6]<<endl;
            cout <<"=========================================================================="<<endl;
            cout <<"This is your commodity's information."<<endl;
            cout <<"Press '1' to change its price, 2 for description, and 3 for both of them."<<endl;
            string change;
            cin >> change;
            if(change == "1")
            {
                cout << "Input new price."<<endl;
                cin >> target[1];
            }
            else if(change == "2")
            {
                cout << "Input new description."<<endl;
                getline(cin,target[6]);
                getline(cin,target[6]);
            }
            else if(change == "3")
            {
                cout << "Input new price."<<endl;
                cin >> target[1];
                cout << "Input new description."<<endl;
                getline(cin,target[6]);
                getline(cin,target[6]);
            }
            else
            {
                cout << "Wrong number!"<<endl;
            }
            
            string all_content,rw1,rw2,rw3,tar_id;
            ifstream reWrite("commodity_info.txt");

            while (!reWrite.eof() )
            {
                getline(reWrite,rw1);// main info except name and description;
                getline(reWrite,rw2);//name
                getline(reWrite,rw3);//description

                istringstream rw(rw1);

                rw >> tar_id;

                if(tar_id == id)
                {
                    for(int i = 0;i < 4;++i)
                    {
                        all_content += target[i];
                        all_content += " ";
                    }
                    all_content += "ONAUCTION"; all_content += "\n";
                    all_content += target[5]; all_content += "\n";
                    all_content += target[6]; all_content += "\n";
                }
                else
                {
                    all_content += rw1; all_content += "\n";
                    all_content += rw2; all_content += "\n";
                    all_content += rw3; all_content += "\n";
                }
            }
            reWrite.close();
            all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
            
            ofstream out("commodity_info.txt");
            out.flush();
            out << all_content;
            out.close();
            cout << "You have successfully change the information."<<endl;
        }
    }
}

void User::Seller_remove_com()
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
				if(target[3] == user_id)
					find_com = true;
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
            cout <<"=========================================================================="<<endl;
            cout <<"ID:          "<<target[0]<<endl;
            cout <<"Price:       "<<target[1]<<endl;
            cout <<"Number:      "<<target[2]<<endl;
            cout <<"Seller ID:   "<<target[3]<<endl;
            cout <<"Added Date:  "<<target[4]<<endl;
            cout <<"Name:        "<<target[5]<<endl;
            cout <<"Description: "<<target[6]<<endl;
            cout <<"=========================================================================="<<endl;
            cout<<"Do you want to remove this?"<<endl;
            cout<<"Press 'y' to confirm, or it will not be removed."<<endl;
            string confirm_str;
            cin >> confirm_str;
            if(confirm_str == "y" || confirm_str == "Y")
            {
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

void User::Seller_check_order()
{
    ifstream in("order_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        bool find = false;
        cout<<"==========================================================================="<<endl;
        cout <<"Order ID  Com id  Price     Number    Date        Buyer ID"<<endl; 
        while (!in.eof() )
        {
            string buffer,id,com,price,num,date,seller,buyer;
            getline(in,buffer);
            istringstream is(buffer);

            is >> id;is >> com;is >> price;is >> num;is >> date;is >> seller;is >> buyer;
            if(seller == user_id)
            {
                find = true;
                Out(10,id);//Order id
                Out(8,com);//Commodity id
                Out(10,price);//Price
                ;Out(10,num);//Number
                Out(12,date);//Date
                //Out(11,seller);//Seller ID
                Out(10,buyer);//Buyer ID
                cout << endl;
            }
        }
        cout<<"==========================================================================="<<endl;
        if(find == false)
            cout << "Fail to find your order."<<endl;
        cout<<endl<<endl;
    }
    in.close();
}

void User::Buyer_check_com()
{
    ifstream in("commodity_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        bool find = false;
        cout<<"================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Seller ID  Added Date  State"<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,id,price,num,seller,addedDate,state;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description 

            istringstream is(buffer1);
			is >> id;is >> price;is >> num;is >> seller;is >> addedDate;is >> state;
			
            if(state == "ONAUCTION")
            {
                find = true;
                Out(10,id);
                Out(30,buffer2);//name
                Out(10,price);
                Out(8,num);
                Out(11,seller);
                Out(12,addedDate);
                Out(12,state);
                cout << endl;
            }   
        }
        cout<<"================================================================================================="<<endl;
        if(find == false)
            cout <<"Fail to find commodity on auction."<<endl;
        else
            cout <<"Here are all the commodities on auction."<<endl;
        cout<<endl<<endl;
        in.close();
    }
}

void User::Buyer_check_order()
{
    ifstream in("order_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        bool find = false;
        cout<<"==========================================================================="<<endl;
        cout <<"Order ID  Com id  Price     Number    Date        Seller ID  "<<endl; 
        while (!in.eof() )
        {
            string buffer,id,com,price,num,date,seller,buyer;
            getline(in,buffer);
            istringstream is(buffer);

            is >> id;is >> com;is >> price;is >> num;is >> date;is >> seller;is >> buyer;
            if(buyer == user_id)
            {
                find = true;
                Out(10,id);//Order id
                Out(8,com);//Commodity id
                Out(10,price);//Price
                ;Out(10,num);//Number
                Out(12,date);//Date
                Out(11,seller);//Seller ID
                //Out(10,buyer);//Buyer ID
                cout << endl;
            }
        }
        cout<<"==========================================================================="<<endl;
        if(find == false)
            cout << "Fail to find your order."<<endl;
        cout<<endl<<endl;
    }
    in.close();
}

void User::Buyer_search_com()
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
        cout<<"================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Seller ID  Added Date"<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,id,price,num,seller,date,state;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description 

            istringstream is(buffer1);
            is >> id;is >> price;is >> num;is >> seller;is >> date;is >> state;
            if(strstr(buffer2.c_str(),target.c_str()) != NULL && state == "ONAUCTION")
            {
                find = true;
                
                Out(10,id);//id
                Out(30,buffer2); //name 
                Out(10,price);//price
                Out(8,num);//number
                Out(11,seller);//seller id
                Out(12,date);//date
                //Out(12,state);//state
                cout << endl;
            }   
        }
        cout<<"================================================================================================="<<endl;
        if(find == false)
            cout<<"Fail to find the commodity you want. Please check the name."<<endl;
        else
            cout <<"Here are all the commodities on auction that match the name you gave."<<endl;
        cout<<endl<<endl;
        in.close();
    }
}

void User::Buyer_buy_com()
{
    //TO DO
}