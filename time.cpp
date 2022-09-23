#include "time.h"
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

const int Time::GetIntYear() const
{
    return year;
}

const int Time::GetIntMonth() const
{
    return month;
}

const int Time::GetIntDay() const
{
    return day;
}

const int Time::GetIntHour() const
{
    return hour;
}

const int Time::GetIntMinute() const
{
    return minute;
}

const int Time::GetIntSecond() const
{
    return second;
}

const string Time::GetStrYear() const
{
    return to_string(year);
}

const string Time::GetStrMonth() const
{
    return to_string(month);
}

const string Time::GetStrDay() const
{
    return to_string(day);
}

const string Time::GetStrHour() const
{
    return to_string(hour);
}

const string Time::GetStrMinute() const
{
    return to_string(minute);
}

const string Time::GetStrSecond() const
{
    return to_string(second);
}

string Time::GetStrAll() const
{
    string res;
    res = to_string(year); res += "-";
    res += to_string(month); res += "-";
    res += to_string(day); res += "-";
    res += to_string(hour); res += "-";
    res += to_string(minute); res += "-";
    res += to_string(second); 
    return res;
}

void Time::Reset()
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
}