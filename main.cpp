#include <iostream>
#include <cstring>
#include <string.h>
#include <string>

#include "commodity.h"
#include "user.h"
#include "order.h"

using namespace std;

int main()
{
	char s[100]= "hello world!";
	cout << strlen(s)<<endl;
	string a = s;
	cout << a <<endl;
	User us;
	cout << us.Get_balance()<<endl;
	us.Set_balance(23.5);
	cout << us.Get_balance()<<endl;
	cout<<"hello world"<<endl;
	return 0;
}