#ifndef __MONTH_H__
#define __MONTH_H__

#include <string>

using namespace std;

const int sevenDays = 7;		//�޷��� ���� ����
const int week = 6;				//�޷¿� ��Ÿ�����ִ� �ִ� ���� ����

class Month
{
private :
	int startDayOfWeek;
	int lastDay;

	int dateArr[week][sevenDays];

public :
	Month() {};
	~Month() {};

	void setStartDayOfWeek(int a)
	{
		startDayOfWeek = a;
	}
	void setLastDay(int a)
	{
		lastDay = a;
	}


	int getStartDayOfWeek()
	{
		return startDayOfWeek;
	}
	int getLastDay()
	{
		return lastDay;
	}
	int getDate(int weekIndex, int dayIndex)
	{
		return dateArr[weekIndex][dayIndex];
	}
	
	void setMonth(int startWeek);
};


#endif