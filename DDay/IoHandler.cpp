#include "IoHandler.h"

void IoHandler::putMsg(string msg)
{
	cout << msg;
}

void IoHandler::putChar(char a)
{
	cout << a;
}

void IoHandler::putNum(int num)
{
	cout << num;
}

void IoHandler::putNewLine()
{
	cout << endl;
}


string IoHandler::inputMenu(string msg)
{
	string inputData;

	cout << msg;
	cin >> inputData;
	return inputData;
}

void IoHandler::printDay(Day day)
{
	cout << day.getYear() << "³â ";
	cout << day.getMonth() << "¿ù ";
	cout << day.getDate() << "ÀÏ ";
}