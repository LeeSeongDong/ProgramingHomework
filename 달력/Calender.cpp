#include "Calender.h"

const int datesInYear = 365;

void Calender::setCalender()
{
	month[0].setLastDay(31);		//1월의 마지막 날
									//2월은 윤년일때 체크하기위해
	month[2].setLastDay(31);
	month[3].setLastDay(30);
	month[4].setLastDay(31);
	month[5].setLastDay(30);
	month[6].setLastDay(31);
	month[7].setLastDay(31);
	month[8].setLastDay(30);
	month[9].setLastDay(31);
	month[10].setLastDay(30);
	month[11].setLastDay(31);		//12월의 마지막 날

	int totalDay;

	totalDay = (year - 1) * datesInYear + 1;												//1년 1월 1일부터 지나온 날짜(1월1일은 월요일)
	totalDay += (( year - 1) / 4)- ( (year - 1) / 100) + ( (year - 1) / 400);			//윤년

	if ( ( (year % 4 == 0) && (year % 100 != 0) ) || (year % 400 == 0) )		//입력된 년도가 윤년일때
	{
		month[1].setLastDay(29);
	}
	else
	{
		month[1].setLastDay(28);
	}


	month[0].setStartDayOfWeek(totalDay % sevenDays);						//1월의 시작요일


	for (int i = 1; i < monthSize; ++i)										//2월부터 12월까지 시작요일
	{
		int lastDay;
		lastDay = month[i].getLastDay();

		month[i].setStartDayOfWeek( (month[i - 1].getLastDay() + month[i - 1].getStartDayOfWeek() ) % sevenDays);
		//이번달 시작요일 = (전달 마지막날 + 시작하는요일) % sevenDays
	}

	for (int i = 0; i < monthSize; ++i)										//month에 날짜 저장
	{
		month[i].setMonth( month[i].getStartDayOfWeek() );
	}
}