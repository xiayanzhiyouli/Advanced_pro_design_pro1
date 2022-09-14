#include "user.h"
#include<string>
#include<iostream>
#include <cstring>
#include<string.h>
#include <iomanip>

#define is_num(X) (X >= '0' && X <= '9')

bool User::Set_id(char* str) 
{
	if(strlen(str) == 4 && str[0] == 'U' && is_num(str[1]) && is_num(str[2]) && is_num(str[3]) )
	{
		user_id = str; 
		return true;
	}
	return false;
}

void User::Set_name(char* str) 
{
	user_name = str; 
}

void User::Set_tele(char* str) 
{
	user_tele = str; 
}

void User::Set_addr(char* str) 
{
	user_addr = str; 
}

void User::Set_password(char* str) 
{
	user_password = str; 
}
	
bool User::Set_balance(double balance) 
{
	if(balance >= 0 && ((int)(balance * 100))  % 10 == 0)
	{
		user_balance = balance;
		return true;
	}
	return false;
}

void User::Set_state(UserState us) 
{
	user_state = us; 
}

void User::PrintAll()
{
	cout << "==========================================="<<endl;
	cout << "User ID       : "<< user_id <<endl;
	cout << "User Name     : "<< user_name <<endl;
	cout << "User Tele     : "<< user_tele <<endl;
	cout << "User Address  : "<< user_addr <<endl;
	cout << "User Balance  : "<< user_balance <<endl;
	if(user_state == ACTIVE)
		cout << "User State    : "<< "ACTIVE" <<endl;
	else
		cout << "User State    : "<< "INACTIVE" <<endl;
	cout << "==========================================="<<endl;
}