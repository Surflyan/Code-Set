#include <iostream>
#include <iomanip>
#include "date.h"
using namespace std;

Date::Date()
{   
	year = 1997;
	month = 1;
	day = 1;
}

Date::Date(int Date_y)
{
	year = Date_y;
	month = 1;
	day = 1;
}

Date::Date(int Date_y, int Date_m, int Date_d)
{
	year = Date_y;
	month = Date_m;
	day = Date_d;
}

void Date::setDate(int d_y, int d_m, int d_d)
{
	year = d_y;
	month = d_m;
	day = d_d;
}

int Date::getYear() const
{
	return year;
}
int Date::getMonth() const
{
	return month;
}
int Date::getDay() const
{
	return day;
}

void Date::showDate() const
{   
	cout << "ÈÕÆÚÎª:" << year << "/" << setw(2)
		<< setfill('0') << month << "/" << setw(2) << day << endl;

}




