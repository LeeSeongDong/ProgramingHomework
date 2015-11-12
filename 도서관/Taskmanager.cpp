#include "Taskmanager.h"

bool Taskmanager::isExist(int stdNum, string bookName)
{
	IoHandler ioh;

	int stdIndex = stdList.getIndex(stdNum);

	if (stdIndex == EMPTY)
	{
		ioh.putMsg("���� �л��Դϴ�.");
		ioh.putNewLine();
		return false;
	}
	else if (bookList.getNumOfBookByName(bookName) == 0)
	{
		ioh.putMsg("���� å�Դϴ�.");
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
	//�л�, å�� �ִ���
	//�����ִ� å�� �ִ���
	//������å 2�� ��������
	//�̹� ������å����

	if ( !isExist(stdNum, bookName))
	{
		return false;
	}

	IoHandler ioh;

	if (bookList.getNumOfBookByName(bookName) <= findNumOfLendBook(bookName))
	{
		ioh.putMsg("��� ");
		ioh.putMsg(bookName);
		ioh.putMsg("å�� �������Դϴ�.");
		ioh.putNewLine();

		return false;
	}
	else if (findNumOfLendBook(stdNum) >= MAX_LEND)
	{
		int stdIndex = stdList.getIndex(stdNum);

		ioh.printStd(stdList.getStudent(stdIndex));
		ioh.putMsg("��/�� �̹� ");
		ioh.putNum(MAX_LEND);
		ioh.putMsg("���� å�� �������Դϴ�.");
		ioh.putNewLine();

		return false;
	}
	else if (findLendIndex(stdNum, bookName) != EMPTY)
	{
		ioh.putMsg("�̹� ������ å�Դϴ�.");
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
	//�л�, å�� �ִ���
	//������å�� �´���

	if ( !isExist(stdNum, bookName) )
	{
		return false;
	}

	IoHandler ioh;

	if (findLendIndex(stdNum, bookName) == EMPTY)
	{
		ioh.putMsg("������ ���� å�Դϴ�.");
		ioh.putNewLine();
		return false;
	}
	else
	{
		return true;
	}
}

//å�̸����� ������ å���� ã��
int Taskmanager::findNumOfLendBook(string bookName)
{
	int count = 0;

	int bookCount = bookList.getNumOfBookByName(bookName);

	//bookList���� å�̸����� å��ȣ ã��
	for (int i = 0; i < bookList.getNumOfBook(); ++i)
	{
		if (bookList.getBook(i).getBookName().compare(bookName) == 0)
		{
			string bookNum = bookList.getBook(i).getBookNum();

			//ã�� å��ȣ�� lendList�� �ִ��� ã��
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

//�й����� ������ å���� ã��
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

//å�̸����� �������ִ� bookIndex ã��
int Taskmanager::findIndexLendableBook(string bookName)
{
	int bookIndex = EMPTY;

	//bookList���� å�̸����� å��ȣ ã��
	for (int i = 0; i < bookList.getNumOfBook(); ++i)
	{
		if (bookList.getBook(i).getBookName().compare(bookName) == 0)
		{
			int count = 0;

			string bookNum = bookList.getBook(i).getBookNum();

			//ã�� å��ȣ�� lendList�� �ִ��� ã��
			for (int j = 0; j < lendList.getNumOfLend(); ++j)
			{
				if (lendList.getLend(j).getBookNum().compare(bookNum) == 0)
				{
					++count;
					break;
				}
			}

			//lendList�� ������ �� bookIndex ��ȯ
			if (count == 0)
			{
				bookIndex = i;
				break;
			}
		}
	}

	return bookIndex;
}

//booklist���� bookName���� bookNumã��
//lendList���� stdNum, bookNum ��� ��ġ�ϴ� lendIndex ã��
int Taskmanager::findLendIndex(int stdNum, string bookName)
{
	int lendIndex = EMPTY;

	for (int i = 0; i < bookList.getNumOfBook(); ++i)
	{
		//bookList���� bookName�� ��ġ�ϴ� bookNumã��
		if (bookList.getBook(i).getBookName().compare(bookName) == 0)
		{
			string bookNum = bookList.getBook(i).getBookNum();

			for (int j = 0; j < lendList.getNumOfLend(); ++j)
			{
				//lendList���� bookNum�� stdNum ��� ��ġ�ϴ� lendList�� indexã��
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
		ioh.putMsg("��/�� ");
		ioh.printBook(bookList.getBook(bookIndex));
		ioh.putMsg("��/�� �����Ͽ����ϴ�.");
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
		ioh.putMsg("��/�� ");
		ioh.printBook(bookList.getBook(bookIndex));
		ioh.putMsg("��/�� �ݳ��Ͽ����ϴ�.");
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