#ifndef __IOHANDLER_H__
#define __IOHANDLER_H__

#include "User.h"

class IoHandler
{
public :
	IoHandler() {}
	~IoHandler() {}

	string inputStr(string msg);
	char inputMenu(User user);
	string inputLetter(string msg);
	int inputNum(string msg);

	void printHangman(int count);
	void printLetter(char a);

	User printUserMenu(SOCKET& servSock);

	
	void printRank(SOCKET& servSock);
	void printPreviousRecord(User& currentUser);
	void printCurrentRecord(int win, int lose);

	void printGameHeader(User& currentUser, int win, int lose);
	void printMenuHeader(User& currentUser, int win, int lose);

	void putMsg(string msg)
	{
		cout << msg;
	}
	void putNewLine()
	{
		cout << endl;
	}
	void putSpace()
	{
		cout << " ";
	}
};

#endif