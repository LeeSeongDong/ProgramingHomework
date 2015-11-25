#include "Taskmanager.h"
#pragma warning(disable:4996)

void Taskmanager::startServer(SOCKET& sock, UserList &userList, WordList &wordList)
{
	IoHandler ioh;
	string userName = sendUserInfo(userList, sock);

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
			sendGameInfo(wordList, sock);
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
			sendRankInfo(userList, sock);
			break;
		}
		//저장후종료
		case 'Q':
		{
			saveAndQuit(userList, sock);
			ioh.saveUserFile("GAME_RECORD.txt", userList);
			break;
		}
		//바로종료
		case 'Z':
		{
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

	userList.logout(userName);
}

string Taskmanager::sendUserInfo(UserList& userList, SOCKET& clntSock)
{
	char buf[255] = { 0 };
	string userName;

	while (true)
	{
		//-----------유저이름 수신------------
		recv(clntSock, buf, sizeof(buf), 0);
		userName = buf;

		if (userList.isUserExist(userName))
		{
			send(clntSock, "T", 1, 0);
		}
		else
		{
			send(clntSock, "F", 1, 0);

			User newUser(userName, 0, 0);
			newUser.login();
			newUser.setWinningRate();
			userList.insertUser(newUser);
			break;
		}

		recv(clntSock, buf, sizeof(buf), 0);

		if (buf[0] == 'L')
		{
			if (!userList.getUserByName(userName).isLogin())
			{
				send(clntSock, "T", 1, 0);
			}
			else
			{
				send(clntSock, "N", 1, 0);
				continue;
			}

			recv(clntSock, buf, sizeof(buf), 0);

			userList.login(userName);

			User user = userList.getUserByName(userName);
			send(clntSock, user.getName().c_str(), user.getName().size(), 0);

			recv(clntSock, buf, sizeof(buf), 0);
			itoa(user.getWinCount(), buf, 10);
			send(clntSock, buf, sizeof(buf), 0);
			
			recv(clntSock, buf, sizeof(buf), 0);
			itoa(user.getLoseCount(), buf, 10);
			send(clntSock, buf, sizeof(buf), 0);

			break;
		}
	}

	return userName;
}

void Taskmanager::sendRankInfo(UserList& userList, SOCKET& clntSock)
{
	userList.setUserWinningRate();
	userList.sortByWinningRate();

	char buf[255] = { 0 };
	int numOfUser = userList.getSize();
	itoa(numOfUser, buf, 10);

	send(clntSock, buf, sizeof(buf), 0);

	int sameRank = 0;

	for (int i = 0; i < numOfUser; ++i)
	{
		User user = userList.getUserByIndex(i);

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
		recv(clntSock, buf, sizeof(buf), 0);
		itoa(i + 1 - sameRank, buf, 10);
		send(clntSock, buf, sizeof(buf), 0);

		recv(clntSock, buf, sizeof(buf), 0);
		string name = user.getName();
		send(clntSock, name.c_str(), name.size(), 0);

		recv(clntSock, buf, sizeof(buf), 0);
		itoa(user.getWinCount(), buf, 10);
		send(clntSock, buf, sizeof(buf), 0);

		recv(clntSock, buf, sizeof(buf), 0);
		itoa(user.getLoseCount(), buf, 10);
		send(clntSock, buf, sizeof(buf), 0);

		recv(clntSock, buf, sizeof(buf), 0);
		string winningRate = to_string(user.getWinningRate());
		send(clntSock, winningRate.c_str(), winningRate.size(), 0);
	}
}

void Taskmanager::sendGameInfo(WordList& wordList, SOCKET& clntSock)
{
	srand((unsigned int)time(NULL));
	int numOfWord = wordList.getWordListSize();
	Word word = wordList.getWordByIndex(rand()%numOfWord);
	char buf[255] = { 0 };

	send(clntSock, word.getWordName().c_str(), word.getWordName().size(), 0);
	recv(clntSock, buf, sizeof(buf), 0);

	send(clntSock, word.getPartOfSpeech().c_str(), word.getPartOfSpeech().size(), 0);
	recv(clntSock, buf, sizeof(buf), 0);

	send(clntSock, word.getMeaning().c_str(), word.getMeaning().size(), 0);
}

void Taskmanager::saveAndQuit(UserList& userList, SOCKET& clntSock)
{
	char buf[255] = { 0 };
	string name;
	int win, lose;

	send(clntSock, "next", 4, 0);

	recv(clntSock, buf, sizeof(buf), 0);
	name = buf;
	send(clntSock, "next", 4, 0);

	recv(clntSock, buf, sizeof(buf), 0);
	win = atoi(buf);
	send(clntSock, "next", 4, 0);

	recv(clntSock, buf, sizeof(buf), 0);
	lose = atoi(buf);
	send(clntSock, "next", 4, 0);

	userList.saveRecord(name, win, lose);
	userList.logout(name);
}