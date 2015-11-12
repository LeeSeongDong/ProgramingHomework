#ifndef __CALENDER_H__
#define __CALENDER_H__

#include "Month.h"

const int monthSize = 12;

class Calender
{
private :
	int year;
	Month month[monthSize];

public :
	Calender(int inputYear)
	{
		year = inputYear;
	};
	~Calender() {};

	Month getMonth(int index)
	{
		return month[index];
	}

	void setCalender();

};

#endif