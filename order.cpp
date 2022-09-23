#include "order.h"
#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
#include <iomanip>

#define is_num(X) (X >= '0' && X <= '9')

bool Order::Set_id(string str)
{
	if(str.length() == 4 && str[0] == 'T' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		order_id = str;
		return true;
	}
	return false;
}

bool Order::Set_com_id(string str) 
{
	if(str.length() == 4 && str[0] == 'M' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		order_com_id = str;
		return true;
	}
	return false;
}

bool Order::Set_price(double price) 
{
	if(price > 0 && ((int)(price * 100)) % 10 == 0)
	{
		order_price = price;
		return true;
	}
	return false;
}

bool Order::Set_num(int num) 
{
	if(num >0)
	{
		order_num = num;
		return true;
	}
	return false;
}

bool Order::Set_order_date(int y, int m, int d, int h, int min, int s) 
{
	if(y <= 0 || m <= 0 || m >12 || d <= 0)
		return false;
	if((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && d >31)
		return false;
	if((m == 4 || m == 6 || m == 9 || m == 11) && d >30)
		return false;
	if(m == 2)
	{
		if((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)//leap year
		{
			if(d >29)
				return false;			
		}
		else if (d > 28) //not leap year
			return false; 
	}
	if(h < 0 || h > 24 || min < 0 || min > 60 || s < 0 || s > 60)
		return false;
	order_date.year = y;
	order_date.month = m;
	order_date.day  = d;
	order_date.hour = h;
	order_date.minute = min;
	order_date.second  = s;
	return true;
}

bool Order::Set_seller_id(string str) 
{
	if(str.length() == 4 && str[0] == 'U' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		order_seller_id = str;
		return true;
	}
	return false;
}

bool Order::Set_buyer_id(string str) 
{
	if(str.length() == 4 && str[0] == 'U' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		order_buyer_id = str;
		return true;
	}
	return false;
}

void Order::PrintAll()
{
	cout << "==========================================="<<endl;
	cout << "Order ID      : "<< order_id <<endl;
	cout << "Commodity ID  : "<< order_com_id <<endl;
	cout << "Price         : "<< order_price <<endl;
	cout << "Num           : "<< order_num <<endl;
	cout << "Trade Date    : "<< order_date.year << "-" << order_date.month << "-" << order_date.day 
	<<"-"<< order_date.hour << "-" << order_date.minute << "-" << order_date.second<<endl;
	cout << "Seller ID     : "<< order_seller_id <<endl;
	cout << "Buyer ID      : "<< order_buyer_id <<endl;
	cout << "==========================================="<<endl;
}