#include "Month.h"

void Month::setMonth(int startWeek)
{
	int date = 1;

	for (int i = 0; i < startWeek; ++i)		//첫주에 나타나는 날짜
	{
		dateArr[0][i] = 0;
	}

	for (int i = startWeek; i < sevenDays; ++i)		//첫주에 나타나는 날짜
	{
		dateArr[0][i] = date;
		++date;
	}


	for (int i = 1; i < week; ++i)					//두번째주부터 마지막까지 나타나는 날짜
	{
		for (int j = 0; j < sevenDays; ++j)
		{

			if (date > lastDay)
			{
				dateArr[i][j] = 0;
			}
			else
			{
				dateArr[i][j] = date;
			}

			++date;
		}
	}
}