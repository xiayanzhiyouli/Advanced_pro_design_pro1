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
extern User* p2us;

int main()
{
	signin();
	main_platform();
	delete p2ad;
	delete p2us;
}


