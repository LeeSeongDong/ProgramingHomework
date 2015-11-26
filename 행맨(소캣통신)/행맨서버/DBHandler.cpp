#include "DBHandler.h"

void DBHandler::connect()
{
	mysql_init(&mysql);

	if (!mysql_real_connect(&mysql, NULL, "root", "kudse5014", NULL, 3306, NULL, 0))
	{
		cout << "데이터베이스 연결 실패!" << endl;
	}
	else
	{
		cout << "데이터베이스 연결 성공!" << endl;
		mysql_select_db(&mysql, "hangman");
	}
}

float DBHandler::calWinningRate(int winCount, int loseCount)
{
	float winningRate;
	float win = (float)winCount;
	float lose = (float)loseCount;

	int temp;

	if ((win + lose) == 0 || win == 0)
	{
		return 0;
	}
	else if (lose == 0)
	{
		return 100.000;
	}

	winningRate = win / (win + lose);

	//소수 셋째자리에서 반올림
	winningRate = winningRate * 100000;
	temp = (int)winningRate;

	if (temp % 10 >= 5)
	{
		temp += 10;
		temp = temp / 10;

		winningRate = (float)temp / 100;
	}
	else
	{
		temp = temp / 10;
		winningRate = (float)temp / 100;
	}

	return winningRate;
}

MYSQL_ROW DBHandler::getRandomWord()
{
	MYSQL_RES *result;
	mysql_query(&mysql, "select * from word order by rand() limit 1");

	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);

	return row;
}

MYSQL_ROW DBHandler::getRowByUserName(string name)
{
	MYSQL_RES* result;
	string query = "select * from user where name='" + name + "'";

	mysql_query(&mysql, query.c_str());

	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);

	return row;
}

MYSQL_RES* DBHandler::getUsers()
{
	MYSQL_RES *result;
	mysql_query(&mysql, "select * from user order by winningRate DESC");

	result = mysql_store_result(&mysql);
	return result;
}

MYSQL_ROW* DBHandler::resToRowArr(MYSQL_RES* res)
{
	MYSQL_ROW* rowArr;
	int numOfArr = (int)mysql_num_rows(res);
	
	rowArr = new MYSQL_ROW[numOfArr];
	for (int i = 0; i < numOfArr; ++i)
	{
		rowArr[i] = mysql_fetch_row(res);
	}

	return rowArr;
}

void DBHandler::insertUser(string name)
{
	string query = "insert into user (name) values ('" + name + "')";
	mysql_query(&mysql, query.c_str());
}

void DBHandler::updateUser(string name, string win, string lose)
{
	int intWin = atoi(win.c_str());
	int intLose = atoi(lose.c_str());

	float winningRate = calWinningRate(intWin, intLose);
	string strWinningRate = to_string(winningRate);

	string query = "update user set win='" + win + "', lose='" + lose + "', winningRate='" + strWinningRate + "' where name='" + name + "'";
	mysql_query(&mysql, query.c_str());
}

void DBHandler::userLogin(string name)
{
	string query = "update user set loginFlag='T' where name='" + name + "'";
	mysql_query(&mysql, query.c_str());
}

void DBHandler::userLogout(string name)
{
	string query = "update user set loginFlag='F' where name='" + name + "'";
	mysql_query(&mysql, query.c_str());
}
