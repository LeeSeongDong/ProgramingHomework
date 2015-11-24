#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "HangmanGame.h"

class Taskmanager
{
private :
	User currentUser;
	int win;
	int lose;

public :
	Taskmanager()
	{
		win = 0;
		lose = 0;
	};
	~Taskmanager() {};

	void startHangmanGame(HangmanGame &hg, SOCKET& servSock);
	char selectMenu(char a, HangmanGame &hg, SOCKET& servSock);

	void loadUser(SOCKET& servSock);
	User getCurrentUser()
	{
		return currentUser;
	}
	int getCurrentWin()
	{
		return win;
	}
	int getCurrentLose()
	{
		return lose;
	}

	string upperToLower(string word);
	bool isOverlap(HangmanGame hg);

	void currentUserScore(bool isWin);

	void putRank(SOCKET& servSock);
	void putPreviousRecord();
	void putCurrentRecord();
	void saveAndQuit(SOCKET& servSock);

};

#endif