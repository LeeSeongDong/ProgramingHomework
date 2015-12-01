#include "Taskmanager.h"

int main()
{
	IoHandler ioh;

	Taskmanager tm;
	HangmanGame hg;

	char menu;

	//-------소켓 라이브러리 불러오기--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		ioh.putMsg("WSAStartup() Error\n");
		return 0;
	}

	//---------소켓생성-------- 
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0);	//TCP를 이용한 소켓

	//---------서버 정보 입력--------------------
	string ip = ioh.inputStr("서버의 IP주소를 입력하세요 : ");
	int port = ioh.inputNum("서버의 포트번호를 입력하세요 : ");

	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;						// IP주소를 이용
	servAddr.sin_addr.s_addr = inet_addr(ip.c_str());	// 서버의 ip주소
	servAddr.sin_port = htons(port);					// 소켓

	//---------서버 연결------------
	retval = connect(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	if (retval == SOCKET_ERROR)
	{
		ioh.putMsg("connect() Error\n");
		return 0;
	}

	ioh.putMsg("행맨 서버에 접속중...");

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
	//----------소켓 닫음------------------
	closesocket(servSock);

	//---------라이브러리 해제---------
	WSACleanup();

	system("pause");
}
