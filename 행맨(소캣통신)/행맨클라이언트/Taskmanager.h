#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "HangmanGame.h"

class Taskmanager
{
private :
	User currentUser;

public :
	Taskmanager() {};
	~Taskmanager() {};

	void startHangmanGame(HangmanGame &hg, WordList &wordList);
	char selectMenu(char a, HangmanGame &hg, UserList &userList, WordList &wordList);

	void loadUser(UserList &userList);
	User getCurrentUser()
	{
		return currentUser;
	}

	string upperToLower(string word);
	bool isOverlap(HangmanGame hg);

	void currentUserScore(bool isWin);

	void putRank(UserList &userList);
	void putPreviousRecord(UserList &userList);
	void putCurrentRecord();
	void saveAndQuit(UserList &userList);

};

#endif