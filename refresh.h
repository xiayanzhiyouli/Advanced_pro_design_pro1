#ifndef __REFRESH__
#define __REFRESH__

using namespace std;

#define INTERVAL 300
#define INTENTION_BUFFER_SIZE 100

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

bool IntentionSmaller(const intention& a,const intention& b);
//return true if a is "really smaller" than b, false otherwise.
//a is "really smaller" than b if a.price < b.price || (a.price == b.price && a.buy_time > b.buy_time).

void IntentionSwap(intention& a,intention& b);

void IntentionSort(intention* p,int n);
//bigger -> smaller.

bool my_JudgeExpire(const string& a,const string& b);
//to judge whether the commodity is expired.

int my_Compare(const string& a,const string& b);
//return the abs of the time between a and b, with the unit of sec.

compare_date my_Split(const string& a);
//split the string standing for time into a struct called compare_date.

string my_Combine(const compare_date& a);
//combine compare_date back to a string.

bool my_Earlier(const string& a,const string& b);
// return true if a is earlier than b, false otherwise.

void my_Deduction(const string& a,double n);
//deduce buyer's balance after the trade was done.

void my_Remittance(const string& a,double n);
//remit buyer's balance after the trade was done.

double my_CheckBalance(const string& a);
//check buyer's balance before the trade is done.

int my_CheckComNum(const string& a);
//chek commodity's num before the trade is done.

double my_CheckComPrice(const string& a);
//chek commodity's price before the intention is changed.

bool my_ScanIntention();
//only choose an expired commodity to trade once.
//return true if find intention for trading, false otherwise.

void my_ClearComRemoved();
//clear all commodities removed.

bool my_JudgeComRemoved(string& a);
//return whether a commodity has been removed.

void my_RefreshIntention();
//refresh the file intention.txt.

void my_ReduceComNum(const string& a, int n);
//reduce commodity's num after the trade was done.

void UpdateUser(intention* p,int cnt);
void UpdateCom(intention* p,int cnt);
void UpdateOrder(intention* p,int cnt);
//three funtions are used for updating information in their own txt file.
#endif