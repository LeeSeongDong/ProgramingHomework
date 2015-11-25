#include "UserList.h"

const int NOT_FOUND = -1;

int UserList::findUserIndex(string name)
{
	for (int i = 0; i < size; ++i)
	{
		if (userList[i].getName() == name)
		{
			return i;
		}
	}
	return NOT_FOUND;
}

User UserList::getUserByName(string name)
{
	return userList[findUserIndex(name)];
}

void UserList::setUserWinningRate()
{
	for (int i = 0; i < size; ++i)
	{
		userList[i].setWinningRate();
	}
}

void UserList::sortByWinningRate()
{
	User temp;

	for (int i = 0; i < size; ++i)
	{
		int k = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (userList[k].getWinningRate() < userList[j].getWinningRate())
			{
				k = j;
			}
			else if (userList[k].getWinningRate() == userList[j].getWinningRate())		//½Â·üÀÌ °°À»¶§ ½ÂÀÌ ¸¹Àº»ç¶÷À» À§·Î
			{
				if (userList[k].getWinCount() < userList[j].getWinCount())
				{
					k = j;
				}
			}
		}

		temp = userList[i];
		userList[i] = userList[k];
		userList[k] = temp;
	}

	/*
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (userList[i].getWinningRate() < userList[j].getWinningRate())
			{
				temp = userList[i];
				userList[i] = userList[j];
				userList[j] = temp;
			}
			else if (userList[i].getWinningRate() == userList[j].getWinningRate())		//½Â·üÀÌ °°À»¶§ ½ÂÀÌ ¸¹Àº»ç¶÷À» À§·Î
			{
				if (userList[i].getWinCount() < userList[j].getWinCount())
				{
					temp = userList[i];
					userList[i] = userList[j];
					userList[j] = temp;
				}
			}
		}
	}
	*/
}

void UserList::insertUser(User& user)
{
	if (capacity == size)
	{
		doubleCapacity();
	}

	++size;
	userList[size - 1] = user;
}

bool UserList::isUserExist(string userName)
{
	if (findUserIndex(userName) != NOT_FOUND)
	{
		return true;
	}
	
	return false;
}

void UserList::doubleCapacity()
{

	int beforCapacity = capacity;

	capacity = capacity * 2;

	User *temp = new User[capacity];

	for (int i = 0; i < beforCapacity; ++i)
	{
		temp[i] = userList[i];
	}

	delete[] userList;

	userList = temp;
}

void UserList::login(string name)
{
	userList[findUserIndex(name)].login();
}

void UserList::logout(string name)
{
	userList[findUserIndex(name)].logout();
}

void UserList::saveRecord(string name, int win, int lose)
{
	userList[findUserIndex(name)].saveRecord(win, lose);
}