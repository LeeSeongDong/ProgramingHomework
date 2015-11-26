#include "User.h"

void User::setWinningRate()
{
	float win = (float)winCount;
	float lose = (float)loseCount;

	int temp;

	if ( (win + lose) == 0 || win == 0)
	{
		winningRate = 0;
	}
	else if (lose == 0)
	{
		winningRate = 100;
	}

	winningRate = win / (win + lose);

	//�Ҽ� ��°�ڸ����� �ݿø�
	winningRate = winningRate * 100000;
	temp = (int)winningRate;

	if (temp % 10 >= 5)
	{
		temp += 10;
		temp = temp / 10;

		winningRate = (float)temp / 100;
	}
	else
	{
		temp = temp / 10;
		winningRate = (float)temp / 100;
	}
}