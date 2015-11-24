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
