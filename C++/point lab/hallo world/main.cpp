#include <iostream>
#include <iomanip>
#include "date.h"
#include "Point.h"


using namespace std;

int main()
{
	Date date1,  date3(2016, 7, 8);

	date1.showDate();
	date3.showDate();	
	cout << date3.getMonth() << endl;
	
	Point p1, p2(2.1, 2.3);
	p1.display_point();
	p2.display_point();




}

