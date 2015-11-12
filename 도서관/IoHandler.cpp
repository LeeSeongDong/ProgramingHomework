#include "IoHandler.h"

void IoHandler::loadStd(string stdFile, StudentList &stdList)
{
	ifstream input;
	input.open(stdFile);

	if (input.fail())
	{
		cout << "학생 파일을 찾지 못했습니다.";
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
		cout << "도서 파일을 찾지 못했습니다.";
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
		cout << "사용자 파일을 찾지 못했습니다.";
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
		cout << "파일을 찾을 수 없습니다.";
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

//정렬된 lendList에서 이전index의 학번과
//같으면 책정보만 옆에 출력
//다르면 다음줄에 학생정보와 책정보 모두 출력
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

	cout << "기능 선택 [1.대출 2.반납 3.현황 4.종료] --- ";
	cin >> num;

	return num;
}