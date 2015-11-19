#include "IoHandler.h"

string IoHandler::inputName(string msg)
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


User IoHandler::printUserMenu(UserList &userList, SOCKET& servSock)
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
		cin >> userName;
		//getline(cin, userName);

		char buf[255];
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
				string name = buf;
				recv(servSock, buf, sizeof(buf), 0);
				string strWin = buf;
				int win = atoi(strWin.c_str());
				recv(servSock, buf, sizeof(buf), 0);
				string strLose = buf;
				int lose = atoi(strWin.c_str());

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

	
void IoHandler::printRank(UserList &userList)
{
	int sameRank = 0;
	char a;

	for (int i = 0; i < userList.getSize(); ++i)
	{
		if (i != 0)
		{
			if (userList.getUserByIndex(i - 1).getWinningRate() == userList.getUserByIndex(i).getWinningRate())
			{
				sameRank += 1;
			}
			else
			{
				sameRank = 0;
			}
		}
		cout << i + 1 - sameRank << "�� : " << userList.getUserByIndex(i).getName();
		cout << "( " << userList.getUserByIndex(i).getWinCount() + userList.getUserByIndex(i).getLoseCount() << "�� ";
		cout << userList.getUserByIndex(i).getWinCount() << "��. ";
		cout << "�·� " << userList.getUserByIndex(i).getWinningRate() << "% )";
		cout << endl << endl;

	}

	cin >> a;
}


void IoHandler::printPreviousRecord(UserList &userList, User currentUser)
{
	if (userList.isUserExist(currentUser.getName()) == true)
	{
		cout << "���� ���� ����� ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() + userList.getUserByName(currentUser.getName()).getLoseCount() << "�� ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() << "�� ";
		cout << userList.getUserByName(currentUser.getName()).getLoseCount() << "���Դϴ�." << endl;
	}

	else
	{
		cout << "���� ����� �����ϴ�." << endl;
	}

	char a;
	cin >> a;
}


void IoHandler::printCurrentRecord(User currentUser)
{
	cout << "�̹� ���� ����� ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() << "�� ";
	cout << currentUser.getWinCount() << "�� ";
	cout << currentUser.getLoseCount() << "���Դϴ�." << endl;

	char a;
	cin >> a;
}


void IoHandler::printGameHeader(User currentUser)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName() << "�� ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() + 1;
	cout << "��° ������ �����߿� �ֽ��ϴ�. (�̹� ���� " << currentUser.getWinCount() << "�� ";
	cout << currentUser.getLoseCount() << "��)" << endl;
	cout << "====================================================" << endl;
}


void IoHandler::printMenuHeader(User currentUser)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName();
	cout << "�� ��� ������ �����ϰ� �ֽ��ϴ�. (�̹� ���� " << currentUser.getWinCount() << "�� ";
	cout << currentUser.getLoseCount() << "��)" << endl;
	cout << "====================================================" << endl;
}