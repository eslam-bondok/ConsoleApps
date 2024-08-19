
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string WinnerName;
};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

string Tabs(short NumberOfTabs)
{
	string Tabs = "";

	for (int i = 1; i <= NumberOfTabs; i++)
	{
		Tabs = Tabs + "\t";
	}

	return Tabs;
}

short ReadHowManyRounds()
{
	int RoundsNumber = 0;

	do {

		cout << "How many Rounds? 1 to 10?" << endl;
		cin >> RoundsNumber;

	} while (RoundsNumber < 1 || RoundsNumber > 10);

	return RoundsNumber;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

enGameChoice ReadPlayerChoice()
{
	short PlayerChoice = 0;

	do {

		cout << "\nYour Choice? [1]: Stone [2]: Paper  [3] : Scissor ? ";
		cin >> PlayerChoice;

	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enGameChoice)PlayerChoice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.ComputerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.PlayerChoice == enGameChoice::Scissor) {
			return enWinner::Computer;
			break;
		}

	case enGameChoice::Paper:
		if (RoundInfo.PlayerChoice == enGameChoice::Stone) {
			return enWinner::Computer;
			break;
		}

	case enGameChoice::Scissor:
		if (RoundInfo.PlayerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
			break;
		}
	}

	return enWinner::Player;
}

string WinnerName(enWinner Winner)
{
	string Winners[3] = { "Player", "Computer", "Draw" };
	return Winners[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
	string Choices[3] = { "Stone", "Paper", "Scissor" };
	return Choices[Choice - 1];
}

enWinner GameWinner(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (ComputerWinTimes > PlayerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "_______________________________________________________\n\n";
	cout << Tabs(2) << "                   +++Game Over +++\n";
	cout << Tabs(2) << "_______________________________________________________\n\n";
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n\n________________Round [" << RoundInfo.RoundNumber << "]________________\n\n";

	cout << "Player Choice     : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice   : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Winner Name       : [" << RoundInfo.WinnerName << "]" << endl;
	cout << "__________________________________________\n\n";

	SetWinnerScreenColor(RoundInfo.Winner);

}

stGameResults FillGameResults(short HowManyRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = HowManyRounds;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.Winner = GameWinner(PlayerWinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.Winner);

	return GameResults;

}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "____________________[Game Results]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds         : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player Win Times    : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer Win Times  : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times          : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Game Winner         : [" << GameResults.WinnerName << "]" << endl;
	cout << Tabs(2) << "_______________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.Winner);
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	int PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\n\nRound [" << GameRound << "] Begins : \n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}
	return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do {

		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << "\nDo You Want to Play Again? Y/N?";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}