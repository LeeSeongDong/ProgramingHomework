#include "Taskmanager.h"

int main()		//argv[1] : �������ϸ�, argv[2] : ��������ϸ�
{
	IoHandler ioh;

	WordList wordList;
	UserList userList;

	Taskmanager tm;
	HangmanGame hg;

	char menu;

	//-------���� ���̺귯�� �ҷ�����(?)--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		ioh.putMsg("WSAStartup() Error\n");
		return 0;
	}

	//---------���ϻ���-------- 
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//TCP�� �̿��� ����

	//---------���� ���� �Է�--------------------
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;						// IP�ּҸ� �̿��ϰ�
	servAddr.sin_port = htons(4000);					// ������ 4000����
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	// ������ ip �ּҴ� 127.0.0.1

	//---------���� ����------------
	retval = connect(servSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		ioh.putMsg("connect() Error\n");
		return 0;
	}

	char buf[255] = { 0 };
	ioh.putMsg("������ ������...");

	//---------������ ����--------
	int sendsize = send(servSock, "con", strlen(buf), 0);

	//---------�����κ��� ��������, �ܾ����� ����-----------
	int recvsize = recv(servSock, buf, sizeof(buf), 0);

	//��������, �ܾ����� �޾Ƽ� userList, wordList�� ����
	//�������� ��ü�� ��� ������?

	///////////////////////////////////////////////////

	tm.loadUser(userList);

	while (true)
	{
		ioh.printMenuHeader(tm.getCurrentUser());

		menu = tm.selectMenu(ioh.inputMenu(tm.getCurrentUser()), hg, userList, wordList);

		if (menu == 'Q' || menu == 'Z')
		{
			break;
		}
	}

	//----------���� ����------------------
	closesocket(servSock);

	//---------���̺귯�� ����(?)---------
	WSACleanup();
}
