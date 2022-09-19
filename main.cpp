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
	/*Admin ad;
	ad.Remove_commodity();
	User us;
	us.Set_id("U001");
	us.Buyer_search_com();*/
	signin();
	main_platform();
	delete p2ad;
}


