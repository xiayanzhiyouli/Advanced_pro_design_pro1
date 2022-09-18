#ifndef __COMMODITY__
#define __COMMODITY__

#include<string>
#include<iostream>
#include<cstring>
#include<string.h>
#include <iomanip>
//#include <string>
using namespace std;

enum CommodityState  {REMOVED,ONAUCTION};

struct ComDate
{
	int year;
	int month;
	int day;
};
class Commodity
{
public:
	Commodity() 
	{
		com_id = "Not Setted";//M001
		com_name = "Not Setted";
		com_price = 0;
		com_num = 0;
		com_description = "Not Setted";
		com_sellerId = "Not Setted";
		com_addedDate.year = 1980;
		com_addedDate.month = 6;
		com_addedDate.day = 1;
		com_state = ONAUCTION;	
	};
	
	string Get_id() const {return com_id;};
	string Get_name() const {return com_name;};
	const double Get_price() const {return com_price;};
	const int Get_num() const {return com_num;};
	string Get_description() const {return com_description;};
	string Get_sellerId() const {return com_sellerId;};
	const ComDate Get_addedDate() const {return com_addedDate;};
	const CommodityState Get_state() const {return com_state;};
	
	bool Set_id(string str);
	void Set_name(string str);
	bool Set_price(double price);
	bool Set_num (int num);
	void Set_description(string des);
	void Set_sellerId(string se_id);
	bool Set_addedDate(int y, int m, int d);
	void Set_state(CommodityState cs);	
	void PrintAll();

	friend ostream& operator << (ostream& os, const Commodity com)
	{
		os << com.com_id << "  " << setw(10) << com.com_name << setw(10) << com.com_price << setw(5) 
		<< com.com_num << " "<<com.com_sellerId << " " 
		<< com.com_addedDate.year << "-"<<com.com_addedDate.month << "-"<<com.com_addedDate.day;

		if(com.com_state == ONAUCTION)
			os << "  ONAUCTION" <<endl;
		else
			os << "  REMOVED" <<endl;
		
		return os;
	};

private:
	string com_id;
	string com_name;
	double com_price;
	int com_num;
	string com_description;
	string com_sellerId;
	ComDate com_addedDate;
	CommodityState com_state;
};
#endif