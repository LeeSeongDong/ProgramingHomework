#include "Taskmanager.h"

void Taskmanager::initializeDay(Day &day)
{
	time_t timeInfo;

	//struct tm *t;
	struct tm t;

	time(&timeInfo);
	//t = localtime(&timeInfo);
	localtime_s(&t, &timeInfo);

	int year = t.tm_year + 1900;		//1900�����̹Ƿ�
	int month = t.tm_mon + 1;			//0�����ͽ����̹Ƿ�
	int date = t.tm_mday;

	day.setDay(year, month, date);
}


void Taskmanager::setDDayOper(string inputData)
{
	oper = inputData.at(0);
	string temp = inputData.substr(1, inputData.size());
	difference = atoi(temp.c_str());
}

void Taskmanager::setDay(Day &day, Day &dDay, string inputData)
{
	int size = inputData.size();

	string inputYear = inputData.substr(0, size - 4);
	string inputMonth = inputData.substr(size - 4, 2);
	string inputDate = inputData.substr(size - 2, 2);

	int year = atoi(inputYear.c_str());
	int month = atoi(inputMonth.c_str());
	int date = atoi(inputDate.c_str());

	if (date > day.getLastDay(month) || month > 12)
	{
		string error = "�߸��� ��¥ �Է�";
		throw error;
	}

	day.setDay(year, month, date);

	if (isExistDDay)
	{
		setDDay(day, dDay);
	}
}

void Taskmanager::setDDay(Day &day, Day &dDay)
{
	isExistDDay = true;

	dDay.setDay(day.getYear(), day.getMonth(), day.getDate());

	if (oper == '+')
	{
		dDay += difference;
	}
	else
	{
		dDay -= difference;
	}
}


int Taskmanager::checkInputData(string inputData)
{
	string error = "��ȿ���� ���� �Է�";

	if (inputData.size() == 1)
	{
		//�Ϸ��̵�
		if (inputData.at(0) == '+' || inputData.at(0) == '-')
		{
			return ONE_DAY_MOVE;
		}
		else
		{
			throw error;
		}
	}
	else
	{
		//DDay����
		if (inputData.at(0) == '+' || inputData.at(0) == '-')
		{
			//+, - ������ �ڿ� ��� ��������
			for (int i = 1; i < inputData.size(); ++i)
			{
				if (inputData.at(i) < '0' || inputData.at(i) > '9')
				{
					throw error;
				}
			}

			setDDayOper(inputData);
			return SET_D_DAY;
		}
		else
		{
			//������¥�̵�
			for (int i = 0; i < inputData.size(); ++i)
			{
				if (inputData.at(i) < '0' || inputData.at(i) > '9')
				{
					throw error;
				}
			}
			return SET_DAY;
		}
	}
}

void Taskmanager::oneDayMove(Day &day, Day &dDay, string inputData)
{
	if (inputData == "+")
	{
		+day;
		if (isExistDDay)
		{
			+dDay;
		}
	}
	else if (inputData == "-")
	{
		-day;
		if (isExistDDay)
		{
			-dDay;
		}
	}
	else
	{
		string error = "�˼����� ������";
		throw error;
	}
}

void Taskmanager::printDay(Day &day, Day &dDay)
{
	IoHandler ioh;

	ioh.putMsg("[���糯¥] ");
	ioh.printDay(day);

	if (isExistDDay)
	{
		ioh.putMsg("[D");
		ioh.putChar(oper);
		ioh.putNum(difference);
		ioh.putMsg("] ");
		ioh.printDay(dDay);
	}
	else
	{
		ioh.putMsg("[D-day ����]");
	}

	ioh.putNewLine();
}


void Taskmanager::printMenu(Day &day, Day &dDay)
{
	IoHandler ioh;
	while (true)
	{
		try
		{
			printDay(day, dDay);

			string inputData = ioh.inputMenu("��¥ �̵�(�����, (������)+, (����)-), D-day ���(+/- ��¥), ����(Q) : ");

			if (inputData == "q" || inputData == "Q")
			{
				break;
			}

			int menu = checkInputData(inputData);

			switch (menu)
			{

				//�Ϸ��̵�
			case ONE_DAY_MOVE:
			{
				oneDayMove(day, dDay, inputData);
				break;
			}

			//DDay����
			case SET_D_DAY:
			{
				setDDay(day, dDay);
				break;
			}

			//������¥�̵�
			case SET_DAY:
			{
				setDay(day, dDay, inputData);
				break;
			}

			default:
			{
				ioh.putMsg("�߸��� ��� �Է�");
				ioh.putNewLine();
				break;
			}
			}
		}
		catch (string error)
		{
			ioh.putMsg(error);
			ioh.putNewLine();
		}

		ioh.putNewLine();
	}
	ioh.putNewLine();
}