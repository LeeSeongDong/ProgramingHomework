#ifndef __IOHANDLER_H__
#define __IOHANDLER_H__

#include "UserList.h"
#include "WordList.h"

class IoHandler
{
public :
	IoHandler() {}
	~IoHandler() {}

	void loadUserFile(string userFile, UserList &userList);
	void loadWordFile(string wordFile, WordList &wordList);
	void saveUserFile(string userFile, UserList &userList);

};

#endif