#ifndef __DAY_H__
#define __DAY_H__

#include "Header.h"

class Day
{
private :
	int year;
	int month;
	int date;

public :
	Day() {};
	Day(int year, int month, int date);
	~Day() {};

	void operator +();
	void operator -();
	void operator +=(int num);
	void operator -=(int num);

	void setDay(int year, int month, int date);

	int getYear();
	int getMonth();
	int getDate();

	int getLastDay(int month);
	bool isLeap(int year);

};

#endif
