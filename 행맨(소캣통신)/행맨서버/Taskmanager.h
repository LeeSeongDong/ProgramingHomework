#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "DBHandler.h"

class Taskmanager
{
private :
	DBHandler dbh;

public :
	Taskmanager() {};
	~Taskmanager() {};

	void startServer(SOCKET& sock);
	string sendUserInfo(SOCKET& clntSock);
	void sendRankInfo(SOCKET& clntSock);
	void sendGameInfo(SOCKET& clntSock);
	void saveAndQuit(SOCKET& clntSock);
	void unsaveAndQuit(string userName);

};

#endif
