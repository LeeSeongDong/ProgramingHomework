#include "Taskmanager.h"
#include "Client.h"

void startHangman(void* p, )
{
	IoHandler ioh;

	Taskmanager tm;
	HangmanGame hg;

	WordList wordList;
	UserList userList;

	char menu;

	ioh.loadWordFile("DICT.txt"/*argv[1]*/, wordList);
	ioh.loadUserFile("GAME_RECORD.txt"/*argv[2]*/, userList);
	userList.setUserWinningRate();
	userList.sortByWinningRate();

	while (true)
	{
		ioh.printMenuHeader(tm.getCurrentUser());

		menu = tm.selectMenu(ioh.inputMenu(tm.getCurrentUser()), hg, userList, wordList, "GAME_RECORD.txt"/*argv[2]*/);

		if (menu == 'Q' || menu == 'Z')
		{
			return 0;
		}
	}
	while (true)
	{
		//-----------Ŭ���̾�Ʈ�κ��� ����------------
		int recvsize = recv(sock, buf, sizeof(buf), 0);
		if (recvsize <= 0)
		{
			cout << "��������\n" << endl;
			break;
		}
		//------------------------------------------------
		buf[recvsize] = '\0';//�����̸�

		//----------Ŭ���̾�Ʈ���� ����------------------
		int sendsize = send(sock, buf, strlen(buf), 0);
		if (sendsize <= 0)
			break;
		//-----------------------------------------------
	}
	//-----------���� �ݱ�---------------
	closesocket(sock);
	//------------------------------------
}

int main()
{
	WSADATA wsaData;
	SOCKADDR_IN servAddr, clntADDR;

	int szClntAddr;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup() error!" << endl;
	}
	//����
	//socket(����)
	//socket();
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serv_addr = { 0 };					// �ʱ�ȭ
	serv_addr.sin_family = AF_INET;					// IP ���
	serv_addr.sin_port = htons(4000);				// ��Ʈ 4000��
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// �ּҴ� �˾Ƽ� ã��

	//bind(ip, port��ȣ �Ҵ�)
	//bind();
	if (bind(servSock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR)) != 0)
	{
		cout << "bind() Error\n" << endl;
		return 0;
	}

	//listen(��Ĺ�� Ŭ���̾�Ʈ�� �����û�� �޾Ƶ��ϼ� �ִ� ���°� �ǰ���)
	//listen();
	listen(servSock, 5);		// 5������� ����� �� �ְ� ��

	SOCKADDR_IN clntAddr = { 0 };
	int size = sizeof(SOCKADDR_IN);

	//accept(Ŭ���̾�Ʈ�� �����û�� ������)
	//accept();
	while (true)
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &size);
		if (clntSock == SOCKET_ERROR)
		{
			cout << "accept() Error\n" << endl;
			continue;
		}
		cout << "Ŭ���̾�Ʈ ����\n" << endl;

		Client c(clntSock);

		//-----------���� ������ ����-------------
		thread t(&tm.loadUser, userList);
	}

	//Ŭ���̾�Ʈ
	//connect(�����û)
	//connect();

	//closesocket(��������)
	//closesocket();

	//----------���� ����---------------
	closesocket(servSock);

	//-------���̺귯�� ����---------
	WSACleanup();

	return 0;
}