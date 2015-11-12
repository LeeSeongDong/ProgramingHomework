#include "Taskmanager.h"

bool Taskmanager::isExist(int stdNum, string bookName)
{
	IoHandler ioh;

	int stdIndex = stdList.getIndex(stdNum);

	if (stdIndex == EMPTY)
	{
		ioh.putMsg("없는 학생입니다.");
		ioh.putNewLine();
		return false;
	}
	else if (bookList.getNumOfBookByName(bookName) == 0)
	{
		ioh.putMsg("없는 책입니다.");
		ioh.putNewLine();
		return false;
	}
	else
	{
		return true;
	}
}

bool Taskmanager::isLendable(int stdNum, string bookName)
{
	//학생, 책이 있는지
	//남아있는 책이 있는지
	//빌려간책 2권 이하인지
	//이미 빌려간책인지

	if ( !isExist(stdNum, bookName))
	{
		return false;
	}

	IoHandler ioh;

	if (bookList.getNumOfBookByName(bookName) <= findNumOfLendBook(bookName))
	{
		ioh.putMsg("모든 ");
		ioh.putMsg(bookName);
		ioh.putMsg("책이 대출중입니다.");
		ioh.putNewLine();

		return false;
	}
	else if (findNumOfLendBook(stdNum) >= MAX_LEND)
	{
		int stdIndex = stdList.getIndex(stdNum);

		ioh.printStd(stdList.getStudent(stdIndex));
		ioh.putMsg("은/는 이미 ");
		ioh.putNum(MAX_LEND);
		ioh.putMsg("권의 책을 대출중입니다.");
		ioh.putNewLine();

		return false;
	}
	else if (findLendIndex(stdNum, bookName) != EMPTY)
	{
		ioh.putMsg("이미 빌려간 책입니다.");
		ioh.putNewLine();
		return false;
	}
	else
	{
		return true;
	}
}

bool Taskmanager::isReturnable(int stdNum, string bookName)
{
	//학생, 책이 있는지
	//빌려간책이 맞는지

	if ( !isExist(stdNum, bookName) )
	{
		return false;
	}

	IoHandler ioh;

	if (findLendIndex(stdNum, bookName) == EMPTY)
	{
		ioh.putMsg("빌리지 않은 책입니다.");
		ioh.putNewLine();
		return false;
	}
	else
	{
		return true;
	}
}

//책이름으로 빌려간 책개수 찾기
int Taskmanager::findNumOfLendBook(string bookName)
{
	int count = 0;

	int bookCount = bookList.getNumOfBookByName(bookName);

	//bookList에서 책이름으로 책번호 찾기
	for (int i = 0; i < bookList.getNumOfBook(); ++i)
	{
		if (bookList.getBook(i).getBookName().compare(bookName) == 0)
		{
			string bookNum = bookList.getBook(i).getBookNum();

			//찾은 책번호가 lendList에 있는지 찾기
			for (int j = 0; j < lendList.getNumOfLend(); ++j)
			{
				if (lendList.getLend(j).getBookNum().compare(bookNum) == 0)
				{
					++count;
					break;
				}
			}
		}

		if (bookCount == count)
		{
			break;
		}
	}

	return count;
}

//학번으로 빌려간 책개수 찾기
int Taskmanager::findNumOfLendBook(int stdNum)
{
	int count = 0;

	for (int i = 0; i < lendList.getNumOfLend(); ++i)
	{
		if (stdNum == lendList.getLend(i).getStdNum())
		{
			++count;
		}
	}

	return count;
}

//책이름으로 빌릴수있는 bookIndex 찾기
int Taskmanager::findIndexLendableBook(string bookName)
{
	int bookIndex = EMPTY;

	//bookList에서 책이름으로 책번호 찾기
	for (int i = 0; i < bookList.getNumOfBook(); ++i)
	{
		if (bookList.getBook(i).getBookName().compare(bookName) == 0)
		{
			int count = 0;

			string bookNum = bookList.getBook(i).getBookNum();

			//찾은 책번호가 lendList에 있는지 찾기
			for (int j = 0; j < lendList.getNumOfLend(); ++j)
			{
				if (lendList.getLend(j).getBookNum().compare(bookNum) == 0)
				{
					++count;
					break;
				}
			}

			//lendList에 없으면 그 bookIndex 반환
			if (count == 0)
			{
				bookIndex = i;
				break;
			}
		}
	}

	return bookIndex;
}

//booklist에서 bookName으로 bookNum찾고
//lendList에서 stdNum, bookNum 모두 일치하는 lendIndex 찾기
int Taskmanager::findLendIndex(int stdNum, string bookName)
{
	int lendIndex = EMPTY;

	for (int i = 0; i < bookList.getNumOfBook(); ++i)
	{
		//bookList에서 bookName과 일치하는 bookNum찾음
		if (bookList.getBook(i).getBookName().compare(bookName) == 0)
		{
			string bookNum = bookList.getBook(i).getBookNum();

			for (int j = 0; j < lendList.getNumOfLend(); ++j)
			{
				//lendList에서 bookNum와 stdNum 모두 일치하는 lendList의 index찾기
				if (lendList.getLend(j).getStdNum() == stdNum && lendList.getLend(j).getBookNum().compare(bookNum) == 0)
				{
					lendIndex = j;
				}
			}
		}
	}

	return lendIndex;
}

void Taskmanager::lendBook(int stdNum, string bookName)
{
	IoHandler ioh;

	if ( !isLendable(stdNum, bookName) )
	{
		return;
	}
	else
	{
		int stdIndex = stdList.getIndex(stdNum);
		int bookIndex = findIndexLendableBook(bookName);
		string bookNum = bookList.getBook(bookIndex).getBookNum();
		Lend lend(stdNum, bookNum);

		lendList.insert(lend);

		ioh.printStd(stdList.getStudent(stdIndex));
		ioh.putMsg("이/가 ");
		ioh.printBook(bookList.getBook(bookIndex));
		ioh.putMsg("을/를 대출하였습니다.");
		ioh.putNewLine();
	}
}

void Taskmanager::returnBook(int stdNum, string bookName)
{
	IoHandler ioh;
	if ( !isReturnable(stdNum, bookName) )
	{
		return;
	}
	else
	{
		int stdIndex = stdList.getIndex(stdNum);
		int lendIndex = findLendIndex(stdNum, bookName);

		string bookNum = lendList.getLend(lendIndex).getBookNum();
		int bookIndex = bookList.getIndexByNum(bookNum);
		lendList.deleteLend(lendIndex);

		ioh.printStd(stdList.getStudent(stdIndex));
		ioh.putMsg("이/가 ");
		ioh.printBook(bookList.getBook(bookIndex));
		ioh.putMsg("을/를 반납하였습니다.");
		ioh.putNewLine();
	}
}

void Taskmanager::printLendList()
{
	IoHandler ioh;
	if ( !lendList.isSort() )
	{
		lendList.sort();
	}

	ioh.printLendList(stdList, bookList, lendList);
}

void Taskmanager::saveLendList(string lendFile)
{
	IoHandler ioh;

	ioh.saveLend(lendFile, lendList);
}