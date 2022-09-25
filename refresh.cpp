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
//the unit of time is the second.

bool my_JudgeExpire(string& a,string& b)
{
    if(my_Compare(a,b) > INTERVAL)
        return true;//expired.
    else
        return false;//not expired.

}
int my_Compare(string& a,string& b)
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

compare_date my_Split(string& a)
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

bool my_Earlier(string& a,string& b)
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

void my_Deduction(string& a,double n)
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
            all_content += to_string(d_balance); all_content += " ";

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

double my_CheckBalance(string& a)
{
    double res;
    ifstream in("user_info.txt");
    if (!in.is_open())
    {
        cout << "Error opening file"<<endl; 
        in.close();
        return;
    }

    string id,name,tele,password,balance,state;

    while (!in.eof() )
    {
        string buffer1,buffer2;
        getline(in,buffer1);// main info except address;
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

void my_ScanIntention()
{
    intention* p = new intention[BUFFER_SIZE];
    int cnt = 0;
    string com, buyer, seller, num, price, buy_time, added_time,temp;

    //TO DO

}