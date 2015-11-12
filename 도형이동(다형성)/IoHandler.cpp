#include "IoHandler.h"

void IoHandler::putNewLine()
{
	cout << endl;
}

void IoHandler::putMsg(string msg)
{
	cout << msg;
}

void IoHandler::putNum(int num)
{
	cout << num;
}

char IoHandler::inputChar()
{
	char c;
	cin >> c;

	return c;
}

int IoHandler::inputNum()
{
	int num;
	cin >> num;

	return num;
}