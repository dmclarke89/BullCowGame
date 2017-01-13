/* The game logic (no view code or direct user interation).
   The game is a simple guess the word game based on Mastermind. */
#pragma once

#include <string>

using FString = std::string;
using int32 = int;

struct BullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class BullCowGame
{
public :

	BullCowGame();

	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	int32 GetMaxTries() const;
	bool IsGameWon() const;
	int32 isValidWordLength(FString wordLength) const;
	EGuessStatus CheckGuessValidity(FString guess) const;

	void Reset(int32 wordLength);
	BullCowCount SubmitValidGuess(FString guess);

private:
	int32 currentTries;
	FString hiddenWord;
	bool gameIsWon;

	bool isLowercase(FString guess) const;
	bool isIsogram(FString guess) const;

};