#include "IoHandler.h"

string IoHandler::inputStr(string msg)
{
	string name;

	cout << msg;
	cin >> name;

	return name;
}

char IoHandler::inputMenu(User user)
{
	char menu;

	cout << "�� ������ �����Ϸ��� ��S����" << endl;
	cout << "������ �̹� ���� ������ ������ ��I����" << endl;
	cout << "������ ���� ���� ������ ������ ��H����" << endl;
	cout << "��ü ������� ����� ������ ��R����" << endl;
	cout << "�̹� ���� ����� �����ϰ� �����Ϸ��� ��Q����" << endl;
	cout << "�̹� ���� ����� �������� �ʰ� �����Ϸ��� ��Z���� �Է��Ͻÿ� [S/I/H/R/Q/Z] : ";
	cin >> menu;

	return menu;
}

string IoHandler::inputLetter(string msg)
{
	string letter;

	cout << msg;

	cin >> letter;

	return letter;
}

int IoHandler::inputNum(string msg)
{
	int num;

	cout << msg;
	cin >> num;

	return num;
}

void IoHandler::printHangman(int count)
{

	cout << "+-----+" << endl;
	cout << "|     |" << endl;

	if (count >= 1)
	{
		cout << "|     O" << endl;
	}
	else
	{
		cout << "|      " << endl;
	}


	if (count >= 4)
	{
		cout << "|    /|��" << endl;
	}
	else if (count >= 3)
	{
		cout << "|    /|  " << endl;
	}
	else if (count >= 2)
	{
		cout << "|    /   " << endl;
	}
	else
	{
		cout << "|          " << endl;
	}


	if (count >= 5)
	{
		cout << "|     |" << endl;
	}
	else
	{
		cout << "|           " << endl;
	}


	if (count >= 7)
	{
		cout << "|    / ��" << endl;
	}
	else if (count >= 6)
	{
		cout << "|     /" << endl;
	}
	else
	{
		cout << "|            " << endl;
	}


	cout << "|" << endl;
	cout << "___" << endl;
}

void IoHandler::printLetter(char a)
{
	cout << a;
}

User IoHandler::printUserMenu(SOCKET& servSock)
{
	User currentUser;
	string userName;
	char a;


	while (true){
		system("cls");

		cout << "====================================================" << endl;
		cout << "                 ��ǰ����� �����մϴ�.             " << endl;
		cout << "====================================================" << endl;

		cout << "(����� �� ���� ������ load�ǰų� ���ο� ����ڰ� ��ϵ˴ϴ�.)" << endl;
		cout << "������� �̸��� �Է��ϼ��� : ";

		while (true)
		{
			while (std::cin.get() != '\n');	//�Է¹��� �����
			getline(cin, userName);

			if (userName != "")
			{
				break;
			}
		}

		char buf[255] = { 0 };
		send(servSock, userName.c_str(), userName.size(), 0);	//����������û
		recv(servSock, buf, sizeof(buf), 0);

		cout << endl << endl;

		if (buf[0] == 'T')
		{
			cout << "��ϵ� ����ڰ� �ֽ��ϴ�. ��ϵ� ������� ���� ������ load�Ϸ��� L��, " << endl;
			cout << "���ο� ����� �̸��� ����Ϸ��� N�� �Է��ϼ��� [L/N] : ";
			cin >> a;

			cout << endl ;

			if (a == 'L' || a == 'l')
			{
				send(servSock, "L", 1, 0);	//�ҷ������û

				recv(servSock, buf, sizeof(buf), 0);

				if (buf[0] == 'N')
				{
					cout << "�̹� �������� ������Դϴ�." << endl;

					system("pause");
					continue;
				}
				else
				{
					send(servSock, "next", 4, 0);
				}

				recv(servSock, buf, sizeof(buf), 0);
				string name = buf;
				send(servSock, "next", 4, 0);

				recv(servSock, buf, sizeof(buf), 0);
				string strWin = buf;
				int win = atoi(strWin.c_str());
				send(servSock, "next", 4, 0);

				recv(servSock, buf, sizeof(buf), 0);
				string strLose = buf;
				int lose = atoi(strLose.c_str());

				User user(name, win, lose);
				currentUser = user;

				cout << "���� ����� [" << userName << "]��/�� �ҷ��ɴϴ�. " << endl;
				system("pause");
				break;
			}

			else if (a == 'N' || a == 'n')
			{
				send(servSock, "N", 1, 0);
				continue;
			}

			else
			{
				send(servSock, "a", 1, 0);
				cout << "L �Ǵ� N�� �Է��ϼ���." << endl;
				system("pause");
				continue;
			}
		}

		else
		{
			User user(userName);
			currentUser = user;

			cout << "���ο� ����� [" << userName << "]��/�� �ҷ��ɴϴ�. ";

			system("pause");

			break;
		}
	}

	return currentUser;
}

void IoHandler::printRank(SOCKET& servSock)
{
	char buf[255] = { 0 };

	recv(servSock, buf, sizeof(buf), 0);
	int numOfUser = atoi(buf);

	for (int i = 0; i < numOfUser; ++i)
	{
		string rank;
		string name;
		string win;
		string lose;
		string winningRate;

		send(servSock, "next", 4, 0);

		recv(servSock, buf, sizeof(buf), 0);
		string msg = buf;
		int msgSize = msg.size();
		int j = 0;

		for (; msg.at(j) != '#'; ++j)
		{
			rank += msg.at(j);
		}
		++j;

		for (; msg.at(j) != '#'; ++j)
		{
			name += msg.at(j);
		}
		++j;

		for (; msg.at(j) != '#'; ++j)
		{
			win += msg.at(j);
		}
		++j;

		for (; msg.at(j) != '#'; ++j)
		{
			lose += msg.at(j);
		}
		++j;

		for (; msg.at(j) != '@'; ++j)
		{
			winningRate += msg.at(j);
		}

		int winCount = atoi(win.c_str());
		int loseCount = atoi(lose.c_str());

		cout << rank << "�� : " << name;
		cout << "( " << winCount+loseCount << "�� ";
		cout << win << "��. ";
		cout << "�·� " << winningRate << "% )";
		cout << endl << endl;
	}

	system("pause");
}

void IoHandler::printPreviousRecord(User& currentUser)
{
	if (currentUser.getLoseCount() != 0 || currentUser.getWinCount() != 0)
	{
		cout << "���� ���� ����� ";
		cout << currentUser.getWinCount() + currentUser.getLoseCount() << "�� ";
		cout << currentUser.getWinCount() << "�� ";
		cout << currentUser.getLoseCount() << "���Դϴ�." << endl;
	}

	else
	{
		cout << "���� ����� �����ϴ�." << endl;
	}

	system("pause");
}

void IoHandler::printCurrentRecord(int win, int lose)
{
	cout << "�̹� ���� ����� ";
	cout << win + lose << "�� ";
	cout << win << "�� ";
	cout << lose << "���Դϴ�." << endl;

	system("pause");
}

void IoHandler::printGameHeader(User& currentUser, int win, int lose)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName() << "�� ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() + 1;
	cout << "��° ������ �����߿� �ֽ��ϴ�. (�̹� ���� " << win << "�� ";
	cout << lose << "��)" << endl;
	cout << "====================================================" << endl;
}

void IoHandler::printMenuHeader(User& currentUser, int win, int lose)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName();
	cout << "�� ��� ������ �����ϰ� �ֽ��ϴ�. (�̹� ���� " << win << "�� ";
	cout << lose << "��)" << endl;
	cout << "====================================================" << endl;
}
