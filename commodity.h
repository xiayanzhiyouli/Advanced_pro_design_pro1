#ifndef __COMMODITY__
#define __COMMODITY__

#include<string>
#include<iostream>
#include<cstring>
#include<string.h>
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
	
	const char* Get_id() const {return com_id.c_str();};
	const char* Get_name() const {return com_name.c_str();};
	const double Get_price() const {return com_price;};
	const int Get_num() const {return com_num;};
	const char* Get_description() const {return com_description.c_str();};
	const char* Get_sellerId() const {return com_sellerId.c_str();};
	const ComDate Get_addedDate() const {return com_addedDate;};
	const CommodityState Get_state() const {return com_state;};
	
	bool Set_id(char* str);
	void Set_name(char* str);
	bool Set_price(double price);
	bool Set_num (int num);
	void Set_description(char* des);
	void Set_sellerId(char* se_id);
	bool Set_addedDate(ComDate a_date);
	void Set_state(CommodityState cs);	

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