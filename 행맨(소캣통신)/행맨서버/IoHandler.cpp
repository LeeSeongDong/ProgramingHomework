#include "IoHandler.h"

void IoHandler::loadUserFile(string userFile, UserList &userList)
{
		ifstream inputFile;

		inputFile.open(userFile);

		if (inputFile.fail())
		{
			cout << "사용자 파일을 찾지 못했습니다.";
			return;
		}

		string name;
		string loadWinCount;
		string loadLoseCount;

		int winCount;
		int loseCount;
		int userCount = 0;

		string temp;

		while (!inputFile.eof())
		{


			inputFile >> name;

			while (name.at(name.size()-1) != ']')		//이름에 공백이 있는경우
			{
				inputFile >> temp;
				name = name + " " + temp;
			}

			inputFile >> loadWinCount;
			inputFile >> loadLoseCount;

			//[ ] 사이에 있는 문자열만 추출
			name = name.substr(1, name.size() - 2);
			loadWinCount = loadWinCount.substr(1, loadWinCount.size() - 1);
			loadLoseCount = loadLoseCount.substr(1, loadLoseCount.size() - 1);

			// 승패는 string에서 int형으로 저장
			winCount = atoi(loadWinCount.c_str());
			loseCount = atoi(loadLoseCount.c_str());

			//이름, 승, 패를 user에 저장후 userList에 삽입
			User user(name, winCount, loseCount);
			userList.insertUser(user);
		}

		inputFile.close();
	}


void IoHandler::loadWordFile(string wordFile, WordList &wordList)
{
	ifstream inputFile;

	inputFile.open(wordFile);

	if (inputFile.fail())
	{
		cout << "단어 파일을 찾지 못했습니다.";
		return;
	}

	string wordName;
	string partOfSpeech;
	string meaning;

	int wordCount = 0;

	string temp;

	while (!inputFile.eof())
	{
		inputFile >> wordName;

		while (wordName.at(wordName.size() - 1) != ']')		//단어에 공백이 있는경우
		{
			inputFile >> temp;
			wordName = wordName + " " + temp;
		}

		inputFile >> partOfSpeech;

		while (partOfSpeech.at(partOfSpeech.size() - 1) != ']')		//품사에 공백이 있는경우
		{
			inputFile >> temp;
			partOfSpeech = partOfSpeech + " " + temp;
		}

		//inputFile >> space;			//구분자인 빈칸을 없애기위해

		getline(inputFile, meaning, '\n');	//의미부분은 공백이 많고 길기 때문에 getline사용


		wordName = wordName.substr(1, wordName.size() - 2);

		Word word(wordName, partOfSpeech, meaning);

		wordList.insertWord(word);
	}

	inputFile.close();
}


void IoHandler::saveUserFile(string userFile, UserList &userList)
{
	ofstream outputFile;

	outputFile.open(userFile);

	if (outputFile.fail())
	{
		cout << "파일을 찾을수 없습니다.";
		return;
	}

	for (int i = 0; i < userList.getSize(); ++i)
	{
		outputFile << "[" << userList.getUserByIndex(i).getName() << "]" << " ";
		outputFile << "[" << userList.getUserByIndex(i).getWinCount() << "]" << " ";
		outputFile << "[" << userList.getUserByIndex(i).getLoseCount() << "]";
		if (i != userList.getSize() - 1)
		{
			outputFile << endl;
		}
	}

	outputFile.close();
}



string IoHandler::inputName(string msg)
{
	string name;

	cout << msg;
	cin >> name;

	return name;
}


char IoHandler::inputMenu(User user)
{
	char menu;

	cout << "새 게임을 시작하려면 “S”를" << endl;
	cout << "본인의 이번 게임 점수를 보려면 “I”를" << endl;
	cout << "본인의 이전 게임 점수를 보려면 “H”를" << endl;
	cout << "전체 사용자의 등수를 보려면 “R”을" << endl;
	cout << "이번 게임 결과를 저장하고 종료하려면 “Q”를" << endl;
	cout << "이번 게임 결과를 저장하지 않고 종료하려면 “Z”를 입력하시오 [S/I/H/R/Q/Z] : ";
	cin >> menu;

	return menu;
}


string IoHandler::inputLetter(string msg)
{
	string letter;

	cout << msg;

	cin >> letter;

	return letter;
}


void IoHandler::printHangman(int count)
{

	cout << "+-----+" << endl;
	cout << "|     |" << endl;

	if (count >= 1)
	{
		cout << "|     O" << endl;
	}
	else
	{
		cout << "|      " << endl;
	}


	if (count >= 4)
	{
		cout << "|    /|＼" << endl;
	}
	else if (count >= 3)
	{
		cout << "|    /|  " << endl;
	}
	else if (count >= 2)
	{
		cout << "|    /   " << endl;
	}
	else
	{
		cout << "|          " << endl;
	}


	if (count >= 5)
	{
		cout << "|     |" << endl;
	}
	else
	{
		cout << "|           " << endl;
	}


	if (count >= 7)
	{
		cout << "|    / ＼" << endl;
	}
	else if (count >= 6)
	{
		cout << "|     /" << endl;
	}
	else
	{
		cout << "|            " << endl;
	}


	cout << "|" << endl;
	cout << "___" << endl;
}


void IoHandler::printLetter(char a)
{
	cout << a;
}


User IoHandler::printUserMenu(UserList &userList)
{
	User currentUser;
	string userName;

	char a;

	while (true){
		system("cls");

		cout << "====================================================" << endl;
		cout << "                 행맨게임을 시작합니다.             " << endl;
		cout << "====================================================" << endl;



		cout << "(기록해 둔 게임 성적을 load되거나 새로운 사용자가 등록됩니다.)" << endl;
		userName = inputName("사용자의 이름을 입력하세요 : ");

		cout << endl << endl;

		if (userList.isUserExist(userName) == true)
		{
			cout << "등록된 사용자가 있습니다. 등록된 사용자의 게임 성적을 load하려면 L을, " << endl;
			cout << "새로운 사용자 이름을 등록하려면 N을 입력하세요 [L/N] : ";
			cin >> a;

			cout << endl << endl;

			if (a == 'L' || a == 'l')
			{
				User user(userList.getUserByName(userName).getName());
				currentUser = user;

				cout << "기존 사용자 [" << currentUser.getName() << "]을/를 불러옵니다. ";
				cin >> a;
				break;
			}

			else if (a == 'N' || a == 'n')
			{
				continue;
			}

			else
			{
				cout << "L 또는 N을 입력하세요." << endl;
				cin >> a;
				continue;
			}
		}

		else
		{
			User user(userName);
			currentUser = user;

			cout << "새로운 사용자 [" << currentUser.getName() << "]을/를 불러옵니다. ";

			cin >> a;

			break;
		}
	}

	return currentUser;
}

	
void IoHandler::printRank(UserList &userList)
{
	int sameRank = 0;
	char a;

	for (int i = 0; i < userList.getSize(); ++i)
	{
		if (i != 0)
		{
			if (userList.getUserByIndex(i - 1).getWinningRate() == userList.getUserByIndex(i).getWinningRate())
			{
				sameRank += 1;
			}
			else
			{
				sameRank = 0;
			}
		}
		cout << i + 1 - sameRank << "등 : " << userList.getUserByIndex(i).getName();
		cout << "( " << userList.getUserByIndex(i).getWinCount() + userList.getUserByIndex(i).getLoseCount() << "전 ";
		cout << userList.getUserByIndex(i).getWinCount() << "승. ";
		cout << "승률 " << userList.getUserByIndex(i).getWinningRate() << "% )";
		cout << endl << endl;

	}

	cin >> a;
}


void IoHandler::printPreviousRecord(UserList &userList, User currentUser)
{
	if (userList.isUserExist(currentUser.getName()) == true)
	{
		cout << "이전 게임 기록은 ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() + userList.getUserByName(currentUser.getName()).getLoseCount() << "전 ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() << "승 ";
		cout << userList.getUserByName(currentUser.getName()).getLoseCount() << "패입니다." << endl;
	}

	else
	{
		cout << "이전 기록이 없습니다." << endl;
	}

	char a;
	cin >> a;
}


void IoHandler::printCurrentRecord(User currentUser)
{
	cout << "이번 게임 기록은 ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() << "전 ";
	cout << currentUser.getWinCount() << "승 ";
	cout << currentUser.getLoseCount() << "패입니다." << endl;

	char a;
	cin >> a;
}


void IoHandler::printGameHeader(User currentUser)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName() << "의 ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() + 1;
	cout << "번째 게임이 수행중에 있습니다. (이번 게임 " << currentUser.getWinCount() << "승 ";
	cout << currentUser.getLoseCount() << "패)" << endl;
	cout << "====================================================" << endl;
}


void IoHandler::printMenuHeader(User currentUser)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName();
	cout << "이 행맨 게임을 수행하고 있습니다. (이번 게임 " << currentUser.getWinCount() << "승 ";
	cout << currentUser.getLoseCount() << "패)" << endl;
	cout << "====================================================" << endl;
}