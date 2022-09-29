#ifndef __USER__
#define __USER__

#include<string>
#include<iostream>
#include <cstring>
#include <string.h>
#include <iomanip>
//#include <string>

#include <fstream>
#include <cstdlib>
#include <sstream>

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
	user_password = "Not Setted";
	user_balance = 0;
	user_state = ACTIVE;
	};
	
	string Get_id() const{return user_id;};
	string Get_name() const{return user_name;};
	string Get_tele() const{return user_tele;};
	string Get_addr() const{return user_addr;};
	string Get_password() const{return user_password;};
	const double Get_balance() const{return user_balance;};
	const UserState Get_state() const{return user_state;};
	
	bool Set_id(string str);
	void Set_name(string str);
	void Set_tele(string str);
	void Set_addr(string str);
	void Set_password(string str);	
	bool Set_balance(double balance);
	void Set_state(UserState us);
	void PrintAll();

	void Seller_release_com();
	void Seller_check_com();//Only check user's own commodity.
	void Seller_change_com();//Only change user's own commodity.
	void Seller_remove_com();//Only remove user's own commodity.
	void Seller_check_order();//Only check user's own order.

	void Buyer_check_com();//Only check commodity on auction.
	void Buyer_check_order();//Only check user's own order.
	void Buyer_search_com();//Only search commodity on auction.
	void Buyer_buy_com();//Only buy commodity on auction.
	void Buyer_cancel_intention();//Only cancel user's own intention.
	void Buyer_change_intention();//Only change user's own intention.
	
	friend ostream& operator << (ostream& os, const User us)
	{
		os << us.user_id << "  " << us.user_name << " " <<us.user_tele
		<< " " << us.user_addr << " "<<us.user_balance;

		if(us.user_state == ACTIVE)
			os << "  ACTIVE"<<endl;
		else
			os << "  INACTIVE"<<endl;

		return os;
	};


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