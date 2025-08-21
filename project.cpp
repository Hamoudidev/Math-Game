#include <iostream>
#include <string>
using namespace std;

enum enGameLevels { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };
enum enOpTypes { Add = 1, Sub = 2, Multi = 3, Div = 4, oMix = 5 };

struct stGameInfo {
	short Questions;
	enGameLevels QuestionLevel;
	enOpTypes OperatingType;
	short rightAnswers = 0;
	short wrongAnswers = 0;
};

struct QuestionInfo {
	int correctAnswer;
	int userAnswer;
};

short ReadManyQuestions() {
	short questions = 1;
	do {
		cout << "How Many Questions do you want to answer ?:  ";
		cin >> questions;
	} while (questions < 0);

	return questions;
}

enGameLevels ReadGameLevel() {
	short level = 1;
	
	do {
		cout << "Enter Questions Level [1] Easy, [2] Medium, [3] Hard, [4] Mix ?:  ";
		cin >> level;
	} while (level > 4 || level < 0);

	return (enGameLevels)level;
}

enOpTypes ReadOperatingType() {
	short level = 1;

	do {
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Multi, [4] Div, [5] Mix ?:  ";
		cin >> level;
	} while (level > 5 || level < 0);

	return (enOpTypes)level;
}

int ReadAnswer() {
	int answer = 1;
	cin >> answer;
	return answer;
}

int RandomNumber(int From, int To) {
	int number = rand() % (To - From + 1) + From;

	return number;
}

int generateQuestion(stGameInfo gameInfo) {
	switch (gameInfo.QuestionLevel) {
	case enGameLevels::Easy:
		return RandomNumber(1, 10);
	case enGameLevels::Medium:
		return RandomNumber(1, 25);
	case enGameLevels::Hard:
		return RandomNumber(60, 99);
	default:
		return RandomNumber(1, 99);
	}
}

char getTypeSympol(stGameInfo gameInfo) {
	char types[4] = { '+', '-', '*', '/'};

	if (gameInfo.OperatingType == 5)
		return types[RandomNumber(0, 3)];
	else
		return types[gameInfo.OperatingType - 1];
}

int getCorrectAnswer(int Num1, int Num2, char TypeSympol) {
	int result = 0;

	switch (TypeSympol) {
	case '+':
		result = Num1 + Num2;
		break;
	case '-':
		result = Num1 - Num2;
		break;
	case '*':
		result = Num1 * Num2;
		break;
	case '/':
		result = Num1 / Num2;
		break;
	}

	return result;
}

bool checkAnswer(QuestionInfo question) {
	return (question.userAnswer == question.correctAnswer);
}

void screenAlert(bool correct) {
	if (!correct) {
		system("color 2F");
		cout << "\a";
	}
}

void printResultMessage(string Message) {
	cout << "\n\n\t______________________________________\n\n";
	cout << "\t\t" << Message << endl;
	cout << "\t______________________________________\n";
}

string getLevelName(enGameLevels level) {
	string levels[4] = { "Easy", "Medium", "Hard", "Mix" };

	return levels[level - 1];
}

string getTypeName(enOpTypes type) {
	string types[5] = { "Add", "Sub", "Multi", "Div", "Mix" };

	return types[type - 1];
}

void printResultInfo(stGameInfo gameResult) {
	cout << endl << "\tNumber of Questions : " << gameResult.Questions << endl;
	cout << endl << "\tQuestions Level     : " << getLevelName(gameResult.QuestionLevel) << endl;
	cout << endl << "\tOpType              : " << getTypeName(gameResult.OperatingType) << endl;
	cout << endl << "\tNumber of Right Answers : " << gameResult.rightAnswers << endl;
	cout << endl << "\tNumber of Wrong Answers : " << gameResult.wrongAnswers << endl;
	cout << "\t______________________________________\n";
}

void playGame() {
	stGameInfo GameInfo;
	QuestionInfo QuestionInfo;

	GameInfo.Questions = ReadManyQuestions();
	GameInfo.QuestionLevel = ReadGameLevel();
	GameInfo.OperatingType = ReadOperatingType();
	
	for (int question = 1; question <= GameInfo.Questions; question++) {
		int firstPart = generateQuestion(GameInfo);
		int secondPart = generateQuestion(GameInfo);
		char TypeSympol = getTypeSympol(GameInfo);

		cout << "\n\nQuestion [" << question << "/" << GameInfo.Questions << "]:\n\n";
		cout << firstPart << endl;
		cout << secondPart << "\t" << TypeSympol << endl;
		cout << "\n____________\n";
		QuestionInfo.userAnswer = ReadAnswer();
		QuestionInfo.correctAnswer = getCorrectAnswer(firstPart, secondPart, TypeSympol);

		if (checkAnswer(QuestionInfo)) {
			cout << "Right Answer :-)";
			system("color 2E");
			GameInfo.rightAnswers += 1;
		}
		else {
			cout << "\a";
			cout << "Wrong Answer :-(";
			cout << "\nThe right answer is: " << getCorrectAnswer(firstPart, secondPart, TypeSympol);
			system("color 4E");
			GameInfo.wrongAnswers += 1;
		}
	}

	if (GameInfo.wrongAnswers < GameInfo.rightAnswers)
		printResultMessage("Final Result is PASS :-)");
	else
		printResultMessage("Final Result is FAILD :-(");

	printResultInfo(GameInfo);
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void startGame() {
	char playAgain = 'Y';

	do {
		ResetScreen();
		playGame();

		cout << "\nDo you want to play again ? Y/N ?:  ";
		cin >> playAgain;
	} while (playAgain == 'Y' || playAgain == 'y');
}

int main() {
	srand((unsigned)time(NULL));

	startGame();

	return 0;
}
