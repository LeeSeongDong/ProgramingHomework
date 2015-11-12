#ifndef __LEND_H__
#define __LEND_H__

#include "Header.h"

class Lend
{
private :
	int stdNum;
	string bookNum;

public :
	Lend() {};
	Lend(int loadStdNum, string loadBookNum)
	{
		stdNum = loadStdNum;
		bookNum = loadBookNum;
	};
	~Lend() {};

	int getStdNum() const
	{
		return stdNum;
	}
	string getBookNum() const
	{
		return bookNum;
	}

	void setLend(int stdNum, string bookNum)
	{
		this->stdNum = stdNum;
		this->bookNum = bookNum;
	}
};
#endif