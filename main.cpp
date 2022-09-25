#include <iostream>
#include <cstring>
#include <string.h>
#include <string>
#include <iomanip>
#include <ctime>

#include "commodity.h"
#include "user.h"
#include "order.h"
#include "admin.h"
#include "time.h"
#include "signIn.h"
#include "refresh.h"

using namespace std;

//extern void signin();
//extern void main_platform();

Admin* p2ad = new Admin;
User* p2us = new User;
Time* p2te = new Time;

int main()
{
	signin();
	main_platform();
	delete p2ad;
	delete p2us;
	delete p2te;
	return 0;
}



