#ifndef __Time__
#define __Time__

#include<string>
#include<iostream>
#include <cstring>
#include <string.h>
#include <iomanip>
//#include <string>

#include <fstream>
#include <cstdlib>
#include <sstream>

#include <unistd.h>

#include <ctime>

using namespace std;

class Time
{
public:
    Time()
    {
        time_t curtime;
        time(&curtime);
        tm* nowtime = localtime(&curtime);
        year = nowtime->tm_year + 1900;
        month = nowtime->tm_mon + 1;
        day = nowtime->tm_mday;
        hour = nowtime->tm_hour;
        minute = nowtime->tm_min;
        second = nowtime->tm_sec;
    };

    const int GetIntYear() const;
    const int GetIntMonth() const;
    const int GetIntDay() const;
    const int GetIntHour() const;
    const int GetIntMinute() const;
    const int GetIntSecond() const;

    const string GetStrYear() const;
    const string GetStrMonth() const;
    const string GetStrDay() const;
    const string GetStrHour() const;
    const string GetStrMinute() const;
    const string GetStrSecond() const;  

    string GetStrAll() const; 

    void Reset();  
private:
    int year,month,day,hour,minute,second;
};

#endif