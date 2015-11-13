#include "IoHandler.h"

void startHangman(void* p, UserList &userList, WordList &wordList)
{
	SOCKET sock = (SOCKET)p;
	char buf[256];

	while (true)
	{
		//-----------�����̸� ����------------
		int recvsize = recv(sock, buf, sizeof(buf), 0);
		buf[recvsize] = '\0';

		string userName = buf;

		//----------Ŭ���̾�Ʈ���� ����------------------
		int sendsize = send(sock, buf, strlen(buf), 0);
	}

	//-----------���� �ݱ�---------------
	closesocket(sock);
}

int main()
{
	IoHandler ioh;

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
	if(bind(servSock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR)))
	{
		cout << "bind() Error\n" << endl;
		return 0;
	}
	*/

	//listen ��Ĺ�� Ŭ���̾�Ʈ�� �����û�� �޾Ƶ��ϼ� �ִ� ���°� �ǰ���
	listen(servSock, 5);		// 5������� ����� �� �ְ� ��

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
		thread t(&startHangman, clntSock, userList, wordList);
	}

	//----------���� ����---------------
	closesocket(servSock);

	//-------���̺귯�� ����---------
	WSACleanup();

	return 0;
}
