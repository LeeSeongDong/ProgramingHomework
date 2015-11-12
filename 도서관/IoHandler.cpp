#include "IoHandler.h"

void IoHandler::loadStd(string stdFile, StudentList &stdList)
{
	ifstream input;
	input.open(stdFile);

	if (input.fail())
	{
		cout << "�л� ������ ã�� ���߽��ϴ�.";
		return;
	}

	string loadStdNum;
	string loadStdName;
	int stdNum;

	while (!input.eof())
	{
		input >> loadStdNum >> loadStdName;

		stdNum = atoi(loadStdNum.c_str());

		Student std(stdNum, loadStdName);

		stdList.insert(std);
	}

	input.close();
}

void IoHandler::loadBook(string bookFile, BookList &bookList)
{
	ifstream input;
	input.open(bookFile);

	if (input.fail())
	{
		cout << "���� ������ ã�� ���߽��ϴ�.";
		return;
	}

	string loadBookNum;
	string loadBookName;

	while (!input.eof())
	{
		input >> loadBookNum;

		getline(input, loadBookName, '\n');

		loadBookName = loadBookName.substr(1, loadBookName.size());

		Book book(loadBookNum, loadBookName);

		bookList.insert(book);
	}

	input.close();
}

void IoHandler::loadLend(string lendFile, LendList &lendList)
{
	ifstream input;
	input.open(lendFile);

	if (input.fail())
	{
		cout << "����� ������ ã�� ���߽��ϴ�.";
		return;
	}

	string loadStdNum;
	string loadBookNum;
	int stdNum;

	while (!input.eof())
	{
		input >> loadBookNum >> loadStdNum;

		stdNum = atoi(loadStdNum.c_str());

		Lend lend(stdNum, loadBookNum);

		lendList.insert(lend);
	}

	input.close();
}

void IoHandler::saveLend(string lendFile, LendList &lendList)
{
	ofstream output;

	output.open(lendFile);

	if (output.fail())
	{
		cout << "������ ã�� �� �����ϴ�.";
		return;
	}

	for (int i = 0; i < lendList.getNumOfLend(); ++i)
	{
		output << lendList.getLend(i).getBookNum() << " " << lendList.getLend(i).getStdNum();

		if (i != (lendList.getNumOfLend() - 1))
		{
			output << endl;
		}
	}

	output.close();
}

void IoHandler::putMsg(string msg)
{
	cout << msg;
}

void IoHandler::putNum(int num)
{
	cout << num;
}

void IoHandler::putNewLine()
{
	cout << endl;
}

int IoHandler::inputNum()
{
	int num;

	cin >> num;
	return num;
}

string IoHandler::inputMsg()
{
	string msg;

	getline(cin, msg, '\n');

	msg = msg.substr(1, msg.size());
	return msg;
}

void IoHandler::printStd(Student const &std)
{
	cout << std.getStdNum() << " " << std.getStdName();
}

void IoHandler::printBook(Book const &book)
{
	cout << book.getBookNum() << " " << book.getBookName();
}

//���ĵ� lendList���� ����index�� �й���
//������ å������ ���� ���
//�ٸ��� �����ٿ� �л������� å���� ��� ���
void IoHandler::printLendList(StudentList const &stdList, BookList const &bookList, LendList const &lendList)
{
	for (int i = 0; i < lendList.getNumOfLend(); ++i)
	{
		int stdNum = lendList.getLend(i).getStdNum();
		string bookNum = lendList.getLend(i).getBookNum();

		int stdIndex = stdList.getIndex(stdNum);
		int bookIndex = bookList.getIndexByNum(bookNum);

		if (i == 0)
		{
			printStd(stdList.getStudent(stdIndex));
			cout << " [";
			printBook(bookList.getBook(bookIndex));
			cout << "]";
		}
		else
		{
			if (lendList.getLend(i).getStdNum() == lendList.getLend(i - 1).getStdNum())
			{
				cout << " [";
				printBook(bookList.getBook(bookIndex));
				cout << "]";
			}
			else
			{
				cout << endl;
				printStd(stdList.getStudent(stdIndex));
				cout << " [";
				printBook(bookList.getBook(bookIndex));
				cout << "]";
			}
		}
	}

	cout << endl << endl;
}

int IoHandler::putMenu()
{
	int num;

	cout << "��� ���� [1.���� 2.�ݳ� 3.��Ȳ 4.����] --- ";
	cin >> num;

	return num;
}