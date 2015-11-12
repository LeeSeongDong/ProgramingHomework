#include "Taskmanager.h"

int main()
{
	StudentList stdList;
	BookList bookList;
	LendList lendList;

	IoHandler ioh;

	ioh.loadStd("std.txt", stdList);
	ioh.loadBook("book.txt", bookList);
	ioh.loadLend("lend.txt", lendList);

	Taskmanager tm(stdList, bookList, lendList);

	int menu;
	while (true)
	{
		menu = ioh.putMenu();

		switch (menu)
		{
		case 1:	//대출
		{
			ioh.putMsg("학번과 도서명 입력 --- ");
			int stdNum =  ioh.inputNum();
			string bookName = ioh.inputMsg();

			tm.lendBook(stdNum, bookName);
			ioh.putNewLine();

			break;
		}
		case 2:	//반납
		{
			ioh.putMsg("학번과 도서명 입력 --- ");
			int stdNum = ioh.inputNum();
			string bookName = ioh.inputMsg();

			tm.returnBook(stdNum, bookName);
			ioh.putNewLine();

			break;
		}
		case 3:	//현황
		{
			tm.printLendList();
			break;
		}
		case 4:	//종료
		{
			tm.saveLendList("lend.txt");
			ioh.putMsg("대출 - 반납 상황을 저장하고 종료합니다.");

			return 0;
		}
		default:
		{
			ioh.putMsg("1 ~ 4중에 선택하세요.");
			ioh.putNewLine();
			break;
		}
		}
	}
}