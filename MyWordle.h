#pragma once

bool ContainsOnlyLetters(std::string const& str);

void CheckForLettersFound(std::string& wordToGuess, std::string& userInput, std::string& colorCodeShort, std::string& colorCodeLong);

void ReadWordList(std::string& filename, std::vector<std::string>& vectorOfWords);

void GetGuess(std::string& userInput);

std::string GetRandomWord(std::vector<std::string>& stdvectorOfWords);

void PlayGame(int numberOfRounds, std::string& wordToGuess, bool& won);

bool IsEmpty(std::fstream& pFile);

void PrintWordByColorCode(std::string& word, std::string& colorCode, int& lengthOfColorCodeString);

enum ConsoleColors
{
	BlackFore = 0,
	MaroonFore = FOREGROUND_RED,
	GreenFore = FOREGROUND_GREEN,
	NavyFore = FOREGROUND_BLUE,
	TealFore = FOREGROUND_GREEN | FOREGROUND_BLUE,
	OliveFore = FOREGROUND_RED | FOREGROUND_GREEN,
	PurpleFore = FOREGROUND_RED | FOREGROUND_BLUE,
	GrayFore = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	SilverFore = FOREGROUND_INTENSITY,
	RedFore = FOREGROUND_INTENSITY | FOREGROUND_RED,
	LimeFore = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	BlueFore = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	AquaFore = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	YellowFore = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	FuchsiaFore = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	WhiteFore = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

	BlackBack = 0,
	MaroonBack = BACKGROUND_RED,
	GreenBack = BACKGROUND_GREEN,
	NavyBack = BACKGROUND_BLUE,
	TealBack = BACKGROUND_GREEN | BACKGROUND_BLUE,
	OliveBack = BACKGROUND_RED | BACKGROUND_GREEN,
	PurpleBack = BACKGROUND_RED | BACKGROUND_BLUE,
	GrayBack = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	SilverBack = BACKGROUND_INTENSITY,
	RedBack = BACKGROUND_INTENSITY | BACKGROUND_RED,
	LimeBack = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
	BlueBack = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
	AquaBack = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
	YellowBack = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
	FuchsiaBack = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
	WhiteBack = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
};
