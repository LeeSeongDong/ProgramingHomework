#ifndef __IOHANDLER_H__
#define __IOHANDLER_H__

#include <iostream>
#include <iomanip>

#include "Calender.h"

class IoHandler
{
public :
	IoHandler() {};
	~IoHandler() {};

	int year;

	int inputYear(string msg);
	void printYear();
	void printCalender(Calender cld);
};

#endif