#include "order.h"
#include<string>
#include<iostream>
#include <cstring>
#include<string.h>

#define is_num(X) (X >= '0' && X <= '9')

bool Order::Set_id(char* str)
{
	if(strlen(str) == 4 && str[0] == 'T' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		order_id = str;
		return true;
	}
	return false;
}

bool Order::Set_com_id(char* str) 
{
	if(strlen(str) == 4 && str[0] == 'M' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
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

bool Order::Set_order_date(OrderDate od) 
{
	int y = od.year;
	int m = od.month;
	int d = od.day;
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
	order_date.year = od.year;
	order_date.month = od.month;
	order_date.day  = od.day;
	return true;
}

bool Order::Set_seller_id(char* str) 
{
	if(strlen(str) == 4 && str[0] == 'U' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		order_seller_id = str;
		return true;
	}
	return false;
}

bool Order::Set_buyer_id(char* str) 
{
	if(strlen(str) == 4 && str[0] == 'U' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		order_buyer_id = str;
		return true;
	}
	return false;
}