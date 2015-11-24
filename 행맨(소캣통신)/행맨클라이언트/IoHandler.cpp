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

		while (std::cin.get() != '\n');	//�Է¹��� �����
		getline(cin, userName);

		char buf[255] = { 0 };
		send(servSock, userName.c_str(), userName.size(), 0);	//����������û
		recv(servSock, buf, sizeof(buf), 0);

		cout << endl << endl;

		if (buf[0] == 'T')
		{
			cout << "��ϵ� ����ڰ� �ֽ��ϴ�. ��ϵ� ������� ���� ������ load�Ϸ��� L��, " << endl;
			cout << "���ο� ����� �̸��� ����Ϸ��� N�� �Է��ϼ��� [L/N] : ";
			cin >> a;

			cout << endl << endl;

			if (a == 'L' || a == 'l')
			{
				send(servSock, "L", 1, 0);	//�ҷ������û

				recv(servSock, buf, sizeof(buf), 0);

				if (buf[0] == 'N')
				{
					cout << "�̹� �������� ������Դϴ�." << endl;

					cin >> a;
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

				cout << "���� ����� [" << userName << "]��/�� �ҷ��ɴϴ�. ";
				cin >> a;
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
				cin >> a;
				continue;
			}
		}

		else
		{
			User user(userName);
			currentUser = user;

			cout << "���ο� ����� [" << userName << "]��/�� �ҷ��ɴϴ�. ";

			cin >> a;

			break;
		}
	}

	return currentUser;
}

void IoHandler::printRank(SOCKET& servSock)
{
	char a;
	char buf[255] = { 0 };

	int rank;
	string name;
	int win;
	int lose;
	string winningRate;

	recv(servSock, buf, sizeof(buf), 0);
	int numOfUser = atoi(buf);
	

	for (int i = 0; i < numOfUser; ++i)
	{
		send(servSock, "RNK", 4, 0);

		recv(servSock, buf, sizeof(buf), 0);
		rank = atoi(buf);
		send(servSock, "NAM", 4, 0);

		recv(servSock, buf, sizeof(buf), 0);
		name = buf;
		send(servSock, "WIN", 4, 0);

		recv(servSock, buf, sizeof(buf), 0);
		win = atoi(buf);
		send(servSock, "LOSE", 4, 0);

		recv(servSock, buf, sizeof(buf), 0);
		lose = atoi(buf);
		send(servSock, "WINR", 4, 0);

		recv(servSock, buf, sizeof(buf), 0);
		winningRate = buf;

		cout << rank << "�� : " << name;
		cout << "( " << win + lose << "�� ";
		cout << win << "��. ";
		cout << "�·� " << winningRate << "% )";
		cout << endl << endl;
	}

	cin >> a;
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

	char a;
	cin >> a;
}

void IoHandler::printCurrentRecord(int win, int lose)
{
	cout << "�̹� ���� ����� ";
	cout << win + lose << "�� ";
	cout << win << "�� ";
	cout << lose << "���Դϴ�." << endl;

	char a;
	cin >> a;
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
