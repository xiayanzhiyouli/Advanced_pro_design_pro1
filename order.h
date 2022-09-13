#ifndef __ORDER__
#define __ORDER__

#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
//#include <string>
using namespace std;

struct OrderDate
{
	int year;
	int month;
	int day;
};

class Order
{
public:
	Order()
	{
		order_id = "Not Setted";
		order_com_id = "Not Setted";
		order_price = 0;
		order_num = 0;
		order_date.year = 1980;
		order_date.month = 6;
		order_date.day = 1;
		order_seller_id = "Not Setted";
		order_buyer_id = "Not Setted";		
	}
	
	const char* Get_id() const {return order_id.c_str();};
	const char* Get_com_id() const {return order_com_id.c_str();};
	const double Get_price() const {return order_price;};
	const int Get_num() const {return order_num;};
	const OrderDate Get_order_date() const {return order_date;};
	const char* Get_seller_id() const {return order_seller_id.c_str();};
	const char* Get_buyer_id() const {return order_buyer_id.c_str();};
	
	bool Set_id(char* str);
	bool Set_com_id(char* str);
	bool Set_price(double price);
	bool Set_num(int num);
	bool Set_order_date(OrderDate od);
	bool Set_seller_id(char* str);
	bool Set_buyer_id(char* str);
	
private:
	string order_id;//T001
	string order_com_id;//M001
	double order_price;
	int order_num;
	OrderDate order_date;
	string order_seller_id;//U001
	string order_buyer_id;//U001
};

#endif