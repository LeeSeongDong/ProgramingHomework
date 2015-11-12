#ifndef __IOHANDLER_H__
#define __IOHANDLER_H__

#include "ShapeList.h"

class IoHandler
{
public :
	IoHandler() {};
	~IoHandler() {};

	void putNewLine();
	void putMsg(string msg);
	void putNum(int num);

	char inputChar();
	int inputNum();
};

#endif
