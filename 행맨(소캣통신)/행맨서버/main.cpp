#include "Taskmanager.h"

WordList wordList;
UserList userList;

unsigned WINAPI startServ(void* p)
{
	SOCKET sock = (SOCKET)p;
	Taskmanager tm;

	char buf[255] = { 0 };
	tm.startServer(sock, userList, wordList);

	//-----------���� �ݱ�---------------
	closesocket(sock);

	return 0;
}

int main()
{
	IoHandler ioh;

	//-----------�������� �ֽ�ȭ--------------
	//����, �������� �ε�
	ioh.loadWordFile("DICT.txt", wordList);
	ioh.loadUserFile("GAME_RECORD.txt", userList);


	//-------���� ���̺귯�� �ҷ�����(?)--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		printf("WSAStartup() Error\n");
		return 0;
	}
	//-------------------------------------------

	//----------���� ����--------------
	SOCKET servSock;
	servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock == SOCKET_ERROR)
	{
		printf("socket() Error\n");
		return 0;
	}
	//-----------------------------------

	//--------����(�ڽ�)�� ���� ���� �Է�------------
	SOCKADDR_IN serv_addr = { 0 };					// �ʱ�ȭ
	serv_addr.sin_family = AF_INET;					// IP ���
	serv_addr.sin_port = htons(4000);				// ��Ʈ 4000��
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// �ּҴ� �˾Ƽ� ã��
	//------------------------------------------------

	//-----------���ͳݿ� ����---------------------
	retval = ::bind(servSock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		printf("bind() Error\n");
		return 0;
	}
	//--------------------------------------------

	//-----------����ο� ����-----------------
	listen(servSock, 5);		// 5������� ����� �� �ְ� ��...
	//-------------------------------------------
	SOCKADDR_IN clnt_addr = { 0 };
	int size = sizeof(SOCKADDR_IN);

	cout << "��������" << endl;


	while (true)
	{
		//-------------Ŭ���̾�Ʈ ���� ���, connect�� �ϸ� ������-------------
		SOCKET sock = accept(servSock, (SOCKADDR*)&clnt_addr, &size);	
		if (sock == SOCKET_ERROR)
		{
			printf("accept() Error\n");
			continue;
		}

		cout << "Ŭ���̾�Ʈ ����\n" << endl;

		//-----------���� ������ ����-------------
		_beginthreadex(NULL, 0, startServ, (void*)sock, 0, NULL);
	}

	//----------���� ����---------------
	closesocket(servSock);

	//-------���̺귯�� ����---------
	WSACleanup();

	return 0;
}
