#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "IoHandler.h"

class Taskmanager
{
private:
	bool isExistDDay;

	char oper;
	int difference;

public:
	Taskmanager()
	{
		isExistDDay = false;
	};
	~Taskmanager() {};

	void initializeDay(Day &day);								//Day 오늘날짜로 초기화

	void setDDayOper(string inputData);							//D-Day (+100 or -100 etc)
	void setDay(Day &day, Day &dDay, string inputData);			//날짜지정 20120630
	void setDDay(Day &day, Day &dDay);							

	int checkInputData(string inputData);						//inputData를 분석하여 수행할 작업 판단

	void oneDayMove(Day &day, Day &dDay, string inputData);		//Day +

	void printDay(Day &day, Day &dDay);							//출력
	void printMenu(Day &day, Day &dDay);						//메뉴출력
};

#endif