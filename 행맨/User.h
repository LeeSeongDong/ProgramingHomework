#ifndef __USER_H__
#define __USER_H__

#include <string>

using namespace std;

class User
{
private :

	string name;
	int winCount;
	int loseCount;
	float winningRate;

public :
	User() {};
	User(string inputName)
	{
		name = inputName;
		winCount = 0;
		loseCount = 0;
	};
	User(string inputName, int inputWinCount, int inputLoseCount)
	{
		name = inputName;
		winCount = inputWinCount;
		loseCount = inputLoseCount;
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

	void setWinningRate();
	void saveRecord(int currentWinCount, int currentLoseCount)
	{
		winCount += currentWinCount;
		loseCount += currentLoseCount;
	}
};

#endif