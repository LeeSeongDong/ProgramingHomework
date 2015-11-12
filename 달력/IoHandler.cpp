#include "IoHandler.h"

const int bigYearNumber = 10;
const int bigYearSize = 5;

const int calenderColumn = 3;
const int calenderRow = 4;

const int dateSize = 3;
const int rowSize = dateSize * 7;

int IoHandler::inputYear(string msg)
{
	while (true)
	{
		cout << msg;
		cin >> year;

		if (year > 0)
		{
			return year;
		}

		cout << "���� ������ �Է��ϼ���." << endl;
	}
}


void IoHandler::printYear()
{

	string bigYear[bigYearNumber][bigYearSize];

	bigYear[0][0] = "#####";
	bigYear[0][1] = "#   #";
	bigYear[0][2] = "#   #";
	bigYear[0][3] = "#   #";
	bigYear[0][4] = "#####";

	bigYear[1][0] = "    #";
	bigYear[1][1] = "    #";
	bigYear[1][2] = "    #";
	bigYear[1][3] = "    #";
	bigYear[1][4] = "    #";

	bigYear[2][0] = "#####";
	bigYear[2][1] = "    #";
	bigYear[2][2] = "#####";
	bigYear[2][3] = "#    ";
	bigYear[2][4] = "#####";

	bigYear[3][0] = "#####";
	bigYear[3][1] = "    #";
	bigYear[3][2] = "#####";
	bigYear[3][3] = "    #";
	bigYear[3][4] = "#####";

	bigYear[4][0] = "#   #";
	bigYear[4][1] = "#   #";
	bigYear[4][2] = "#####";
	bigYear[4][3] = "    #";
	bigYear[4][4] = "    #";

	bigYear[5][0] = "#####";
	bigYear[5][1] = "#    ";
	bigYear[5][2] = "#####";
	bigYear[5][3] = "    #";
	bigYear[5][4] = "#####";

	bigYear[6][0] = "#####";
	bigYear[6][1] = "#    ";
	bigYear[6][2] = "#####";
	bigYear[6][3] = "#   #";
	bigYear[6][4] = "#####";

	bigYear[7][0] = "#####";
	bigYear[7][1] = "    #";
	bigYear[7][2] = "    #";
	bigYear[7][3] = "    #";
	bigYear[7][4] = "    #";

	bigYear[8][0] = "#####";
	bigYear[8][1] = "#   #";
	bigYear[8][2] = "#####";
	bigYear[8][3] = "#   #";
	bigYear[8][4] = "#####";

	bigYear[9][0] = "#####";
	bigYear[9][1] = "#   #";
	bigYear[9][2] = "#####";
	bigYear[9][3] = "    #";
	bigYear[9][4] = "#####";

	int inputYear;
	int digitCount = 1;

	inputYear = year;

	//inputYear�� �ڸ����� �ľ��ϱ� ���� ��
	while (true)
	{
		if (inputYear / 10 > 0)
		{
			inputYear = inputYear / 10;
			++digitCount;
		}
		else break;
	}

	inputYear = year;

	int *temp = new int[digitCount];		//inputyear�� �� �ڸ����� �����ϱ����� �迭
	
	for (int i = 0; i < digitCount; ++i)	//����index�� ���� �ڸ����� ����
	{
		temp[digitCount - i - 1] = inputYear % 10;
		inputYear = inputYear / 10;
	}

	//inputYear�� ����ϴ� ��
	for (int i = 0; i < bigYearSize; ++i)
	{
		cout << "                   ";						//year�� ��� ������
		for (int j = 0; j < digitCount; ++j)
		{
			cout << setw(bigYearSize + 2) << bigYear[ temp[j] ][i];
		}
		cout << endl;
	}
	cout << endl;
}


void IoHandler::printCalender(Calender cld)
{
	int month;
	month = 1;

	for (int i = 0; i < calenderRow; ++i)
	{

		for (int j = 0; j < calenderColumn; ++ j)		//�ش� �� ���
		{
			cout << "  " << month + j << "��" << setw(rowSize);
		}

		cout << endl;


		for (int j = 0; j < calenderColumn; ++j)		//���� ���
		{
			cout << setw(dateSize) << "��";
			cout << setw(dateSize) << "��";
			cout << setw(dateSize) << "ȭ";
			cout << setw(dateSize) << "��";
			cout << setw(dateSize) << "��";
			cout << setw(dateSize) << "��";
			cout << setw(dateSize) << "��";

			cout << "   ";
		}

		cout << endl;

		for (int j = 0; j < week; ++j)		//��¥ ���
		{
			for (int k = 0; k < calenderColumn; ++k)			
			{
				for (int l = 0; l < sevenDays; ++l)
				{
					if (cld.getMonth(month + k - 1).getDate(j, l) == 0)
					{
						cout << "   ";			//dateArr���� 0�ΰ��� ��ĭ
					}
					else
					{
						cout << setw(dateSize) << cld.getMonth(month + k - 1).getDate(j, l);
					}
				}

				cout << "   ";			//���� ����
			}

			cout << endl;
		}

		cout << endl;
		month += calenderColumn;
	}
}