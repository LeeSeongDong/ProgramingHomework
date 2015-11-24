#ifndef __USER_H__
#define __USER_H__

#include "Header.h"

class User
{
private :

	string name;
	int winCount;
	int loseCount;
	float winningRate;


public :
	bool loginFlag;
	User() {};
	User(string inputName)
	{
		name = inputName;
		winCount = 0;
		loseCount = 0;
		loginFlag = false;
	};
	User(string inputName, int inputWinCount, int inputLoseCount)
	{
		name = inputName;
		winCount = inputWinCount;
		loseCount = inputLoseCount;
		loginFlag = false;
	};
	~User() {};


	string getName()
	{
		return name;
	}
	int getWinCount()
	{
		return winCount;
	}
	int getLoseCount()
	{
		return loseCount;
	}
	float getWinningRate()
	{
		return winningRate;
	}
	bool isLogin()
	{
		return loginFlag;
	}

	void setWinningRate();
	void saveRecord(int currentWinCount, int currentLoseCount)
	{
		winCount += currentWinCount;
		loseCount += currentLoseCount;
	}

	void login()
	{
		loginFlag = true;
	}
	void logout()
	{
		loginFlag = false;
	}
};

#endif