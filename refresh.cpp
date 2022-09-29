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
#include "time.h"

using namespace std;
//the unit of time is the second.

extern Time* p2te;

void my_RefreshIntention()
{
    my_ClearComRemoved();
    //while(my_ScanIntention());
}

bool IntentionSmaller(const intention& a,const intention& b)
{
    if(a.price < b.price || (a.price == b.price && a.buy_time > b.buy_time))
        return true;
    return false;
}

void IntentionSwap(intention& a,intention& b)
{
    intention temp = a;
    a = b;
    b = temp;
}

void IntentionSort(intention* p,int n)
{
    for(int i = n;i > 0;--i)
        for(int j = 0;j < i-1;++j)
            if(IntentionSmaller(p[j],p[j + 1]))
                IntentionSwap(p[j],p[j +1]);
}

bool my_JudgeExpire(const string& a,const string& b)
{
    if(my_Compare(a,b) > INTERVAL)
        return true;//expired.
    else
        return false;//not expired.

}
int my_Compare(const string& a,const string& b)
{
    compare_date a_date = my_Split(a);
    compare_date b_date = my_Split(b);
    int res = 0;
    res += a_date.second - b_date.second;
    res += (a_date.minute - b_date.minute)*60;
    res += (a_date.hour - b_date.hour)*3600;
    res += (a_date.day - b_date.day)*3600*24;
    res += (a_date.month - b_date.month)*3600*24*30;
    res += (a_date.year - b_date.year)*3600*24*30*12;
    return abs(res);
}

compare_date my_Split(const string& a)
{
    int temp[5];
    int cnt = 0;
    for(int i = 0;i < a.length();++i)
        if(a[i] == '-')
            temp[cnt++] = i;
    compare_date cd;
    cd.year = stoi(a.substr(0,temp[0]));
    cd.month = stoi(a.substr(temp[0] + 1,temp[1] - temp[0] - 1));
    cd.day = stoi(a.substr(temp[1] + 1,temp[2] - temp[1] - 1));
    cd.hour = stoi(a.substr(temp[2] + 1,temp[3] - temp[2] - 1));
    cd.minute = stoi(a.substr(temp[3] + 1,temp[4] - temp[3] - 1));
    cd.second = stoi(a.substr(temp[4] + 1,temp[5] - temp[4] - 1));
    return cd;
}

string my_Combine(compare_date& a)
{
    string res;
    res = to_string(a.year); res += "-";
    res += to_string(a.month); res += "-";
    res += to_string(a.day); res += "-";
    res += to_string(a.hour); res += "-";
    res += to_string(a.minute); res += "-";
    res += to_string(a.second);

    return res;
}

bool my_Earlier(const string& a,const string& b)
{
    compare_date a_date = my_Split(a);
    compare_date b_date = my_Split(b);

    if(a_date.year < b_date.year)
        return true;
    if(a_date.year > b_date.year)
        return false;  
    if(a_date.month < b_date.month)
        return true;
    if(a_date.month > b_date.month)
        return false;
    if(a_date.day < b_date.day)
        return true;
    if(a_date.day > b_date.day)
        return false;
    if(a_date.hour < b_date.hour)
        return true;
    if(a_date.hour > b_date.hour)
        return false;
    if(a_date.minute < b_date.minute)
        return true;
    if(a_date.minute > b_date.minute)
        return false;
    if(a_date.second < b_date.second)
        return true;
    if(a_date.second > b_date.second)
        return false;
    return true;
}

void my_Deduction(const string& a,double n)
{
    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }

    string id,name,tele,password,balance,state,all_content;

    while (!in.eof() )
    {
        string buffer1,buffer2;
        getline(in,buffer1);// main info except address;
        if(buffer1.length() == 0)
        {
            in.close();
            return;
        }
        getline(in,buffer2);//address
        istringstream is(buffer1);

        is >> id;//id
        if(id == a)
        {
            all_content += id; all_content += " ";
            is >> name; all_content += name; all_content += " ";
            is >> tele; all_content += tele; all_content += " ";
            is >> password; all_content += password; all_content += " ";

            is >> balance; 
            double d_balance = stod(balance);
            d_balance -= n;
            balance = to_string(d_balance); 
            all_content += balance.substr(0,balance.length() - 5); all_content += " ";

            is >> state; all_content += state; all_content += "\n";
            all_content += buffer2; all_content += "\n";
        }
        else
        {
            all_content += buffer1; all_content += "\n";
            all_content += buffer2; all_content += "\n";
        }
    }
    in.close();

    all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
    ofstream out("user_info.txt");
    out.flush();
    out << all_content;
    out.close();
}

void my_Remittance(const string& a,double n)
{
    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }

    string id,name,tele,password,balance,state,all_content;

    while (!in.eof() )
    {
        string buffer1,buffer2;
        getline(in,buffer1);// main info except address;
        if(buffer1.length() == 0)
        {
            in.close();
            return;
        }
        getline(in,buffer2);//address
        istringstream is(buffer1);

        is >> id;//id
        if(id == a)
        {
            all_content += id; all_content += " ";
            is >> name; all_content += name; all_content += " ";
            is >> tele; all_content += tele; all_content += " ";
            is >> password; all_content += password; all_content += " ";

            is >> balance; 
            double d_balance = stod(balance);
            d_balance += n;
            balance = to_string(d_balance);
            all_content += balance.substr(0,balance.length() - 5); all_content += " ";

            is >> state; all_content += state; all_content += "\n";
            all_content += buffer2; all_content += "\n";
        }
        else
        {
            all_content += buffer1; all_content += "\n";
            all_content += buffer2; all_content += "\n";
        }
    }
    in.close();

    all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
    ofstream out("user_info.txt");
    out.flush();
    out << all_content;
    out.close();
}

double my_CheckBalance(const string& a)
{
    double res;
    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return -1;
    }

    string id,name,tele,password,balance,state;

    while (!in.eof() )
    {
        string buffer1,buffer2;
        getline(in,buffer1);// main info except address;
        if(buffer1.length() == 0)
        {
            in.close();
            return -1;
        }
        getline(in,buffer2);//address
        istringstream is(buffer1);

        is >> id;//id
        if(id == a)
        {
            is >> name;
            is >> tele;
            is >> password;
            is >> balance; 
            res = stod(balance);
            is >> state; 
            break;
        }
    }
    in.close();

    return res;
}

int my_CheckComNum(const string& a)
{
    string res;
    ifstream in("commodity_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl;
        return -1; 
    }
        
    while (!in.eof() )
    {
        string buffer1,buffer2,buffer3,temp;
        getline(in,buffer1);
        if(buffer1.length() == 0)
        {
            in.close();
            return -1;
        }
        getline(in,buffer2);
        getline(in,buffer3);

        istringstream is(buffer1);

        is >> temp;

        if(temp == a)
        {
            is >> temp; is >> res;
            break;
        }
    }
    in.close();

    return stoi(res);
}

bool my_ScanIntention()
{
    intention* p = new intention[INTENTION_BUFFER_SIZE];
    int cnt = 0;
    bool find = false;
    string com, buyer, seller, num, price, buy_time, added_time,temp;

    //first ergodic of the file.
    //find an expired commodity.
    ifstream in("intention_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl;
        return false; 
    }
        
    if(in.eof())
        return false;

    while (!in.eof() )
    {
        string buffer;
        getline(in,buffer);

        if(buffer.length() == 0)
        {
            in.close();
            return false;
        }

        istringstream is(buffer);

        is >> com; is >> buyer; is >> seller;
        is >> num; is >> price; is >> buy_time; is >> added_time;

        p2te->Reset();
        if(my_JudgeExpire(added_time,p2te->GetStrAll()))//expired
        {
            find = true;
            break;
        }
    }
    in.close();
    
    if(!find)
        return false;
    //can not find any intention to trade.

    //second ergodic of the file.
    //find all the buyers of this expired commodity.
    string all_content;
    ifstream collect("intention_info.txt");
    if (!collect.is_open())
    {
        cout << "Error opening file"<<endl;
        return false; 
    }
        
    while (!collect.eof() )
    {
        string buffer,temp;
        getline(collect,buffer);
        istringstream is(buffer);

        is >> temp;

        if(temp == com)
        {
            p[cnt].com_id = temp;
            is >> temp; p[cnt].buyer_id = temp;
            is >> temp; p[cnt].seller_id = temp;
            is >> temp; p[cnt].num = stoi(temp);
            is >> temp; p[cnt].price = stod(temp);
            is >> temp; p[cnt].buy_time = temp;
            is >> temp; p[cnt].added_time = temp;

            if(p[cnt].num * p[cnt].price <= my_CheckBalance(p[cnt].buyer_id))
                ++cnt;
        }
        else
        {
            all_content += buffer; all_content += "\n";
        }
    }
    collect.close();

    all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.

    ofstream out("intention_info.txt");
    out.flush();
    out << all_content;
    out.close();
    
    IntentionSort(p,cnt);
    //sort all the buyers.
    //bigger -> smaller.
    int sum = 0,deal_num = 0;
    for(int i = 0;i < cnt;++i)
    {
        sum += p[i].num;
        if(sum <= my_CheckComNum(com))
            ++deal_num;
    }

    UpdateUser(p,deal_num);
    
    UpdateCom(p,deal_num);
    
    UpdateOrder(p,deal_num);
    
    //intention_info.txt has been updated.

    delete[] p;//am necessity.
    return true;
}

void my_ReduceComNum(const string& a, int n)
{
    ifstream in("commodity_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }

    string id,price,num,seller,added_date,state,name,description,all_content;

    while (!in.eof() )
    {
        string buffer1,buffer2,buffer3;
        getline(in,buffer1);
        if(buffer1.length() == 0)
        {
            in.close();
            return;
        }
        getline(in,buffer2);
        getline(in,buffer3);
        istringstream is(buffer1);

        is >> id;//id
        if(id == a)
        {
            all_content += id; all_content += " ";
            is >> price; all_content += price; all_content += " ";
            is >> num; 
            int reduce_num = stoi(num);
            reduce_num -= n;
            all_content += to_string(reduce_num); all_content += " ";
            is >> seller; all_content += seller; all_content += " ";
            is >> added_date; all_content += added_date; all_content += " ";
            is >> state; all_content += state; all_content += "\n";

            all_content += buffer2; all_content += "\n";
            all_content += buffer3; all_content += "\n";
        }
        else
        {
            all_content += buffer1; all_content += "\n";
            all_content += buffer2; all_content += "\n";
            all_content += buffer3; all_content += "\n";
        }
    }
    in.close();

    all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
    ofstream out("commodity_info.txt");
    out.flush();
    out << all_content;
    out.close();
}

void UpdateUser(intention* p,int cnt)
{
    for(int i = 0;i < cnt;++i)
    {
        my_Deduction(p[i].buyer_id,p[i].price * p[i].num);
        my_Remittance(p[i].seller_id,p[i].price * p[i].num);
    }
    return;
}

void UpdateCom(intention* p,int cnt)
{
    for(int i = 0;i < cnt;++i)
        my_ReduceComNum(p[i].com_id,p[i].num);
    return;
}

void UpdateOrder(intention* p,int cnt)
{
    ifstream in("order_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }

    string all_content,lastIdStr;
    int lastIdInt;

    while (!in.eof() )
    {
        string buffer,temp;
        getline(in,buffer);

        if(buffer.length() == 0)
        {
            in.close();
            break;
        }

        istringstream is(buffer);

        is >> lastIdStr;
       
        all_content += buffer;
        all_content += "\n";
    }
    in.close();

    for(int i = 0;i < cnt;++i)
    {
        lastIdInt = stoi(lastIdStr.substr(1,3));
        lastIdStr = to_string(++lastIdInt);

        if(lastIdStr.length() == 3)
            lastIdStr = "T" + lastIdStr;
        if(lastIdStr.length() == 2)
            lastIdStr = "T0" + lastIdStr;
        if(lastIdStr.length() == 1)
            lastIdStr = "T00" + lastIdStr;

        all_content += lastIdStr; all_content += " ";
        all_content += p[i].com_id; all_content += " ";

        string ShortPrice = to_string(p[i].price);
        all_content += ShortPrice.substr(0,ShortPrice.length() - 5); all_content += " ";
        all_content += to_string(p[i].num); all_content += " ";
        p2te->Reset();
        all_content += p2te->GetStrAll(); all_content += " ";
        all_content += p[i].seller_id; all_content += " ";
        all_content += p[i].buyer_id; all_content += "\n";
    }

    all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
    ofstream out("order_info.txt");
    out.flush();
    out << all_content;
    out.close();
    return;
}

void my_ClearComRemoved()
{
    ifstream in("intention_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }

    string all_content,com_id;

    while (!in.eof() )
    {
        string buffer;
        getline(in,buffer);

        if(buffer.length() == 0)
        {
            in.close();
            return;
        }

        istringstream is(buffer);

        is >> com_id;

        if(!my_JudgeComRemoved(com_id))
        {
            all_content += buffer;
            all_content += "\n";
        }  
    }
    in.close();

    all_content = all_content.substr(0,all_content.length() -1);//delete the last '\n'.
    ofstream out("intention_info.txt");
    out.flush();
    out << all_content;
    out.close();
    return;
}

bool my_JudgeComRemoved(string& a)
{
    ifstream in("commodity_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return true;
        //"No Commodity" means all intention need to be deleted.
    }


    while (!in.eof() )
    {
        string buffer1,buffer2,buffer3;
        getline(in,buffer1);
        if(buffer1.length() == 0)
        {
            in.close();
            return true;
            //"No Commodity" means all intention need to be deleted.
        }
        getline(in,buffer2);
        getline(in,buffer3);
        istringstream is(buffer1);

        string temp;
        is >> temp;//id
        if(temp == a)
        {
            is >> temp; is >> temp; is >> temp;
            is >> temp; is >> temp;
            if(temp == "ONAUCTION")
                return false;
            else
                return true;
            break;
        }
    }
    in.close();

    return true;
    //"No Commodity" means all intention need to be deleted.
}

double my_CheckComPrice(const string& a)
{
    string res;
    ifstream in("commodity_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl;
        return -1; 
    }
        
    while (!in.eof() )
    {
        string buffer1,buffer2,buffer3,temp;
        getline(in,buffer1);
        if(buffer1.length() == 0)
        {
            in.close();
            return -1;
        }
        getline(in,buffer2);
        getline(in,buffer3);

        istringstream is(buffer1);

        is >> temp;

        if(temp == a)
        {
            is >> res;
            break;
        }
    }
    in.close();

    return stod(res);
}