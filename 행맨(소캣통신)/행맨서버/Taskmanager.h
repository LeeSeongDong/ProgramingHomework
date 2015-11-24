#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "IoHandler.h"

class Taskmanager
{
private :

public :
	Taskmanager() {};
	~Taskmanager() {};

	void startServer(SOCKET& sock, UserList &userList, WordList &wordList);
	string sendUserInfo(UserList& userList, SOCKET& clntSock);
	void sendRankInfo(UserList& userList, SOCKET& clntSock);
	void sendGameInfo(WordList& wordList, SOCKET& clntSock);
	void saveAndQuit(UserList& userList, SOCKET& clntSock);

};

#endif
