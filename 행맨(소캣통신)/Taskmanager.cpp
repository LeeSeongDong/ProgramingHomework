#include "Taskmanager.h"

const int NUMBER_OF_ALPHABET = 26;
const int LOWER_A = 97;
const int GAP_UPPER_TO_LOWER = 32;

void Taskmanager::startHangmanGame(HangmanGame &hg, WordList &wordList)
{
	IoHandler ioh;
	char a;

	hg.makeQuestion(wordList);

	string lowerQuestion = upperToLower(hg.getQuestionWord());
	
	string lowerInputData;

	hg.setUsableLetter();
	hg.setFindLetter();
	
	hg.endGame();		//hangmancount = 0

	while (true)
	{
		hg.putGameHeader(currentUser);
		hg.putHangman();
		hg.putQuestion();

		hg.putUsableLetter();

		ioh.putNewLine();
		ioh.putNewLine();


		lowerInputData = upperToLower(ioh.inputLetter("���ĺ��̳� ��ü �ܾ �Է��ϼ���. [A - z �Ǵ� �ܾ�] : "));
		hg.setInputWord(lowerInputData);

		if (isOverlap(hg))
		{
			cin >> a;
			continue;
		}

		
		if (hg.isCorrect() == true)
		{
			if (hg.isWin() == true)
			{
				hg.putGameHeader(currentUser);
				hg.putHangman();
				hg.putQuestion();

				hg.putUsableLetter();

				ioh.putNewLine();
				ioh.putNewLine();

				ioh.putMsg("�ܾ�ã�⿡ �����ϼ̽��ϴ�!! ����Ͻ÷��� �ƹ� Ű�� �Է��ϼ���.");
				cin >> a;

				currentUserScore(true);
				break;
			}
		}
		else
		{
			if (hg.isWin() != true && hg.isLose() == true)
			{
				hg.putGameHeader(currentUser);
				hg.putHangman();
				hg.putQuestion();

				hg.putUsableLetter();

				ioh.putNewLine();
				ioh.putNewLine();

				ioh.putMsg("�ܾ�ã�⿡ �����ϼ̽��ϴ�!! ����Ͻ÷��� �ƹ� Ű�� �Է��ϼ���. ");
				cin >> a;

				currentUserScore(false);
				break;
			}
		}
	}
}

char Taskmanager::selectMenu(char a, HangmanGame &hg, UserList &userList, WordList &wordList, string userFile)
{
	IoHandler ioh;

	char b;

	if (a >= LOWER_A)
	{
		a -= GAP_UPPER_TO_LOWER;
	}

	switch (a)
	{

	case 'S':
	{
		startHangmanGame(hg,wordList);
		break;
	}
	case 'I':
	{
		putCurrentRecord();
		break;
	}
	case 'H':
	{
		putPreviousRecord(userList);
		break;
	}
	case 'R':
	{
		putRank(userList);
		break;
	}
	case 'Q':
	{
		saveAndQuit(userFile, userList);
		cin >> b;
		break;
	}
	case 'Z':
	{
		break;
	}

	default:
	{
		ioh.putMsg("[S/I/H/R/Q/Z] �߿��� �Է��ϼ���. ");
		cin >> b;
		break;
	}
	}

	return a;

}

void Taskmanager::loadUser(UserList &userList)
{
	IoHandler ioh;

	currentUser = ioh.printUserMenu(userList);
}

string Taskmanager::upperToLower(string word)
{
	for (int i = 0; i < word.size(); ++i)
	{
		if (word.at(i) < LOWER_A)
		{
			word.at(i) += GAP_UPPER_TO_LOWER;
		}
	}

	return word;
}

bool Taskmanager::isOverlap(HangmanGame hg)
{
	IoHandler ioh;

	if (hg.isLetter())
	{
		int count = 0;

		for (int i = 0; i < NUMBER_OF_ALPHABET; ++i)
		{
			if (hg.getUsableLetter(i) + GAP_UPPER_TO_LOWER == hg.getInputWord().at(0))
			{
				++count;
			}
		}

		if (count == 0)
		{
			ioh.putMsg("��� ������ �����߿��� ��� �Է��ϼ���. ");
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (hg.getInputWord().size() == hg.getQuestionWord().size())
		{
			return false;
		}
		else
		{
			ioh.putMsg("�ܾ��� ���ڼ��� �ٸ��ϴ�.");
			return true;
		}
	}
}


void Taskmanager::currentUserScore(bool isWin)
{
	if (isWin)
	{
		currentUser.saveRecord(1, 0);
	}
	else
	{
		currentUser.saveRecord(0, 1);
	}
}


void Taskmanager::putRank(UserList &userList)
{
	IoHandler ioh;

	ioh.printRank(userList);
}


void Taskmanager::putPreviousRecord(UserList &userList)
{
	IoHandler ioh;

	ioh.printPreviousRecord(userList, currentUser);
}


void Taskmanager::putCurrentRecord()
{
	IoHandler ioh;

	ioh.printCurrentRecord(currentUser);
}


void Taskmanager::saveAndQuit(string userFile, UserList &userList)
{
	IoHandler ioh;


	//���� �����
	if (userList.isUserExist(currentUser.getName()) == true)
	{
		cout << endl;

		cout << "���� ���� ����� " << userList.getUserByName(currentUser.getName()).getWinCount() + userList.getUserByName(currentUser.getName()).getLoseCount() << "�� ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() << "�� ";
		cout << userList.getUserByName(currentUser.getName()).getLoseCount() << "�п� ";

		cout << endl;

		cout << "�̹� ���� ����� " << currentUser.getWinCount() + currentUser.getLoseCount() << "�� ";
		cout << currentUser.getWinCount() << "�� ";
		cout << currentUser.getLoseCount() << "�а� �ݿ��Ǿ�";

		cout << endl;

		cout << userList.getUserByName(currentUser.getName()).getWinCount() + userList.getUserByName(currentUser.getName()).getLoseCount() +
			currentUser.getWinCount() + currentUser.getLoseCount() << "�� ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() + currentUser.getWinCount() << "�� ";
		cout << userList.getUserByName(currentUser.getName()).getLoseCount() + currentUser.getLoseCount();
		cout << "�и� ���� ����� ���Ͽ� �����ϰ� �����մϴ�." << endl;

		
		userList.getUserByName(currentUser.getName()).saveRecord(currentUser.getWinCount(), currentUser.getLoseCount());

		userList.saveUser(currentUser);
	}

	//���ο� �����
	else
	{
		cout << endl;

		cout << "���� ���� ����� " << 0 << "�� " << 0 << "�� " << 0 << "�п� ";
		
		cout << endl;
		
		cout << "�̹� ���� ����� " << currentUser.getWinCount() + currentUser.getLoseCount() << "�� ";
		cout << currentUser.getWinCount() << "�� ";
		cout << currentUser.getLoseCount() << "�а� �ݿ��Ǿ�";

		cout << endl;

		cout << currentUser.getWinCount() + currentUser.getLoseCount() << "�� ";
		cout << currentUser.getWinCount() << "�� ";
		cout << currentUser.getLoseCount();
		cout << "�и� ���� ����� ���Ͽ� �����ϰ� �����մϴ�." << endl;

		userList.insertUser(currentUser);
	}

	ioh.saveUserFile(userFile, userList);
}