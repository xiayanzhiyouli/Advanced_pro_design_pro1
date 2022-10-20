#include "user.h"
#include "time.h"
#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
#include <iomanip>

#include <fstream>
#include <cstdlib>
#include <sstream>

#include <unistd.h>

#include "refresh.h"

using namespace std;

#define is_num(X) (X >= '0' && X <= '9')

#define Out(X,Y);  cout.width(X);cout.flags(ios::left);cout << Y;

extern Time* p2te;
extern User* p2us;

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
	cout << "================================================="<<endl;
	cout << "User ID       : "<< user_id <<endl;
	cout << "User Name     : "<< user_name <<endl;
	cout << "User Tele     : "<< user_tele <<endl;
	cout << "User Address  : "<< user_addr <<endl;
	cout << "User Balance  : "<< user_balance <<endl;
	if(user_state == ACTIVE)
		cout << "User State    : "<< "ACTIVE" <<endl;
	else
		cout << "User State    : "<< "INACTIVE" <<endl;
	cout << "================================================="<<endl;
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
        id = to_string(last_num_id + 1);

        if(id.length() == 3)
            id = "M" + id;
        if(id.length() == 2)
            id = "M0" + id;
        if(id.length() == 1)
            id = "M00" + id;
        

        cout << "Please input your commodity's name."<<endl;
        getline(cin,name);
        getline(cin,name);
        cout << "Please input your commodity's description."<<endl;
        //getline(cin,description);
        getline(cin,description);
        cout << "Please input your commodity's price."<<endl;
        cin >> price;
        cout << "Please input your commodity's number."<<endl;
        cin >> number;
        all_content += id; all_content += " ";
        all_content += price; all_content += " ";
        all_content += number; all_content += " ";
        all_content += user_id; all_content += " ";
        p2te->Reset();
        all_content += p2te->GetStrAll(); all_content += " ";
        all_content += "ONAUCTION"; all_content += "\n";
        all_content += name; all_content += "\n";
        all_content += description;

        cout <<"Do you really want to do this?"<<endl;
        string to_comfirm;
        cout <<"Input y to confirm, otherwise to cancel."<<endl;
        cin >> to_comfirm;
        if(to_comfirm != "Y" && to_comfirm != "y")
        {
            cout <<"You have cancelled it."<<endl;
            return;
        }
        ofstream out("commodity_info.txt");
        out.flush();
        out << all_content;
        out.close();
        cout << "You have successfully release the commodity."<<endl;
        sleep(1);
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
        cout<<"======================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Added Date           State"<<endl;
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
                Out(21,addedDate);
                Out(12,state);
                cout << endl;
            }   
        }
        cout<<"======================================================================================================="<<endl;
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
            cout <<"================================================================================"<<endl;
            cout <<"ID:          "<<target[0]<<endl;
            cout <<"Price:       "<<target[1]<<endl;
            cout <<"Number:      "<<target[2]<<endl;
            cout <<"Seller ID:   "<<target[3]<<endl;
            cout <<"Added Date:  "<<target[4]<<endl;
            cout <<"Name:        "<<target[5]<<endl;
            cout <<"Description: "<<target[6]<<endl;
            cout <<"================================================================================"<<endl;
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
                    for(int i = 0;i < 5;++i)
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
            
            cout <<"Do you really want to do this?"<<endl;
            string to_comfirm;
            cout <<"Input y to confirm, otherwise to cancel."<<endl;
            cin >> to_comfirm;
            if(to_comfirm != "Y" && to_comfirm != "y")
            {
                cout <<"You have cancelled it."<<endl;
                return;
            }
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
        cout<<"================================================================================="<<endl;
        cout <<"Order ID  Com id  Price     Number    Date                 Buyer ID"<<endl; 
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
                Out(21,date);//Date
                //Out(11,seller);//Seller ID
                Out(10,buyer);//Buyer ID
                cout << endl;
            }
        }
        cout<<"================================================================================="<<endl;
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
        cout<<"======================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Seller ID  Added Date           State"<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,id,price,num,seller,addedDate,state;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description 

            istringstream is(buffer1);
			is >> id;is >> price;is >> num;is >> seller;is >> addedDate;is >> state;
			
            p2te->Reset();
            if(state == "ONAUCTION" && !my_JudgeExpire(addedDate,p2te->GetStrAll()))
            {
                find = true;
                Out(10,id);
                Out(30,buffer2);//name
                Out(10,price);
                Out(8,num);
                Out(11,seller);
                Out(21,addedDate);
                Out(12,state);
                cout << endl;
            }   
        }
        cout<<"======================================================================================================="<<endl;
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
        cout<<"================================================================================="<<endl;
        cout <<"Order ID  Com id  Price     Number    Date                 Seller ID  "<<endl; 
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
                Out(21,date);//Date
                Out(11,seller);//Seller ID
                //Out(10,buyer);//Buyer ID
                cout << endl;
            }
        }
        cout<<"================================================================================="<<endl;
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
        cout<<"======================================================================================================="<<endl;
        cout <<"Com ID    Name                          Price     Number  Seller ID  Added Date         "<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,id,price,num,seller,date,state;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description 

            istringstream is(buffer1);
            is >> id;is >> price;is >> num;is >> seller;is >> date;is >> state;
            p2te->Reset();
            if(strstr(buffer2.c_str(),target.c_str()) != NULL && state == "ONAUCTION" && !my_JudgeExpire(p2te->GetStrAll(),date))
            {
                find = true;
                
                Out(10,id);//id
                Out(30,buffer2); //name 
                Out(10,price);//price
                Out(8,num);//number
                Out(11,seller);//seller id
                Out(21,date);//date
                //Out(12,state);//state
                cout << endl;
            }   
        }
        cout<<"======================================================================================================="<<endl;
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
    string id,price,num,seller,date,state,name,description;
    string buy_num,buy_price,buy_time;
    cout <<"Input ID of the commodity you want to buy."<<endl;
    cin >> id;
    ifstream in("commodity_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        return;
    }

    bool find = false;
    while (!in.eof() )
    {
        string buffer1,buffer2,buffer3,temp_id,temp_price,temp_num,temp_seller,temp_date,temp_state;
        getline(in,buffer1);// main info except name and description;
        getline(in,buffer2);//name
        getline(in,buffer3);//description 

        istringstream is(buffer1);
        is >> temp_id;is >> temp_price;is >> temp_num;is >> temp_seller;is >> temp_date;is >> temp_state;
        
        if(temp_id == id && temp_state == "ONAUCTION" && p2us->Get_id() != temp_seller)
        {
            find = true;
            id = temp_id;
            price = temp_price;
            num = temp_num;
            seller = temp_seller;
            date = temp_date;
            state = temp_state;
            name = buffer2;
            description = buffer3;
            break;
        }   
    }

    if(find == false)
    {
        cout <<"Fail to find other sellers' commodities on auction."<<endl;
        return;
    }
    
    p2te->Reset();
    buy_time = p2te->GetStrAll();

    if(my_JudgeExpire(date,buy_time))//expired.
    {
        cout << "The commodity you chose is expired now."<<endl;
        return;
    }

    cout <<"=========================================="<<endl;
    cout <<"ID:          "<<id<<endl;
    cout <<"Name:        "<<name<<endl;
    cout <<"Price:       "<<price<<endl;
    cout <<"Number:      "<<num<<endl;
    cout <<"Seller ID:   "<<seller<<endl;
    cout <<"Added Date:  "<<date<<endl;
    cout <<"Description: "<<description<<endl;
    cout <<"=========================================="<<endl;
    cout<<endl<<endl;
    in.close();


    cout <<"Input the number you want to buy."<<endl;
    cin >> buy_num;
    if(stoi(buy_num) > stoi(num))
    {
        cout << "You can not buy more commodities than what the seller have."<<endl;
        return;
    }

    cout <<"Input the price you can afford."<<endl;
    cin >> buy_price;

    if(stod(buy_price) < stod(price))
    {
        cout << "Your price must be higher than "<<price<<"."<<endl;
        return;
    }

    if(stoi(buy_num)*stod(buy_price) > p2us->Get_balance())
    {
        cout << "You can not afford them."<<endl;
        return;
    }

    cout <<"Do you really want to do this?"<<endl;
    string to_comfirm;
    cout <<"Press y to comfirm, otherwise to cancel."<<endl;
    cin >> to_comfirm;
    if(to_comfirm != "Y" && to_comfirm != "y")
    {
        cout <<"You have cancelled it!"<<endl;
        return;
    }

    string res,duetimeStr;
    res = id; res += " ";//commodity id
    res += p2us->Get_id(); res += " ";//buyer id
    res += seller; res += " ";//seller id
    res += buy_num; res += " ";
    res += buy_price; res += " ";
    res += buy_time; res += " ";
    res += date;//the date here means the commodity's added date.


    string all_content;
    ifstream temp("intention_info.txt");
    if (!temp.is_open())
    {
        cout << "Error opening file"<<endl; 
        return;
    }

    while (!temp.eof() )
    {
        string buffer;
        getline(temp,buffer);
        all_content += buffer;
        all_content += "\n";
    }
    temp.close();

    if(all_content == "\n")
        all_content = res;//empty file.
    else
        all_content += res;

    ofstream out("intention_info.txt");
    out.flush();
    out << all_content;
    out.close();

    cout << "Success!"<<endl;
    cout << "You will get commodities if there are enough commodities or your price is higher than others."<<endl;
    cout << "You can delete this before the deadline for this trading."<<endl;
}

void User::Buyer_cancel_intention()
{
    string com_id,all_content;
    bool find = false;
    cout<<"Input the commodity number."<<endl;
    cin >> com_id;


    ifstream in("intention_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }


    while (!in.eof() )
    {
        string buffer,com,id;
        getline(in,buffer);

        if(buffer.length() == 0)
        {
            cout<<endl;
            cout <<"You do not have such purchase intention or the trading has been finished."<<endl<<endl;
            in.close();
            return;
        }

        istringstream is(buffer);

        is >> com;
        is >> id;

        if(com == com_id && id == user_id)
            find = true;
        else
        {
            all_content += buffer;
            all_content += "\n";
        }
    }
        
    if(!find)
    {
        cout<<endl;
        cout <<"You do not have such purchase intention or the trading has been finished."<<endl<<endl;
        in.close();
        return;
    }

    in.close();
    cout << "Do you really want to cancel your purchase intention?"<<endl;
    cout << "Input 'y' to confirm, otherwise to stop."<<endl;
    string to_comfirm;
    cin >> to_comfirm;
    if(to_comfirm == "Y" || to_comfirm == "y")
    {
        all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
        ofstream out("intention_info.txt");
        out.flush();
        out << all_content;
        out.close();

        cout <<"You have cancelled your purchase intention."<<endl;
    }
    else
        cout << "You have stopped the cancelling operation."<<endl;
}

void User::Buyer_change_intention()
{
    string target_id,com_id,buyer,seller,num,price,buy_time,added_time,all_content;
    bool find = false;
    cout<<"Input the commodity number."<<endl;
    cin >> target_id;


    ifstream in("intention_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }


    while (!in.eof() )
    {
        string buffer;
        getline(in,buffer);

        if(buffer.length() == 0)
        {
            cout<<endl;
            cout <<"You do not have such purchase intention or the trading has been finished."<<endl<<endl;
            in.close();
            return;
        }

        istringstream is(buffer);

        is >> com_id; is >> buyer; is >> seller; is >> num;
        is >> price; is >> buy_time; is >> added_time;

        if(target_id == com_id && buyer == user_id)
        {
            find = true;
            break;
        }
    }
        
    if(!find)
    {
        cout<<endl;
        cout <<"You do not have such purchase intention or the trading has been finished."<<endl<<endl;
        in.close();
        return;
    }

    in.close();

    string to_comfirm;
    cout <<"Do you want to change the number? 'y' to change, otherwise to keep original number."<<endl;
    cin >> to_comfirm;
    if(to_comfirm == "Y" || to_comfirm == "y")
    {
        cout << "Input the new num you can want."<<endl;
        cin >> num;
    }

    if(my_CheckComNum(target_id) < stoi(num))
    {
        cout << "We do not have so many commodities left!"<<endl;
        cout << "Changing failed!"<<endl;
        return;
    }

    cout <<"Do you want to change the price? 'y' to change, otherwise to keep original price."<<endl;
    cin >> to_comfirm;
    if(to_comfirm == "Y" || to_comfirm == "y")
    {
        cout << "Input the new price you can afford."<<endl;
        cin >> price;
    }

    if(my_CheckComPrice(target_id) > stod(price))
    {
        cout << "The price your offer must be higher than seller's."<<endl;
        cout << "Changing failed!"<<endl;
        return;
    }

    if(stoi(num) * stod(price) > my_CheckBalance(buyer))
    {
        cout << "You can not afford it!"<<endl;
        cout << "Changing failed!"<<endl;
        return;
    }
    
    ifstream repeat("intention_info.txt");
    if (!repeat.is_open())
    {
        cout << "Error opening file"<<endl; 
        repeat.close();
        return;
    }


    while (!repeat.eof() )
    {
        string buffer,re_com_id,re_buyer;
        getline(repeat,buffer);

        if(buffer.length() == 0)
        {
            cout<<endl;
            cout <<"You do not have such purchase intention or the trading has been finished."<<endl<<endl;
            repeat.close();
            return;
        }

        istringstream is(buffer);

        is >> re_com_id; is >> re_buyer; 

        if(target_id == re_com_id && re_buyer == user_id)
        {
            all_content += com_id; all_content += " ";
            all_content += buyer; all_content += " ";
            all_content += seller; all_content += " ";
            all_content += num; all_content += " ";
            double d_price = stod(price);
            price = to_string(d_price);
            price = price.substr(0,price.length() - 5);
            all_content += price; all_content += " ";
            all_content += buy_time; all_content += " ";
            all_content += added_time; all_content += "\n";
        }
        else
        {
            all_content += buffer;
            all_content += "\n";
        }
    }
    repeat.close();

    all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
    ofstream out("intention_info.txt");
    out.flush();
    out << all_content;
    out.close();   

    cout << "Changing succeeded!"<<endl;
    return;
}

void User::Buyer_check_com_detailed()
{
    ifstream in("commodity_info.txt");
    if (!in.is_open())
        cout << "Error opening file"<<endl; 
    else
    {
        string target_id;
        cout << "Please input the id of the commodity you want to check."<<endl;
        cin >> target_id;
        bool find = false;
        cout<<"======================================================================================================="<<endl;
        while (!in.eof() )
        {
            string buffer1,buffer2,buffer3,id,price,num,seller,addedDate,state;
            getline(in,buffer1);// main info except name and description;
            getline(in,buffer2);//name
            getline(in,buffer3);//description 

            istringstream is(buffer1);
			is >> id;is >> price;is >> num;is >> seller;is >> addedDate;is >> state;
			
            p2te->Reset();
            if(state == "ONAUCTION" && !my_JudgeExpire(addedDate,p2te->GetStrAll()) && target_id == id)
            {
                find = true;
                cout <<"ID:           "<<id<<endl;
                cout <<"Name:         "<<buffer2<<endl;
                cout <<"Price         "<<price<<endl;
                cout <<"Number:       "<<num<<endl;
                cout <<"Seller ID:    "<<seller<<endl;
                cout <<"Added Date:   "<<addedDate<<endl;
                cout <<"State:        "<<state<<endl;
                cout <<"Description:  "<<buffer3<<endl;
            }   
        }
        cout<<"======================================================================================================="<<endl;
        if(find == false)
            cout <<"Fail to find the commodity you want."<<endl;
        cout<<endl<<endl;
        in.close();
    }
}