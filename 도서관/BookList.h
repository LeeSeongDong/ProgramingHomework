#ifndef __BOOKLIST_H__
#define __BOOKLIST_H__

#include "Book.h"

class BookList
{
private :
	int numOfBook;
	Book bookList[MAX_BOOK];

	bool isMax();

public :
	BookList()
	{
		numOfBook = 0;
	};
	~BookList() {};

	void insert(Book book);

	int getNumOfBook() const
	{
		return numOfBook;
	}
	int getIndexByNum(string bookNum) const;
	//int getIndexByName(string bookName) const;
	Book getBook(int index) const;

	int getNumOfBookByName(string bookName) const;
};
#endif