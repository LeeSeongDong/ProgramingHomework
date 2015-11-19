#include "Taskmanager.h"

void startHangman(void* p, UserList &userList, WordList &wordList)
{
	SOCKET sock = (SOCKET)p;
	char buf[255];

	while (true)
	{
		//-----------�����̸� ����------------
		recv(sock, buf, sizeof(buf), 0);
	
		string userName = buf;
		if(userList.isUserExist(userName))
		{
			send(sock, "T", 1, 0);
		}
		else
		{
			send(sock, "F", 1, 0);
			break;
		}

		recv(sock, buf, sizeof(buf), 0);

		if (buf[0] == 'L')
		{
			User user = userList.getUserByName(userName);
			send(sock, user.getName().c_str(), user.getName().size(), 0);
			itoa(user.getWinCount(), buf, 10);
			send(sock, buf, sizeof(buf), 0);
			itoa(user.getLoseCount(), buf, 10);
			send(sock, buf, sizeof(buf), 0);
			
			break;
		}
	}

	//-----------���� �ݱ�---------------
	closesocket(sock);
}

int main()
{
	IoHandler ioh;

	Taskmanager tm;
	WordList wordList;
	UserList userList;

	//����, �������� �ε�
	ioh.loadWordFile("DICT.txt"/*argv[1]*/, wordList);
	ioh.loadUserFile("GAME_RECORD.txt"/*argv[2]*/, userList);
	userList.setUserWinningRate();
	userList.sortByWinningRate();

	WSADATA wsaData;
	SOCKADDR_IN servAddr, clntADDR;

	int szClntAddr;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup() error!" << endl;
	}

	//����
	//socket(����)
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serv_addr = { 0 };					// �ʱ�ȭ
	serv_addr.sin_family = AF_INET;					// IP ���
	serv_addr.sin_port = htons(4000);				// ��Ʈ 4000��
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// �ּҴ� �˾Ƽ� ã��

	//bind(ip, port��ȣ �Ҵ�)
	bind(servSock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR));
	
	/*
	if(bind(servSock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR)) 0)
	{
		cout << "bind() Error\n" << endl;
		return 0;
	}
	*/

	//listen ��Ĺ�� Ŭ���̾�Ʈ�� �����û�� �޾Ƶ��ϼ� �ִ� ���°� �ǰ���
	listen(servSock, 10);		// 10������� ����� �� �ְ� ��

	SOCKADDR_IN clntAddr = { 0 };
	int size = sizeof(SOCKADDR_IN);

	//accept(Ŭ���̾�Ʈ�� �����û�� ������)
	while (true)
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &size);
		if (clntSock == SOCKET_ERROR)
		{
			cout << "accept() Error\n" << endl;
			continue;
		}
		cout << "Ŭ���̾�Ʈ ����\n" << endl;
		//-----------���� ������ ����-------------
		thread t(&tm.startServer, clntSock, userList, wordList);
	}

	//----------���� ����---------------
	closesocket(servSock);

	//-------���̺귯�� ����---------
	WSACleanup();

	return 0;
}
