#ifndef __USERLIST_H__
#define __USERLIST_H__

#include "User.h"

class UserList
{
private :
	int capacity = 10;
	int size = 0;

	User *userList;

	void doubleCapacity();
	int findUserIndex(string name);

public :
	UserList() 
	{
		userList = new User[capacity];
	};
	~UserList()
	{
		delete[]userList;
	};

	User getUserByIndex(int i)
	{
		return userList[i];
	}

	int getSize()
	{
		return size;
	}
	User getUserByName(string name);
	void setUserWinningRate();
	void sortByWinningRate();

	bool isUserExist(string userName);
	void insertUser(User& user);

	void saveRecord(string name, int win, int lose);
	void login(string name);
	void logout(string name);

	
};

#endif