#include "Taskmanager.h"

void Taskmanager::startHangmanGame(HangmanGame &hg, SOCKET& servSock)
{
	IoHandler ioh;
	char a;

	string word, partOfSpeech, meaning;
	char buf[255] = { 0 };

	recv(servSock, buf, sizeof(buf), 0);
	word = buf;
	send(servSock, "next", 4, 0);

	recv(servSock, buf, sizeof(buf), 0);
	partOfSpeech = buf;
	send(servSock, "next", 4, 0);

	recv(servSock, buf, sizeof(buf), 0);
	meaning = buf;

	hg.setQuestion(word, partOfSpeech, meaning);

	string lowerQuestion = upperToLower(hg.getQuestionWord());

	string lowerInputData;

	hg.setUsableLetter();
	hg.setFindLetter();

	hg.initGame();		//hangmancount = 0

	while (true)
	{
		hg.putGameHeader(currentUser, win, lose);
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
				hg.putGameHeader(currentUser, win, lose);
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
				hg.putGameHeader(currentUser, win, lose);
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

char Taskmanager::selectMenu(char a, HangmanGame &hg, SOCKET& servSock)
{
	IoHandler ioh;
	char buf[255] = { 0 };

	if (a >= LOWER_A)
	{
		a -= GAP_UPPER_TO_LOWER;
	}

	switch (a)
	{

	case 'S':
	{//���ӽ���
		send(servSock, "S", 1, 0);
		startHangmanGame(hg, servSock);
		break;
	}
	case 'I':
	{//������������
		send(servSock, "I", 1, 0);
		putCurrentRecord();
		break;
	}
	case 'H':
	{//�������� �������
		send(servSock, "H", 1, 0);
		putPreviousRecord();
		break;
	}
	case 'R':
	{//��ü���� ����
		send(servSock, "R", 1, 0);
		putRank(servSock);
		break;
	}
	case 'Q':
	{//������ ����
		send(servSock, "Q", 1, 0);
		saveAndQuit(servSock);
		break;
	}
	case 'Z':
	{//���������ʰ� ����
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

void Taskmanager::loadUser(SOCKET& servSock)
{
	IoHandler ioh;

	currentUser = ioh.printUserMenu(servSock);
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
		++win;
	}
	else
	{
		++lose;
	}
}

void Taskmanager::putRank(SOCKET& servSock)
{
	IoHandler ioh;

	ioh.printRank(servSock);
}

void Taskmanager::putPreviousRecord()
{
	IoHandler ioh;

	ioh.printPreviousRecord(currentUser);
}

void Taskmanager::putCurrentRecord()
{
	IoHandler ioh;

	ioh.printCurrentRecord(win, lose);
}

void Taskmanager::saveAndQuit(SOCKET& servSock)
{
	IoHandler ioh;
	char a;
	char buf[255] = { 0 };

	cout << endl;

	cout << "���� ���� ����� " << currentUser.getWinCount() + currentUser.getLoseCount() << "�� ";
	cout << currentUser.getWinCount() << "�� ";
	cout << currentUser.getLoseCount() << "�п� ";

	cout << endl;

	cout << "�̹� ���� ����� " << win + lose << "�� ";
	cout << win << "�� ";
	cout << lose << "�а� �ݿ��Ǿ�";

	cout << endl;

	cout << currentUser.getWinCount() + currentUser.getLoseCount() + win + lose << "�� ";
	cout << currentUser.getWinCount() + win << "�� ";
	cout << currentUser.getLoseCount() + lose;
	cout << "�и� ���� ����� ������ �����ϰ� �����մϴ�." << endl;

	currentUser.saveRecord(win, lose);
	recv(servSock, buf, sizeof(buf), 0);

	send(servSock, currentUser.getName().c_str(), currentUser.getName().size(), 0);
	recv(servSock, buf, sizeof(buf), 0);

	itoa(currentUser.getWinCount(), buf, 10);
	send(servSock, buf, sizeof(buf), 0);
	recv(servSock, buf, sizeof(buf), 0);

	itoa(currentUser.getLoseCount(), buf, 10);
	send(servSock, buf, sizeof(buf), 0);

	cin >> a;
	cout << a;
}