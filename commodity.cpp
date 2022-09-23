#include "commodity.h"
#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
#include <iomanip>

#define is_num(X) (X >= '0' && X <= '9')

bool Commodity::Set_id(string str)  
{
	if(str.length() == 4 && str[0] == 'M' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		com_id = str;
		return true;
	}
	return false;
}

void Commodity::Set_name(string str) 
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

void Commodity::Set_description(string des)  
{
	com_description = des;
}

void Commodity::Set_sellerId(string se_id)  
{
	com_sellerId = se_id;
}

bool Commodity::Set_addedDate(int y, int m, int d, int h, int min, int s)  
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
	com_addedDate.year = y;
	com_addedDate.month = m;
	com_addedDate.day  = d;
	com_addedDate.hour = h;
	com_addedDate.minute = min;
	com_addedDate.second  = s;
	return true;
}

void Commodity::Set_state(CommodityState cs)  
{
	com_state = cs;
}

void Commodity::PrintAll()
{
	cout << "==========================================="<<endl;
	cout << "Commodity ID:          " << com_id <<endl;
	cout << "Commodity Name :       " << com_name <<endl;
	cout << "Commodity Price :      " << com_price <<endl;
	cout << "Commodity Number :     " << com_id <<endl;
	cout << "Commodity Descrption : " << com_description <<endl;
	cout << "Seller ID :            " << com_sellerId <<endl;
	cout << "Added Date :           " << com_addedDate.year << "-" << com_addedDate.month <<"-" << com_addedDate.day
	<<"-"<<com_addedDate.hour << "-" << com_addedDate.minute <<"-" << com_addedDate.second<<endl;
	//cout << "Commodity State :      " << com_state <<endl;
	if(com_state == ONAUCTION)
		cout << "Commodity State :      " << "ONAUCTION" <<endl;
	else
		cout << "Commodity State :      " << "REMOVED" <<endl;
	cout << "==========================================="<<endl;
}

