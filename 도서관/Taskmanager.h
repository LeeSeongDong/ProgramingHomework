#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "IoHandler.h"

class Taskmanager
{
private :
	StudentList stdList;
	BookList bookList;
	LendList lendList;

	bool isExist(int stdNum, string bookName);
	bool isLendable(int stdNum, string bookName);
	bool isReturnable(int stdNum, string bookName);

	int findNumOfLendBook(string bookName);
	int findNumOfLendBook(int stdNum);
	int findIndexLendableBook(string bookName);
	int findLendIndex(int stdNum, string bookName);

public :
	Taskmanager(StudentList &stdList, BookList &bookList, LendList &lendList)
	{
		this->stdList = stdList;
		this->bookList = bookList;
		this->lendList = lendList;
	};
	~Taskmanager() {};

	void lendBook(int stdNum, string bookName);
	void returnBook(int stdNum, string bookName);
	void printLendList();
	void saveLendList(string lendFile);
};
#endif