#include <iostream>
#include <cstring>
#include <string.h>
#include <string>
#include <iomanip>

#include "commodity.h"
#include "user.h"
#include "order.h"
#include "admin.h"

using namespace std;

int main()
{
	Admin ad;
	//ad.Check_commodity();
	//ad.Check_order();
	//ad.Check_user();
	//ad.Ban_user();
	ad.Check_user();
	ad.Ban_user();
}