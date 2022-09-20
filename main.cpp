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

extern void signin();
extern void main_platform();

extern Admin* p2ad;
int main()
{
	/*signin();
	main_platform();
	delete p2ad;*/
	User us;
	us.Set_id("U001");
	us.Seller_change_com();
}


