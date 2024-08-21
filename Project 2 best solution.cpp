
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum enQuestionsLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4};
enum enOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enQuestionsLevel QuestionLevel;
	enOperationType OperationType;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionLevel;
	enOperationType OperationType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass = false;
};

int RandomNumer(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

short HowManyQuestions()
{
	short NumberOfQuestions = 0;

	do {

		cout << "How Many Questions do you want to answer? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 100);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;

	do {
		cout << "Enter Questions Level: [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OperationType = 0;

	do {

		cout << "Enter Operation Type : [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

int SimpleCalculator(int number1, int number2, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return number1 + number2;
	case enOperationType::Sub:
		return number1 - number2;
	case enOperationType::Mul:
		return number1 * number2;
	case enOperationType::Div:
		return number1 / number2;
	default:
		return number1 + number2;
	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
		QuestionLevel = (enQuestionsLevel)RandomNumer(1, 3);

	if (OperationType == enOperationType::MixOp)
		OperationType == (enOperationType)RandomNumer(1, 4);

	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::Easy:
		Question.Number1 = RandomNumer(1, 10);
		Question.Number2 = RandomNumer(1, 10);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;

	case enQuestionsLevel::Med:
		Question.Number1 = RandomNumer(10, 50);
		Question.Number2 = RandomNumer(10, 50);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;

	case enQuestionsLevel::Hard:
		Question.Number1 = RandomNumer(50, 100);
		Question.Number2 = RandomNumer(50, 100);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;
	}
}

void GenerateQuizzQuestions(stQuizz &Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OperationType);
	}
}

string GetOpTypeSymbol(enOperationType OpType)
{
	string OpTypes[4] = { "+", "-", "*", "/" };
	return OpTypes[OpType - 1];
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << "\n________________________\n";
}

int ReadQuestionAnswer()
{
	int Answer;
	cin >> Answer;
	return Answer;
}

void SetColorScreen(bool IsRight)
{
	if (IsRight)
		system("color 2F");
	else
		system("color 4F");
}

void CorrectTheQuestionAnswer(stQuizz &Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].CorrectAnswer != Quizz.QuestionList[QuestionNumber].PlayerAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer" << endl;
		cout << "The Right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer";
	}

	SetColorScreen(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionsAnswer(stQuizz &Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool IsPass)
{
	if (IsPass)
		return "Pass";
	else
		return "Fail";
}

string GetQuestionsLevelText(enQuestionsLevel Level)
{
	string Levels[4] = { "Easy", "Med", "Hard", "Mix" };
	return Levels[Level - 1];
}

string GetOperatorName(enOperationType Operation)
{
	string Operations[5] = { "Add", "Sub", "Mul", "Div", "Mix" };
	return Operations[Operation - 1];
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n____________________________\n\n";
	cout << "Final Results is " << GetFinalResultsText(Quizz.IsPass);
	cout << "\n____________________________\n\n";

	cout << "Number of Questions     : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level         : " << GetQuestionsLevelText(Quizz.QuestionLevel) << endl;
	cout << "Operation Type          : " << GetOperatorName(Quizz.OperationType) << endl;
	cout << "Number of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "\n____________________________\n\n";
}

void PlayGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = HowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OperationType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionsAnswer(Quizz);
	PrintQuizzResults(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do {

		ResetScreen();
		PlayGame();

		cout << "Do You Want to Play Again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}