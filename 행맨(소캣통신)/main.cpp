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
		//-----------클라이언트로부터 수신------------
		int recvsize = recv(sock, buf, sizeof(buf), 0);
		if (recvsize <= 0)
		{
			cout << "접속종료\n" << endl;
			break;
		}
		//------------------------------------------------
		buf[recvsize] = '\0';//유저이름

		//----------클라이언트에게 전송------------------
		int sendsize = send(sock, buf, strlen(buf), 0);
		if (sendsize <= 0)
			break;
		//-----------------------------------------------
	}
	//-----------소켓 닫기---------------
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
	//서버
	//socket(생성)
	//socket();
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serv_addr = { 0 };					// 초기화
	serv_addr.sin_family = AF_INET;					// IP 사용
	serv_addr.sin_port = htons(4000);				// 포트 4000번
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// 주소는 알아서 찾기

	//bind(ip, port번호 할당)
	//bind();
	if (bind(servSock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR)) != 0)
	{
		cout << "bind() Error\n" << endl;
		return 0;
	}

	//listen(소캣이 클라이언트의 연결요청을 받아들일수 있는 상태가 되게함)
	//listen();
	listen(servSock, 5);		// 5명까지만 대기할 수 있게 함

	SOCKADDR_IN clntAddr = { 0 };
	int size = sizeof(SOCKADDR_IN);

	//accept(클라이언트의 연결요청을 수락함)
	//accept();
	while (true)
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &size);
		if (clntSock == SOCKET_ERROR)
		{
			cout << "accept() Error\n" << endl;
			continue;
		}
		cout << "클라이언트 접속\n" << endl;

		Client c(clntSock);

		//-----------수신 스레드 생성-------------
		thread t(&tm.loadUser, userList);
	}

	//클라이언트
	//connect(연결요청)
	//connect();

	//closesocket(소켓종료)
	//closesocket();

	//----------소켓 닫음---------------
	closesocket(servSock);

	//-------라이브러리 해제---------
	WSACleanup();

	return 0;
}