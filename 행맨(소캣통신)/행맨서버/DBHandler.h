#ifndef __DBHANDLER_H__
#define __DBHANDLER_H__

#include "Header.h"

class DBHandler
{
private :
	MYSQL mysql;
	MYSQL_ROW row;		

	void connect();
	float calWinningRate(int winCount, int loseCount);
public :
	DBHandler()
	{
		connect();
	};
	~DBHandler() {};

	MYSQL_ROW getRandomWord();
	MYSQL_ROW getRowByUserName(string name);
	MYSQL_RES* getUsers();
	MYSQL_ROW* resToRowArr(MYSQL_RES* res);

	void insertUser(string name);
	void deleteUser(string name);
	void updateUser(string name, string win, string lose);
	void userLogin(string name);
	void userLogout(string name);


};

#endif
