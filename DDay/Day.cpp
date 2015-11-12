#include "Day.h"

Day::Day(int year, int month, int date)
{
	setDay(year, month, date);
}

void Day::operator +()
{
	*this += 1;
}

void Day::operator -()
{
	*this -= 1;
}

void Day::operator +=(int num)
{
	while (num >= 365)
	{
		if ( (month > 2 && isLeap(year + 1)) || (month <= 2 && isLeap(year)) )
		{
			++year;

			if (num == 365)
			{
				num -= 365;

				date -= 1;

				if (date == 0)
				{
					--month;
					date = getLastDay(month);
				}
			}
			else
			{
				num -= 366;
			}
		}
		else
		{
			++year;
			num -= 365;
		}
	}

	date += num;
	while (date > getLastDay(month))
	{
		date -= getLastDay(month);
		++month;

		if (month > 12)
		{
			++year;
			month = 1;
		}
	}
}

void Day::operator -=(int num)
{
	while (num >= 365)
	{
		if ((month > 2 && isLeap(year)) || (month <= 2 && isLeap(year - 1)))
		{
			--year;

			if (num == 365)
			{
				num -= 365;

				date += 1;

				if (date > getLastDay(month))
				{
					++month;
					date = 1;
				}
			}
			else
			{
				num -= 366;
			}
		}
		else
		{
			--year;
			num -= 365;
		}
	}

	date -= num;
	while (date <= 0)
	{
		--month;

		if (month < 1)
		{
			--year;
			month = 12;
		}

		date += getLastDay(month);
	}
}


void Day::setDay(int year, int month, int date)
{
	this->year = year;
	this->month = month;
	this->date = date;
}


int Day::getYear()
{
	return year;
}

int Day::getMonth()
{
	return month;
}

int Day::getDate()
{
	return date;
}

int Day::getLastDay(int month)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;

	case 4:
	case 6:
	case 9:
	case 11:
		return 30;

	case 2:
	{
		if (isLeap(year))
		{
			return 29;
		}
		else
		{
			return 28;
		}
	}

	default:
	{
		string error = "month의 범위 초과";
		throw error;
	}
	}
}

bool Day::isLeap(int year)
{
	if ((year % 4 == 0 || year % 400 == 0) && year % 100 != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
