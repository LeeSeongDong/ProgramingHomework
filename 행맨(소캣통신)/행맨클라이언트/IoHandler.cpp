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

	cout << "새 게임을 시작하려면 “S”를" << endl;
	cout << "본인의 이번 게임 점수를 보려면 “I”를" << endl;
	cout << "본인의 이전 게임 점수를 보려면 “H”를" << endl;
	cout << "전체 사용자의 등수를 보려면 “R”을" << endl;
	cout << "이번 게임 결과를 저장하고 종료하려면 “Q”를" << endl;
	cout << "이번 게임 결과를 저장하지 않고 종료하려면 “Z”를 입력하시오 [S/I/H/R/Q/Z] : ";
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
		cout << "|    /|＼" << endl;
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
		cout << "|    / ＼" << endl;
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
		cout << "                 행맨게임을 시작합니다.             " << endl;
		cout << "====================================================" << endl;

		cout << "(기록해 둔 게임 성적을 load되거나 새로운 사용자가 등록됩니다.)" << endl;
		cout << "사용자의 이름을 입력하세요 : ";
		cin >> userName;
		//getline(cin, userName);

		char buf[255];
		send(servSock, userName.c_str(), userName.size(), 0);	//유저정보요청
		recv(servSock, buf, sizeof(buf), 0);

		cout << endl << endl;

		if (buf[0] == 'T')
		{
			cout << "등록된 사용자가 있습니다. 등록된 사용자의 게임 성적을 load하려면 L을, " << endl;
			cout << "새로운 사용자 이름을 등록하려면 N을 입력하세요 [L/N] : ";
			cin >> a;

			cout << endl << endl;

			if (a == 'L' || a == 'l')
			{
				send(servSock, "L", 1, 0);	//불러오기요청

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

				cout << "기존 사용자 [" << userName << "]을/를 불러옵니다. ";
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
				cout << "L 또는 N을 입력하세요." << endl;
				cin >> a;
				continue;
			}
		}

		else
		{
			User user(userName);
			currentUser = user;

			cout << "새로운 사용자 [" << userName << "]을/를 불러옵니다. ";

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
		cout << i + 1 - sameRank << "등 : " << userList.getUserByIndex(i).getName();
		cout << "( " << userList.getUserByIndex(i).getWinCount() + userList.getUserByIndex(i).getLoseCount() << "전 ";
		cout << userList.getUserByIndex(i).getWinCount() << "승. ";
		cout << "승률 " << userList.getUserByIndex(i).getWinningRate() << "% )";
		cout << endl << endl;

	}

	cin >> a;
}


void IoHandler::printPreviousRecord(UserList &userList, User currentUser)
{
	if (userList.isUserExist(currentUser.getName()) == true)
	{
		cout << "이전 게임 기록은 ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() + userList.getUserByName(currentUser.getName()).getLoseCount() << "전 ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() << "승 ";
		cout << userList.getUserByName(currentUser.getName()).getLoseCount() << "패입니다." << endl;
	}

	else
	{
		cout << "이전 기록이 없습니다." << endl;
	}

	char a;
	cin >> a;
}


void IoHandler::printCurrentRecord(User currentUser)
{
	cout << "이번 게임 기록은 ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() << "전 ";
	cout << currentUser.getWinCount() << "승 ";
	cout << currentUser.getLoseCount() << "패입니다." << endl;

	char a;
	cin >> a;
}


void IoHandler::printGameHeader(User currentUser)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName() << "의 ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() + 1;
	cout << "번째 게임이 수행중에 있습니다. (이번 게임 " << currentUser.getWinCount() << "승 ";
	cout << currentUser.getLoseCount() << "패)" << endl;
	cout << "====================================================" << endl;
}


void IoHandler::printMenuHeader(User currentUser)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName();
	cout << "이 행맨 게임을 수행하고 있습니다. (이번 게임 " << currentUser.getWinCount() << "승 ";
	cout << currentUser.getLoseCount() << "패)" << endl;
	cout << "====================================================" << endl;
}