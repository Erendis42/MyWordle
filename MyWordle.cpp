// MyWordle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>
#include <random>
#include <Windows.h>

#include "MyWordle.h"

using namespace std;

// this line is needed to change text color in the PlayGame function
const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// word length
int lengthOfWord = 5;

// letters in the latin alphabet
int lengthOfAlphabet = 26;

// letters of the latin alphabet in lowercase
string alphabet = "abcdefghijklmnopqrstuvwxyz";

// number of guesses you have
const int GUESSES = 6;

int main()
{   
    string filename = "words.txt";
    vector<string> vectorOfWords;
    
    ReadWordList(filename, vectorOfWords);

    if (vectorOfWords.size() == 0)
    {
        cout << "Unable to initialize game -- the wordlist is empty!" << endl;
        return 0;
    }

    bool wantsToPlay = true;
    bool won = false;

    string wordToGuess;

    while (wantsToPlay) {
        wordToGuess = GetRandomWord(vectorOfWords);

        system("CLS");
        cout << "Guess the word I'm thinking of." << endl;

        PlayGame(GUESSES, wordToGuess, won);

        char again;
        cout << "Do you want to play again? (Y/N)" << ' ';
        cin >> again;

        if(again != 'y' && again != 'Y')
        {
            wantsToPlay = false;
        }
    }
}

void PlayGame(int numberOfRounds, string& wordToGuess, bool& won)
{
    won = false;
    string colorCodeLong = "xxxxxxxxxxxxxxxxxxxxxxxxxx";
    string colorCodeShort = "xxxxx";

    for (int i = 0; i < numberOfRounds; i++) {
        SetConsoleTextAttribute(hConsole, BlackBack | AquaFore);
        cout << endl << "Enter your guess. You have " << numberOfRounds - i << \
            " chance(s) left." << endl;
        SetConsoleTextAttribute(hConsole, BlackBack | GrayFore);

        string userInput;

        GetGuess(userInput);

        if (wordToGuess == userInput)        
        {
            colorCodeShort = "ggggg";

            PrintWordByColorCode(userInput, colorCodeShort, lengthOfWord);
            
            cout << "You guessed it! Congratulations!" << endl;
            won = true;
            break;
        }
        else {
            colorCodeShort = "xxxxx";
            CheckForLettersFound(wordToGuess, userInput, colorCodeShort, colorCodeLong);
            PrintWordByColorCode(userInput, colorCodeShort, lengthOfWord);
            PrintWordByColorCode(alphabet, colorCodeLong, lengthOfAlphabet);
        }       

        // TODO (if there is enough time): output the word colored with yellow and green for 
        // found characters just like the real thing
    }

    if (!won) {
        cout << "You lose. The word you had to guess was: " << wordToGuess << endl;
    }
}

void PrintWordByColorCode(string& word, string& colorCode, int& lengthOfColorCodeString) {
    for (int i = 0; i < lengthOfColorCodeString; i++)
    {
        switch (colorCode[i])
        {
        case 'g':
            SetConsoleTextAttribute(hConsole, BlackBack | LimeFore);
            break;
        case 'y':
            SetConsoleTextAttribute(hConsole, BlackBack | YellowFore);
            break;
        case 'o':
            SetConsoleTextAttribute(hConsole, BlackBack | SilverFore);
            break;
        default:
            SetConsoleTextAttribute(hConsole, BlackBack | GrayFore);
            break;
        }
        cout << word.at(i);
    }

    SetConsoleTextAttribute(hConsole, BlackBack | GrayFore);

    cout << endl;
}

string GetRandomWord(vector<string>& vectorOfWords) {
    int sizeOfWordList = (int) vectorOfWords.size();

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, sizeOfWordList - 1);

    int r = uni(rng);

    string wordToGuess = vectorOfWords.at(r);

    return wordToGuess;
}

void ReadWordList(string& filename, vector<string>& vectorOfWords)
{
    string word = "";
    fstream inFile;
    inFile.open(filename, ios::in);
    if (inFile.is_open())
    {
        while (getline(inFile, word))
        {
            // skip empty lines
            if (word.length() > 0)
            {
                vectorOfWords.push_back(word);
            }
        }
    }
    else {
        cout << "File not found." << endl;
    }
}

void CheckForLettersFound(string& wordToGuess, string& userInput, string& colorCodeShort, string& colorCodeLong)
{
    int indexOfCharInAlphabet = 0;

    char shortCode = 'x';

    for (int i = 0; i < lengthOfWord; i++)
    {
        indexOfCharInAlphabet = (int) alphabet.find(userInput[i]);

        for (int j = 0; j < lengthOfWord; j++)
        {

            if (userInput[i] == wordToGuess[j]) {
                if (i == j) {
                    colorCodeShort[i] = 'g';
                    colorCodeLong[indexOfCharInAlphabet] = 'g';
                }
                else
                {
                    colorCodeShort[i] = 'y';
                    
                    if (colorCodeLong[indexOfCharInAlphabet] != 'g')
                    {
                        colorCodeLong[indexOfCharInAlphabet] = 'y';
                    }
                }
            }
            else
            {
                if (colorCodeLong[indexOfCharInAlphabet] != 'g' && colorCodeLong[indexOfCharInAlphabet] != 'y') {
                    colorCodeLong[indexOfCharInAlphabet] = 'o';
                }
            }
        }
    }
}

bool ContainsOnlyLetters(string const& str) {
    return regex_match(str, regex("^[A-Za-z]+$"));
}

void GetGuess(string& userInput)
{
    bool isInputFormatCorrect = false;
    while (!isInputFormatCorrect) {
        cin >> userInput;

        // sanitize input (check if length == 5, turn it into all lowercase)
        if (userInput.length() == 5 && ContainsOnlyLetters(userInput)) {
            isInputFormatCorrect = true;
            transform(userInput.begin(), userInput.end(), userInput.begin(), (int(*)(int)) tolower);
            /* explicit cast to resolve the ambiguity
             * instructs the compiler to use tolower function
             * from <cctype> instead of <locale>
             */
        }
        else
        {
            SetConsoleTextAttribute(hConsole, BlackBack | RedFore);
            cout << "Wrong format. Only 5 letter words are accepted." << endl;
            SetConsoleTextAttribute(hConsole, BlackBack | GrayFore);
        }
    }
}

bool IsEmpty(fstream& pFile)
{
    return pFile.peek() == fstream::traits_type::eof();
}
