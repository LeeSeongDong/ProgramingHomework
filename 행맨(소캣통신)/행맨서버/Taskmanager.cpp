#include "Taskmanager.h"
#pragma warning(disable:4996)

void Taskmanager::startServer(SOCKET& sock)
{
	string userName = sendUserInfo(sock);

	cout << userName << "-- 접속" << endl;

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
			cout << userName << "-- 단어정보 요청" << endl;
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
			cout << userName << "-- 랭킹정보 요청" << endl;
			sendRankInfo(sock);
			break;
		}
		//저장후종료
		case 'Q':
		{
			cout << userName << "-- 기록저장 요청" << endl;
			saveAndQuit(sock);
			break;
		}
		//바로종료
		case 'Z':
		{
			unsaveAndQuit(userName);
			break;
		}
		default:
			break;
		}

		if (menu == 'Q' || menu == 'Z')
		{
			cout << userName << "-- 종료" << endl;
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

			send(clntSock, userName.c_str(), (int)userName.size(), 0);

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
			float f1 = (float)atof(userList[i - 1][3]);
			float f2 = (float)atof(userList[i][3]);

			if (f1 == f2)
			{
				sameRank += 1;
			}
			else
			{
				sameRank = 0;
			}
		}
		recv(clntSock, buf, sizeof(buf), 0);

		string msg;
		char intBuf[5] = { 0 };
		itoa(i - sameRank + 1, intBuf, 10);
		msg = intBuf;
		msg = msg + "#" + userList[i][0] + "#" + userList[i][1] + "#" + userList[i][2] + "#" + userList[i][3] + "@";

		send(clntSock, msg.c_str(), (int)msg.size(), 0);
	}
}

void Taskmanager::sendGameInfo( SOCKET& clntSock)
{
	MYSQL_ROW wordRow = dbh.getRandomWord();
	char buf[255] = { 0 };
	string word = wordRow[0];
	string meaning = wordRow[2];

	send(clntSock, word.c_str(), (int)word.size(), 0);
	recv(clntSock, buf, sizeof(buf), 0);

	string partOfSpeech = wordRow[1];
	partOfSpeech = "[" + partOfSpeech + "]";

	send(clntSock, partOfSpeech.c_str(), (int)partOfSpeech.size(), 0);
	recv(clntSock, buf, sizeof(buf), 0);

	send(clntSock, meaning.c_str(), (int)meaning.size(), 0);
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

void Taskmanager::unsaveAndQuit(string userName)
{
	MYSQL_ROW row = dbh.getRowByUserName(userName);
	int winCnt = atoi(row[1]);
	int loseCnt = atoi(row[2]);

	if (winCnt == 0 && winCnt == 0)
	{
		dbh.deleteUser(userName);
	}
	else
	{
		dbh.userLogout(userName);
	}
}