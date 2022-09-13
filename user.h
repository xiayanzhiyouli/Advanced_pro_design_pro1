#ifndef __USER__
#define __USER__

#include<string>
#include<iostream>
#include <cstring>
#include <string.h>
//#include <string>
using namespace std;

enum UserState  {INACTIVE,ACTIVE};
class User
{
public:
	User() {
	user_id = "Not Setted";	//U001
	user_name = "Not Setted";	
	user_tele = "Not Setted";	
	user_addr = "Not Setted";	
	user_balance = 0;
	user_state = ACTIVE;
	};
	
	const char* Get_id() const{return user_id.c_str();};
	const char* Get_name() const{return user_name.c_str();};
	const char* Get_tele() const{return user_tele.c_str();};
	const char* Get_addr() const{return user_addr.c_str();};
	const char* Get_password() const{return user_password.c_str();};
	const double Get_balance() const{return user_balance;};
	const UserState Get_state() const{return user_state;};
	
	bool Set_id(char* str);
	void Set_name(char* str);
	void Set_tele(char* str);
	void Set_addr(char* str);
	void Set_password(char* str);	
	bool Set_balance(double balance);
	void Set_state(UserState us);
	
private:
	string user_id;
	string user_name;
	string user_tele;
	string user_addr;
	string user_password;
	double user_balance;
	enum UserState user_state;
};
#endif