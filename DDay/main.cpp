#include "Taskmanager.h"

int main()
{
	Day day;
	Day dDay;
	Taskmanager tm;
	IoHandler ioh;

	tm.initializeDay(day);		//현재날짜

	tm.printMenu(day, dDay);



	return 0;
}