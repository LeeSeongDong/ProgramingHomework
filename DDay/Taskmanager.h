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

	void initializeDay(Day &day);								//Day ���ó�¥�� �ʱ�ȭ

	void setDDayOper(string inputData);							//D-Day (+100 or -100 etc)
	void setDay(Day &day, Day &dDay, string inputData);			//��¥���� 20120630
	void setDDay(Day &day, Day &dDay);							

	int checkInputData(string inputData);						//inputData�� �м��Ͽ� ������ �۾� �Ǵ�

	void oneDayMove(Day &day, Day &dDay, string inputData);		//Day +

	void printDay(Day &day, Day &dDay);							//���
	void printMenu(Day &day, Day &dDay);						//�޴����
};

#endif