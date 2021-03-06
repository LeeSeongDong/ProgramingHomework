#ifndef __IOHANDLER_H__
#define __IOHANDLER_H__

#include "UserList.h"
#include "WordList.h"

#include <iostream>
#include <fstream>


class IoHandler
{
public :
	IoHandler() {}
	~IoHandler() {}

	void loadUserFile(string userFile, UserList &userList);
	void loadWordFile(string wordFile, WordList &wordList);
	void saveUserFile(string userFile, UserList &userList);

	string inputName(string msg);
	char inputMenu(User user);
	string inputLetter(string msg);

	void printHangman(int count);
	void printLetter(char a);

	User printUserMenu(UserList &userList);

	
	void printRank(UserList &userList);
	void printPreviousRecord(UserList &userList, User currentUser);
	void printCurrentRecord(User currentUser);

	void printGameHeader(User currentUser);
	void printMenuHeader(User currentUser);

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