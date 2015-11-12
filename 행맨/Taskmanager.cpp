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
				hg.putGameHeader(currentUser);
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
				hg.putGameHeader(currentUser);
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
		ioh.putMsg("[S/I/H/R/Q/Z] 중에서 입력하세요. ");
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


	//기존 사용자
	if (userList.isUserExist(currentUser.getName()) == true)
	{
		cout << endl;

		cout << "이전 게임 결과인 " << userList.getUserByName(currentUser.getName()).getWinCount() + userList.getUserByName(currentUser.getName()).getLoseCount() << "전 ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() << "승 ";
		cout << userList.getUserByName(currentUser.getName()).getLoseCount() << "패에 ";

		cout << endl;

		cout << "이번 게임 결과인 " << currentUser.getWinCount() + currentUser.getLoseCount() << "전 ";
		cout << currentUser.getWinCount() << "승 ";
		cout << currentUser.getLoseCount() << "패가 반영되어";

		cout << endl;

		cout << userList.getUserByName(currentUser.getName()).getWinCount() + userList.getUserByName(currentUser.getName()).getLoseCount() +
			currentUser.getWinCount() + currentUser.getLoseCount() << "전 ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() + currentUser.getWinCount() << "승 ";
		cout << userList.getUserByName(currentUser.getName()).getLoseCount() + currentUser.getLoseCount();
		cout << "패를 게임 결과로 파일에 저장하고 종료합니다." << endl;

		
		userList.getUserByName(currentUser.getName()).saveRecord(currentUser.getWinCount(), currentUser.getLoseCount());

		userList.saveUser(currentUser);
	}

	//새로운 사용자
	else
	{
		cout << endl;

		cout << "이전 게임 결과인 " << 0 << "전 " << 0 << "승 " << 0 << "패에 ";
		
		cout << endl;
		
		cout << "이번 게임 결과인 " << currentUser.getWinCount() + currentUser.getLoseCount() << "전 ";
		cout << currentUser.getWinCount() << "승 ";
		cout << currentUser.getLoseCount() << "패가 반영되어";

		cout << endl;

		cout << currentUser.getWinCount() + currentUser.getLoseCount() << "전 ";
		cout << currentUser.getWinCount() << "승 ";
		cout << currentUser.getLoseCount();
		cout << "패를 게임 결과로 파일에 저장하고 종료합니다." << endl;

		userList.insertUser(currentUser);
	}

	ioh.saveUserFile(userFile, userList);
}