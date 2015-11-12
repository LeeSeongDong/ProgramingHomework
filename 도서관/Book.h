#ifndef __BOOK_H__
#define __BOOK_H__

#include "Header.h"

class Book
{
private :
	string bookNum;
	string bookName;

public :
	Book() {};
	Book(string loadBookNum, string loadBookName)
	{
		bookNum = loadBookNum;
		bookName = loadBookName;
	};
	~Book() {};

	string getBookNum() const
	{
		return bookNum;
	}
	string getBookName() const
	{
		return bookName;
	}

};
#endif