#include "Taskmanager.h"

#pragma warning(disable:4996);

int main()		//argv[1] : 사전파일명, argv[2] : 사용자파일명
{
	IoHandler ioh;

	WordList wordList;
	UserList userList;

	Taskmanager tm;
	HangmanGame hg;

	char menu;

	//-------소켓 라이브러리 불러오기(?)--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		ioh.putMsg("WSAStartup() Error\n");
		return 0;
	}

	//---------소켓생성-------- 
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//TCP를 이용한 소켓

	//---------서버 정보 입력--------------------
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;						// IP주소를 이용하고
	servAddr.sin_port = htons(4000);					// 소켓은 4000번에
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	// 서버의 ip 주소는 127.0.0.1

	//---------서버 연결------------
	retval = connect(servSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		ioh.putMsg("connect() Error\n");
		return 0;
	}

	char buf[255] = { 0 };
	ioh.putMsg("행맨 서버에 접속중...");

	tm.loadUser(userList, servSock);

	while (true)
	{
		ioh.printMenuHeader(tm.getCurrentUser());

		menu = tm.selectMenu(ioh.inputMenu(tm.getCurrentUser()), hg, userList, wordList);

		if (menu == 'Q' || menu == 'Z')
		{
			send(servSock, &menu, 1, 0);
			break;
		}
	}

	///////////////////////////////////////////////////
	//----------소켓 닫음------------------
	closesocket(servSock);

	//---------라이브러리 해제(?)---------
	WSACleanup();
}
