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

User IoHandler::printUserMenu(SOCKET& servSock)
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

		while (std::cin.get() != '\n');	//입력버퍼 지우기
		getline(cin, userName);

		char buf[255] = { 0 };
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

				if (buf[0] == 'N')
				{
					cout << "이미 게임중인 사용자입니다." << endl;

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
				send(servSock, "a", 1, 0);
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

		cout << rank << "등 : " << name;
		cout << "( " << win + lose << "전 ";
		cout << win << "승. ";
		cout << "승률 " << winningRate << "% )";
		cout << endl << endl;
	}

	cin >> a;
}

void IoHandler::printPreviousRecord(User& currentUser)
{
	if (currentUser.getLoseCount() != 0 || currentUser.getWinCount() != 0)
	{
		cout << "이전 게임 기록은 ";
		cout << currentUser.getWinCount() + currentUser.getLoseCount() << "전 ";
		cout << currentUser.getWinCount() << "승 ";
		cout << currentUser.getLoseCount() << "패입니다." << endl;
	}

	else
	{
		cout << "이전 기록이 없습니다." << endl;
	}

	char a;
	cin >> a;
}

void IoHandler::printCurrentRecord(int win, int lose)
{
	cout << "이번 게임 기록은 ";
	cout << win + lose << "전 ";
	cout << win << "승 ";
	cout << lose << "패입니다." << endl;

	char a;
	cin >> a;
}

void IoHandler::printGameHeader(User& currentUser, int win, int lose)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName() << "의 ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() + 1;
	cout << "번째 게임이 수행중에 있습니다. (이번 게임 " << win << "승 ";
	cout << lose << "패)" << endl;
	cout << "====================================================" << endl;
}

void IoHandler::printMenuHeader(User& currentUser, int win, int lose)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName();
	cout << "이 행맨 게임을 수행하고 있습니다. (이번 게임 " << win << "승 ";
	cout << lose << "패)" << endl;
	cout << "====================================================" << endl;
}
