/*
This is the console executable which makes use of BullCowGame class (game logic in here).
This acts as the view in an MVC pattern and is responsible for all user interation.
*/
#pragma once

#include <iostream>
#include <string>
#include "game.h"

#include "BullCowGame.h"

using FText = std::string;
using int32 = int;

FText getValidGuess();

BullCowGame bullCowGame;

void printIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n\n";
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << bullCowGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
}

void printGameSummary()
{
	if (bullCowGame.IsGameWon())
	{
		std::cout << "Congratulations! You Won!\n";
	}
	else
	{
		std::cout << "Unlucky, you lost - better luck next time!\n";
	}
}

bool askToPlayAgain()
{
	FText playAgain;
	std::cout << "Would you like to play again? [y/n]\n";
	std::getline(std::cin, playAgain);

	return (playAgain[0] == 'y' || playAgain[0] == 'Y');
}

void playGame(int32 wordLength)
{
	bullCowGame.Reset(wordLength);

	while (!bullCowGame.IsGameWon() && bullCowGame.GetCurrentTry() <= bullCowGame.GetMaxTries())
	{
		FText guess = getValidGuess(); 

		BullCowCount bullCowCount = bullCowGame.SubmitValidGuess(guess);
		std::cout << "Bulls = " << bullCowCount.bulls << " Cows = " << bullCowCount.cows << "\n\n";
	}
	
	printGameSummary();
}

int askForWordLength()
{
	bool validInput = false;
	int32 wordLen = 0;
	FText wordLength = "";
	do 
	{
		std::cout << "Please enter the word length you wish to guess [3/4/5/6/7]:";

		std::getline(std::cin, wordLength);
		wordLen = bullCowGame.isValidWordLength(wordLength);
		
		if (wordLen != 0)
		{
			std::cout << "OK, can you guess the " << wordLen << " letter word I'm thinking of?!\n";
			validInput = true;
		}
		else
		{
			std::cout << "You entered an invalid word length - try again!\n";
		}

	} while (!validInput);

	return wordLen;
}

FText getValidGuess()
{
	EGuessStatus status = EGuessStatus::Invalid_Status;
	FText guess = "";

	do
	{
		std::cout << "Try number " << bullCowGame.GetCurrentTry() << " of " << bullCowGame.GetMaxTries() << "\n";
		std::cout << "Enter your guess : ";
		std::getline(std::cin, guess);
		status = bullCowGame.CheckGuessValidity(guess);

		switch (status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << bullCowGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		default:
			break;
		}

	} while (status != EGuessStatus::OK);
	
	return guess;
}