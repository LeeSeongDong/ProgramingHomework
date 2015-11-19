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

char Taskmanager::selectMenu(char a, HangmanGame &hg, UserList &userList, WordList &wordList, SOCKET& servSock)
{
	IoHandler ioh;

	if (a >= LOWER_A)
	{
		a -= GAP_UPPER_TO_LOWER;
	}

	switch (a)
	{

	case 'S':
	{
		send(servSock, "S", 1, 0);
		startHangmanGame(hg,wordList);
		break;
	}
	case 'I':
	{
		send(servSock, "I", 1, 0);
		putCurrentRecord();
		break;
	}
	case 'H':
	{
		send(servSock, "H", 1, 0);
		send(servSock, currentUser.getName().c_str(), currentUser.getName().size(), 0);
		putPreviousRecord(userList);
		break;
	}
	case 'R':
	{
		send(servSock, "R", 1, 0);
		putRank(userList);
		break;
	}
	case 'Q':
	{
		send(servSock, "Q", 1, 0);
		saveAndQuit(userList);
		break;
	}
	case 'Z':
	{
		send(servSock, "Z", 1, 0);
		break;
	}

	default:
	{
		ioh.putMsg("[S/I/H/R/Q/Z] �߿��� �Է��ϼ���. ");
		break;
	}
	}

	return a;
}

void Taskmanager::loadUser(UserList &userList, SOCKET& servSock)
{
	IoHandler ioh;

	currentUser = ioh.printUserMenu(userList, servSock);
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


void Taskmanager::saveAndQuit(UserList &userList)
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
}