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
		case 1:	//����
		{
			ioh.putMsg("�й��� ������ �Է� --- ");
			int stdNum =  ioh.inputNum();
			string bookName = ioh.inputMsg();

			tm.lendBook(stdNum, bookName);
			ioh.putNewLine();

			break;
		}
		case 2:	//�ݳ�
		{
			ioh.putMsg("�й��� ������ �Է� --- ");
			int stdNum = ioh.inputNum();
			string bookName = ioh.inputMsg();

			tm.returnBook(stdNum, bookName);
			ioh.putNewLine();

			break;
		}
		case 3:	//��Ȳ
		{
			tm.printLendList();
			break;
		}
		case 4:	//����
		{
			tm.saveLendList("lend.txt");
			ioh.putMsg("���� - �ݳ� ��Ȳ�� �����ϰ� �����մϴ�.");

			return 0;
		}
		default:
		{
			ioh.putMsg("1 ~ 4�߿� �����ϼ���.");
			ioh.putNewLine();
			break;
		}
		}
	}
}