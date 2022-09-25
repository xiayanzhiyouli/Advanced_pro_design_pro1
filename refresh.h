#ifndef __REFRESH__
#define __REFRESH__

using namespace std;

#define INTERVAL 300
#define BUFFER_SIZE 100

struct compare_date
{
    int year,month,day,hour,minute,second;
};

struct intention
{
    string com_id,buyer_id,seller_id;
    int num;
    double price;
    string buy_time;
    string added_time;
};

bool my_JudgeExpire(string& a,string& b);
//to judge whether the commodity is expired.

int my_Compare(string& a,string& b);
//return the abs of the time between a and b, with the unit of sec.

compare_date my_Split(string& a);
//split the string standing for time into a struct called compare_date.

string my_Combine(compare_date& a);
//combine compare_date back to a string.

bool my_Earlier(string& a,string& b);
// return true if a is earlier than b, false otherwise.

void my_Deduction(string& a,double n);

double my_CheckBalance(string& a);

void my_ScanIntention();

#endif