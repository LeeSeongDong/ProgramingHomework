#include "Taskmanager.h"

int main()		//argv[1] : �������ϸ�, argv[2] : ��������ϸ�
{
	IoHandler ioh;

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
	string ip = ioh.inputStr("������ IP�ּҸ� �Է��ϼ��� : ");
	int port = ioh.inputNum("������ ��Ʈ��ȣ�� �Է��ϼ��� : ");

	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;						// IP�ּҸ� �̿��ϰ�
	servAddr.sin_port = htons(port);					// ������ 4000����
	servAddr.sin_addr.s_addr = inet_addr(ip.c_str());	// ������ ip �ּҴ� 127.0.0.1

	//---------���� ����------------
	retval = connect(servSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		ioh.putMsg("connect() Error\n");
		return 0;
	}

	ioh.putMsg("��� ������ ������...");

	User currentUser = ioh.printUserMenu(servSock);

	tm.setCurrentUser(currentUser);

	while (true)
	{
		ioh.printMenuHeader(tm.getCurrentUser(), tm.getCurrentWin(), tm.getCurrentLose());

		menu = tm.selectMenu(ioh.inputMenu(tm.getCurrentUser()), hg, servSock);

		if (menu == 'Q' || menu == 'Z')
		{
			recv(servSock, &menu, 1, 0);
			break;
		}
	}

	///////////////////////////////////////////////////
	//----------���� ����------------------
	closesocket(servSock);

	//---------���̺귯�� ����(?)---------
	WSACleanup();
}
