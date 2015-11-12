#ifndef __IOHANDLER_H__
#define __IOHANDLER_H__

#include "Day.h"

class IoHandler
{
public:
	IoHandler() {};
	~IoHandler() {};

	void putMsg(string msg);
	void putChar(char a);
	void putNum(int num);
	void putNewLine();

	string inputMenu(string msg);
	void printDay(Day day);
};

#endif
