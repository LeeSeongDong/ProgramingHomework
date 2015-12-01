#include "Taskmanager.h"

unsigned WINAPI startServ(void* p)
{
	SOCKET sock = (SOCKET)p;
	Taskmanager tm;

	char buf[255] = { 0 };
	tm.startServer(sock);

	//-----------소켓 닫기---------------
	closesocket(sock);

	return 0;
}

int main()
{
	//-------소켓 라이브러리 불러오기(?)--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		printf("WSAStartup() Error\n");
		return 0;
	}
	//-------------------------------------------

	//----------소켓 생성--------------
	SOCKET servSock;
	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == SOCKET_ERROR)
	{
		printf("socket() Error\n");
		return 0;
	}
	//-----------------------------------
	
	//--------서버(자신)의 소켓 정보 입력------------
	SOCKADDR_IN serv_addr = { 0 };					// 초기화
	serv_addr.sin_family = AF_INET;					// IP 사용
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// 주소는 알아서 찾기
	serv_addr.sin_port = htons(1111);				// 포트 1111번
	//------------------------------------------------

	//-----------인터넷에 연결---------------------
	retval = ::bind(servSock, (SOCKADDR*)&serv_addr, sizeof(serv_addr));
	if (retval == SOCKET_ERROR)
	{
		printf("bind() Error\n");
		return 0;
	}
	//--------------------------------------------

	//-----------대기인원 설정-----------------
	listen(servSock, 5);		// 5명까지 대기
	//-------------------------------------------
	SOCKADDR_IN clnt_addr;// = { 0 };
	int size = sizeof(clnt_addr);

	cout << "서버가동" << endl;


	while (true)
	{
		//-------------클라이언트 접속 대기, connect를 하면 리턴함-------------
		SOCKET sock = accept(servSock, (SOCKADDR*)&clnt_addr, &size);	
		if (sock == SOCKET_ERROR)
		{
			printf("accept() Error\n");
			continue;
		}

		cout << "클라이언트 접속\n";

		//-----------수신 스레드 생성-------------
		_beginthreadex(NULL, 0, startServ, (void*)sock, 0, NULL);
	}

	//----------소켓 닫음---------------
	closesocket(servSock);

	//-------라이브러리 해제---------
	WSACleanup();

	return 0;
}
