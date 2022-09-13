#include "commodity.h"
#include<string>
#include<iostream>
#include <cstring>
#include<string.h>

#define is_num(X) (X >= '0' && X <= '9')

bool Commodity::Set_id(char* str)  
{
	if(strlen(str) == 4 && str[0] == 'M' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		com_id = str;
		return true;
	}
	return false;
}

void Commodity::Set_name(char* str) 
{
	com_name = str;
}

bool Commodity::Set_price(double price)  
{
	if(price > 0 && ((int)(price * 100)) % 10 == 0)
	{
		com_price = price;
		return true;
	}
	return false;
}

bool Commodity::Set_num (int num)  
{
	if(num > 0)
	{
		com_num = num;
		return true;
	}
	return false;
}

void Commodity::Set_description(char* des)  
{
	com_description = des;
}

void Commodity::Set_sellerId(char* se_id)  
{
	com_sellerId = se_id;
}

bool Commodity::Set_addedDate(ComDate a_date)  
{
	int y = a_date.year;
	int m = a_date.month;
	int d = a_date.day;
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
	com_addedDate.year = a_date.year;
	com_addedDate.month = a_date.month;
	com_addedDate.day  = a_date.day;
	return true;
}

void Commodity::Set_state(CommodityState cs)  
{
	com_state = cs;
}