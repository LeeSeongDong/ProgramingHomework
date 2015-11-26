#include "Taskmanager.h"
#pragma warning(disable:4996)

void Taskmanager::startServer(SOCKET& sock)
{
	string userName = sendUserInfo(sock);

	char buf[255] = { 0 };

	while (true)
	{
		recv(sock, buf, sizeof(buf), 0);
		char menu = buf[0];

		switch (menu)
		{
		//게임시작
		case 'S':
		{
			sendGameInfo(sock);
			break;
		}
		//현재승패정보
		case 'I':
		{
			break;
		}
		//이전승패정보
		case 'H':
		{
			break;
		}
		//전체유저승패정보
		case 'R':
		{
			sendRankInfo(sock);
			break;
		}
		//저장후종료
		case 'Q':
		{
			saveAndQuit(sock);
			break;
		}
		//바로종료
		case 'Z':
		{
			dbh.userLogout(userName);
			break;
		}
		default:
			break;
		}

		if (menu == 'Q' || menu == 'Z')
		{
			break;
		}
	}
}

string Taskmanager::sendUserInfo(SOCKET& clntSock)
{
	char buf[255] = { 0 };
	string userName;
	MYSQL_ROW row;

	while (true)
	{
		//-----------유저이름 수신------------
		recv(clntSock, buf, sizeof(buf), 0);
		userName = buf;

		row = dbh.getRowByUserName(userName);
		if (row)
		{
			send(clntSock, "T", 1, 0);
		}
		else
		{
			send(clntSock, "F", 1, 0);

			dbh.insertUser(userName);
			dbh.userLogin(userName);
			break;
		}

		recv(clntSock, buf, sizeof(buf), 0);

		if (buf[0] == 'L')
		{
			if (row[4][0] == 'F')
			{
				send(clntSock, "T", 1, 0);
			}
			else
			{
				send(clntSock, "N", 1, 0);
				continue;
			}

			recv(clntSock, buf, sizeof(buf), 0);

			dbh.userLogin(userName);

			send(clntSock, userName.c_str(), userName.size(), 0);

			recv(clntSock, buf, sizeof(buf), 0);
			send(clntSock, row[1], sizeof(buf), 0);
			
			recv(clntSock, buf, sizeof(buf), 0);
			send(clntSock, row[2], sizeof(buf), 0);

			break;
		}
	}

	return userName;
}

void Taskmanager::sendRankInfo(SOCKET& clntSock)
{
	MYSQL_RES* result = dbh.getUsers();
	MYSQL_ROW* userList = dbh.resToRowArr(result);

	char buf[255] = { 0 };
	int numOfUser = (int)mysql_num_rows(result);
	itoa(numOfUser, buf, 10);

	send(clntSock, buf, sizeof(buf), 0);

	int sameRank = 0;

	for (int i = 0; i < numOfUser; ++i)
	{
		if (i != 0)
		{
			if (userList[i - 1][3] == userList[i][3])
			{
				sameRank += 1;
			}
			else
			{
				sameRank = 0;
			}
		}
		recv(clntSock, buf, sizeof(buf), 0);
		itoa(i + 1 - sameRank, buf, 10);
		send(clntSock, buf, sizeof(buf), 0);

		recv(clntSock, buf, sizeof(buf), 0);
		string name = userList[i][0];
		send(clntSock, name.c_str(), name.size(), 0);

		recv(clntSock, buf, sizeof(buf), 0);
		string win = userList[i][1];
		send(clntSock, win.c_str(), sizeof(win), 0);

		recv(clntSock, buf, sizeof(buf), 0);
		string lose = userList[i][2];
		send(clntSock, lose.c_str(), sizeof(lose), 0);

		recv(clntSock, buf, sizeof(buf), 0);
		string winningRate = userList[i][3];
		send(clntSock, winningRate.c_str(), winningRate.size(), 0);
	}
}

void Taskmanager::sendGameInfo( SOCKET& clntSock)
{
	MYSQL_ROW wordRow = dbh.getRandomWord();
	char buf[255] = { 0 };
	string word = wordRow[0];
	string meaning = wordRow[2];

	send(clntSock, word.c_str(), word.size(), 0);
	recv(clntSock, buf, sizeof(buf), 0);

	string partOfSpeech = wordRow[1];
	partOfSpeech = "[" + partOfSpeech + "]";

	send(clntSock, partOfSpeech.c_str(), partOfSpeech.size(), 0);
	recv(clntSock, buf, sizeof(buf), 0);

	send(clntSock, meaning.c_str(), meaning.size(), 0);
}

void Taskmanager::saveAndQuit(SOCKET& clntSock)
{
	char buf[255] = { 0 };
	string name, win, lose;

	send(clntSock, "next", 4, 0);

	recv(clntSock, buf, sizeof(buf), 0);
	name = buf;
	send(clntSock, "next", 4, 0);

	recv(clntSock, buf, sizeof(buf), 0);
	win = buf;
	send(clntSock, "next", 4, 0);

	recv(clntSock, buf, sizeof(buf), 0);
	lose = buf;
	send(clntSock, "next", 4, 0);

	dbh.updateUser(name, win, lose);
	dbh.userLogout(name);
}