#ifndef __ORDER__
#define __ORDER__

#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
#include <iomanip>
//#include <string>
using namespace std;

struct OrderDate
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
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
		order_date.hour = 12;
		order_date.minute = 0;
		order_date.second = 0;
		order_seller_id = "Not Setted";
		order_buyer_id = "Not Setted";		
	}
	
	string Get_id() const {return order_id;};
	string Get_com_id() const {return order_com_id;};
	const double Get_price() const {return order_price;};
	const int Get_num() const {return order_num;};
	const OrderDate Get_order_date() const {return order_date;};
	string Get_seller_id() const {return order_seller_id;};
	string Get_buyer_id() const {return order_buyer_id;};
	
	bool Set_id(string str);
	bool Set_com_id(string str);
	bool Set_price(double price);
	bool Set_num(int num);
	bool Set_order_date(int y, int m, int d, int h, int min, int s);
	bool Set_seller_id(string str);
	bool Set_buyer_id(string str);
	void PrintAll();

	friend ostream& operator << (ostream& os, const Order od)
	{
		return os << od.order_id << "  " << od.order_com_id << setw(10) << od.order_price << setw(5) 
		<< od.order_num << " "<<od.order_date.year << "-"<< od.order_date.month <<"-"<<od.order_date.day
		<<"-"<<od.order_date.hour << "-"<< od.order_date.minute <<"-"<<od.order_date.second
		<<" "<< od.order_seller_id << " "<< od.order_buyer_id <<endl;
	};
	
private:
	string order_id;//T001
	string order_com_id;//M001
	double order_price;
	int order_num;
	OrderDate order_date;
	string order_seller_id;//U001
	string order_buyer_id;//U002
};

#endif