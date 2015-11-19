#include "Taskmanager.h"

void Taskmanager::startServer(void* p, UserList &userList, WordList &wordList)
{
	SOCKET sock = (SOCKET)p;

	sendUserInfo(userList, sock);

	char buf[255] = { 0 };

	while (true)
	{
		recv(sock, buf, sizeof(buf), 0);
		switch (buf[0])
		{
		//���ӽ���
		case 'S':
		{

		}
		//�����������
		case 'I':
		{
			break;
		}
		//������������
		case 'H':
		{
			recv(sock, buf, sizeof(buf), 0);
		}
		//��ü������������
		case 'R':
		{

		}
		//����������
		case 'Q':
		{

		}
		//�ٷ�����
		case 'Z':
		{

		}
		default:
			break;
		}
	}
	//-----------���� �ݱ�---------------
	closesocket(sock);
}

void Taskmanager::sendUserInfo(UserList& userList, SOCKET& clntSock)
{
	char buf[255] = { 0 };

	while (true)
	{
		//-----------�����̸� ����------------
		recv(clntSock, buf, sizeof(buf), 0);

		string userName = buf;
		if (userList.isUserExist(userName))
		{
			send(clntSock, "T", 1, 0);
		}
		else
		{
			send(clntSock, "F", 1, 0);
			break;
		}

		recv(clntSock, buf, sizeof(buf), 0);

		if (buf[0] == 'L')
		{
			User user = userList.getUserByName(userName);
			send(clntSock, user.getName().c_str(), user.getName().size(), 0);
			itoa(user.getWinCount(), buf, 10);
			send(clntSock, buf, sizeof(buf), 0);
			itoa(user.getLoseCount(), buf, 10);
			send(clntSock, buf, sizeof(buf), 0);

			break;
		}
	}
}

void Taskmanager::sendRankInfo(UserList& userList, SOCKET& clntSock)
{

}

void Taskmanager::sendGameInfo(WordList& wordList, SOCKET& clntSock)
{
	
}