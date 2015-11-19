#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "IoHandler.h"

class Taskmanager
{
private :

public :
	Taskmanager() {};
	~Taskmanager() {};

	void startServer(void* p, UserList &userList, WordList &wordList);
	void sendUserInfo(UserList& userList, SOCKET& clntSock);
	void sendRankInfo(UserList& userList, SOCKET& clntSock);
	void sendGameInfo(WordList& wordList, SOCKET& clntSock);

};

#endif
