#ifndef __IOHANDLER_H__
#define __IOHANDLER_H__

#include "StudentList.h"
#include "BookList.h"
#include "LendList.h"

#include <iostream>
#include <fstream>

class IoHandler
{
public :
	IoHandler() {};
	~IoHandler() {};

	//파일 load & save
	//string, int 입출력
	//std, book, lendList 출력

	void loadStd(string stdFile, StudentList &stdList);
	void loadBook(string bookFile, BookList &bookList);
	void loadLend(string lendFile, LendList &lendList);
	void saveLend(string lendFile, LendList &lendList);

	void putMsg(string msg);
	void putNum(int num);
	void putNewLine();

	int inputNum();
	string inputMsg();

	void printStd(Student const &std);
	void printBook(Book const &book);
	void printLendList(StudentList const &stdList, BookList const &bookList, LendList const &lendList);

	int putMenu();
};
#endif