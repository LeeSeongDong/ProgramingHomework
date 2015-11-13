#include "IoHandler.h"

void IoHandler::loadUserFile(string userFile, UserList &userList)
{
		ifstream inputFile;

		inputFile.open(userFile);

		if (inputFile.fail())
		{
			cout << "����� ������ ã�� ���߽��ϴ�.";
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

			while (name.at(name.size()-1) != ']')		//�̸��� ������ �ִ°��
			{
				inputFile >> temp;
				name = name + " " + temp;
			}

			inputFile >> loadWinCount;
			inputFile >> loadLoseCount;

			//[ ] ���̿� �ִ� ���ڿ��� ����
			name = name.substr(1, name.size() - 2);
			loadWinCount = loadWinCount.substr(1, loadWinCount.size() - 1);
			loadLoseCount = loadLoseCount.substr(1, loadLoseCount.size() - 1);

			// ���д� string���� int������ ����
			winCount = atoi(loadWinCount.c_str());
			loseCount = atoi(loadLoseCount.c_str());

			//�̸�, ��, �и� user�� ������ userList�� ����
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
		cout << "�ܾ� ������ ã�� ���߽��ϴ�.";
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

		while (wordName.at(wordName.size() - 1) != ']')		//�ܾ ������ �ִ°��
		{
			inputFile >> temp;
			wordName = wordName + " " + temp;
		}

		inputFile >> partOfSpeech;

		while (partOfSpeech.at(partOfSpeech.size() - 1) != ']')		//ǰ�翡 ������ �ִ°��
		{
			inputFile >> temp;
			partOfSpeech = partOfSpeech + " " + temp;
		}

		//inputFile >> space;			//�������� ��ĭ�� ���ֱ�����

		getline(inputFile, meaning, '\n');	//�ǹ̺κ��� ������ ���� ��� ������ getline���


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
		cout << "������ ã���� �����ϴ�.";
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

	cout << "�� ������ �����Ϸ��� ��S����" << endl;
	cout << "������ �̹� ���� ������ ������ ��I����" << endl;
	cout << "������ ���� ���� ������ ������ ��H����" << endl;
	cout << "��ü ������� ����� ������ ��R����" << endl;
	cout << "�̹� ���� ����� �����ϰ� �����Ϸ��� ��Q����" << endl;
	cout << "�̹� ���� ����� �������� �ʰ� �����Ϸ��� ��Z���� �Է��Ͻÿ� [S/I/H/R/Q/Z] : ";
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
		cout << "|    /|��" << endl;
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
		cout << "|    / ��" << endl;
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
		cout << "                 ��ǰ����� �����մϴ�.             " << endl;
		cout << "====================================================" << endl;



		cout << "(����� �� ���� ������ load�ǰų� ���ο� ����ڰ� ��ϵ˴ϴ�.)" << endl;
		userName = inputName("������� �̸��� �Է��ϼ��� : ");

		cout << endl << endl;

		if (userList.isUserExist(userName) == true)
		{
			cout << "��ϵ� ����ڰ� �ֽ��ϴ�. ��ϵ� ������� ���� ������ load�Ϸ��� L��, " << endl;
			cout << "���ο� ����� �̸��� ����Ϸ��� N�� �Է��ϼ��� [L/N] : ";
			cin >> a;

			cout << endl << endl;

			if (a == 'L' || a == 'l')
			{
				User user(userList.getUserByName(userName).getName());
				currentUser = user;

				cout << "���� ����� [" << currentUser.getName() << "]��/�� �ҷ��ɴϴ�. ";
				cin >> a;
				break;
			}

			else if (a == 'N' || a == 'n')
			{
				continue;
			}

			else
			{
				cout << "L �Ǵ� N�� �Է��ϼ���." << endl;
				cin >> a;
				continue;
			}
		}

		else
		{
			User user(userName);
			currentUser = user;

			cout << "���ο� ����� [" << currentUser.getName() << "]��/�� �ҷ��ɴϴ�. ";

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
		cout << i + 1 - sameRank << "�� : " << userList.getUserByIndex(i).getName();
		cout << "( " << userList.getUserByIndex(i).getWinCount() + userList.getUserByIndex(i).getLoseCount() << "�� ";
		cout << userList.getUserByIndex(i).getWinCount() << "��. ";
		cout << "�·� " << userList.getUserByIndex(i).getWinningRate() << "% )";
		cout << endl << endl;

	}

	cin >> a;
}


void IoHandler::printPreviousRecord(UserList &userList, User currentUser)
{
	if (userList.isUserExist(currentUser.getName()) == true)
	{
		cout << "���� ���� ����� ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() + userList.getUserByName(currentUser.getName()).getLoseCount() << "�� ";
		cout << userList.getUserByName(currentUser.getName()).getWinCount() << "�� ";
		cout << userList.getUserByName(currentUser.getName()).getLoseCount() << "���Դϴ�." << endl;
	}

	else
	{
		cout << "���� ����� �����ϴ�." << endl;
	}

	char a;
	cin >> a;
}


void IoHandler::printCurrentRecord(User currentUser)
{
	cout << "�̹� ���� ����� ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() << "�� ";
	cout << currentUser.getWinCount() << "�� ";
	cout << currentUser.getLoseCount() << "���Դϴ�." << endl;

	char a;
	cin >> a;
}


void IoHandler::printGameHeader(User currentUser)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName() << "�� ";
	cout << currentUser.getWinCount() + currentUser.getLoseCount() + 1;
	cout << "��° ������ �����߿� �ֽ��ϴ�. (�̹� ���� " << currentUser.getWinCount() << "�� ";
	cout << currentUser.getLoseCount() << "��)" << endl;
	cout << "====================================================" << endl;
}


void IoHandler::printMenuHeader(User currentUser)
{
	system("cls");

	cout << "====================================================" << endl;
	cout << "   " << currentUser.getName();
	cout << "�� ��� ������ �����ϰ� �ֽ��ϴ�. (�̹� ���� " << currentUser.getWinCount() << "�� ";
	cout << currentUser.getLoseCount() << "��)" << endl;
	cout << "====================================================" << endl;
}