#ifndef __ADMIN__
#define __ADMIN__

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

class Admin
{
public:    
    Admin()
    {
        admin_name = "admin";
        admin_password = "123456";
    }

    string Get_name() const {return admin_name;};
    string Get_password() const {return admin_password;};

    void Check_commodity();
    void Search_commodity();
    void Remove_commodity();
    void Check_order();
    void Check_user();
    void Ban_user();

    
private:
    string admin_name;
    string admin_password;
};
#endif