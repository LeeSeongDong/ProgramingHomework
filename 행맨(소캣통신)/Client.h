#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "Header.h"

class Client
{
private :
	SOCKET socket;

public :
	Client(SOCKET socket) { setSocket(socket); };
	~Client() {};

	void setSocket(SOCKET socket)
	{
		this->socket = socket;
	}
	SOCKET getSocket()
	{
		return socket;
	}

};

#endif
