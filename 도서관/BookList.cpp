#include "BookList.h"

bool BookList::isMax()
{
	if (numOfBook == MAX_BOOK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BookList::insert(Book book)
{
	if (!isMax())
	{
		bookList[numOfBook] = book;
		++numOfBook;
	}
}

//책번호와 일치하는 bookList의 index 반환
int BookList::getIndexByNum(string bookNum) const
{
	int index = EMPTY;

	for (int i = 0; i < numOfBook; ++i)
	{
		if (bookList[i].getBookNum().compare(bookNum) == 0)
		{
			index = i;
			break;
		}
	}

	return index;
}

/*
int BookList::getIndexByName(string bookName)
{
	int index = EMPTY;

	for (int i = 0; i < numOfBook; ++i)
	{
		if (bookList[i].getBookName().compare(bookName) == 0)
		{
			index = i;
			break;
		}
	}
}
*/

Book BookList::getBook(int index) const
{
	return bookList[index];
}

//bookName과 일치하는 책의 개수 반환
int BookList::getNumOfBookByName(string bookName) const
{
	int count = 0;

	for (int i = 0; i < numOfBook; ++i)
	{
		if (bookList[i].getBookName().compare(bookName) == 0)
		{
			++count;
		}
	}

	return count;
}