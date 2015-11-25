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


		lowerInputData = upperToLower(ioh.inputLetter("알파벳이나 전체 단어를 입력하세요. [A - z 또는 단어] : "));
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

				ioh.putMsg("단어찾기에 성공하셨습니다!! 계속하시려면 아무 키나 입력하세요.");
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

				ioh.putMsg("단어찾기에 실패하셨습니다!! 계속하시려면 아무 키나 입력하세요. ");
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
	{//게임시작
		send(servSock, "S", 1, 0);
		startHangmanGame(hg, servSock);
		break;
	}
	case 'I':
	{//현재유저정보
		send(servSock, "I", 1, 0);
		putCurrentRecord();
		break;
	}
	case 'H':
	{//현재유저 이전기록
		send(servSock, "H", 1, 0);
		putPreviousRecord();
		break;
	}
	case 'R':
	{//전체유저 순위
		send(servSock, "R", 1, 0);
		putRank(servSock);
		break;
	}
	case 'Q':
	{//저장후 종료
		send(servSock, "Q", 1, 0);
		saveAndQuit(servSock);
		break;
	}
	case 'Z':
	{//저장하지않고 종료
		send(servSock, "Z", 1, 0);
		break;
	}

	default:
	{
		ioh.putMsg("[S/I/H/R/Q/Z] 중에서 입력하세요. ");
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
			ioh.putMsg("사용 가능한 낱말중에서 골라 입력하세요. ");
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
			ioh.putMsg("단어의 글자수가 다릅니다.");
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

	cout << "이전 게임 결과인 " << currentUser.getWinCount() + currentUser.getLoseCount() << "전 ";
	cout << currentUser.getWinCount() << "승 ";
	cout << currentUser.getLoseCount() << "패에 ";

	cout << endl;

	cout << "이번 게임 결과인 " << win + lose << "전 ";
	cout << win << "승 ";
	cout << lose << "패가 반영되어";

	cout << endl;

	cout << currentUser.getWinCount() + currentUser.getLoseCount() + win + lose << "전 ";
	cout << currentUser.getWinCount() + win << "승 ";
	cout << currentUser.getLoseCount() + lose;
	cout << "패를 게임 결과로 서버에 저장하고 종료합니다." << endl;

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