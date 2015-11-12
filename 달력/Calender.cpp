#include "Calender.h"

const int datesInYear = 365;

void Calender::setCalender()
{
	month[0].setLastDay(31);		//1���� ������ ��
									//2���� �����϶� üũ�ϱ�����
	month[2].setLastDay(31);
	month[3].setLastDay(30);
	month[4].setLastDay(31);
	month[5].setLastDay(30);
	month[6].setLastDay(31);
	month[7].setLastDay(31);
	month[8].setLastDay(30);
	month[9].setLastDay(31);
	month[10].setLastDay(30);
	month[11].setLastDay(31);		//12���� ������ ��

	int totalDay;

	totalDay = (year - 1) * datesInYear + 1;												//1�� 1�� 1�Ϻ��� ������ ��¥(1��1���� ������)
	totalDay += (( year - 1) / 4)- ( (year - 1) / 100) + ( (year - 1) / 400);			//����

	if ( ( (year % 4 == 0) && (year % 100 != 0) ) || (year % 400 == 0) )		//�Էµ� �⵵�� �����϶�
	{
		month[1].setLastDay(29);
	}
	else
	{
		month[1].setLastDay(28);
	}


	month[0].setStartDayOfWeek(totalDay % sevenDays);						//1���� ���ۿ���


	for (int i = 1; i < monthSize; ++i)										//2������ 12������ ���ۿ���
	{
		int lastDay;
		lastDay = month[i].getLastDay();

		month[i].setStartDayOfWeek( (month[i - 1].getLastDay() + month[i - 1].getStartDayOfWeek() ) % sevenDays);
		//�̹��� ���ۿ��� = (���� �������� + �����ϴ¿���) % sevenDays
	}

	for (int i = 0; i < monthSize; ++i)										//month�� ��¥ ����
	{
		month[i].setMonth( month[i].getStartDayOfWeek() );
	}
}