#pragma once

#include "BullCowGame.h"
#include <map>
#include <sstream>

#define TMap std::map
using int32 = int;

constexpr int32 minWordLength = 3;
constexpr int32 maxWordLength = 7;

BullCowGame::BullCowGame()
{
}

int32 BullCowGame::GetCurrentTry() const
{
	return currentTries;
}

int32 BullCowGame::GetHiddenWordLength() const
{
	return hiddenWord.length();
}

bool BullCowGame::IsGameWon() const
{
	return gameIsWon;
}

int32 BullCowGame::GetMaxTries() const
{
	TMap<int32, int32> wordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7, 20} };

	return wordLengthToMaxTries[GetHiddenWordLength()];
}


bool BullCowGame::isLowercase(FString guess) const
{
	// Treat 0 letter guesses as lowercase.
	if (guess.length() == 0)
	{
		return true;
	}

	for (auto letter : guess)
	{
		if (!islower(letter))
		{
			return false;
		}
	}

	return true;
}

bool BullCowGame::isIsogram(FString guess) const
{
	// Treat 0 and 1 letter guesses as isogram.
	if (guess.length() <= 1)
	{
		return true;
	}
	
	TMap<char, bool> letterSeen;

	for (auto letter : guess)
	{
		letter = tolower(letter);
		if (!letterSeen[letter])
		{
			letterSeen[letter] = true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

EGuessStatus BullCowGame::CheckGuessValidity(FString guess) const
{
	if (guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!isIsogram(guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!isLowercase(guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

int32 BullCowGame::isValidWordLength(FString wordLength) const
{
	int32 wordLen = 0;

	// convert to int.
	std::stringstream(wordLength) >> wordLen;

	if (wordLen >= minWordLength && wordLen <= maxWordLength)
	{
		return wordLen;
	}
	else
	{
		return 0; // TODO - should probably return something "better" here...
	}
}

void BullCowGame::Reset(int32 wordLength)
{
	const FString HIDDEN_WORD_3 = "cat";
	const FString HIDDEN_WORD_4 = "lion";
	const FString HIDDEN_WORD_5 = "tiger";
	const FString HIDDEN_WORD_6 = "badger";
	const FString HIDDEN_WORD_7 = "dolphin";

	switch (wordLength)
	{
	case 3:
		hiddenWord = HIDDEN_WORD_3;
		break;
	case 4:
		hiddenWord = HIDDEN_WORD_4;
		break;
	case 5:
		hiddenWord = HIDDEN_WORD_5;
		break;
	case 6:
		hiddenWord = HIDDEN_WORD_6;
		break;
	case 7:
		hiddenWord = HIDDEN_WORD_7;
		break;
	default:
		hiddenWord = HIDDEN_WORD_3;
		break;
	}

	currentTries = 1;
	gameIsWon = false;
}

BullCowCount BullCowGame::SubmitValidGuess(FString guess)
{
	BullCowCount bullCowCount;

	currentTries++;
	int32 wordLength = hiddenWord.length();
	
	for (int32 hiddenWordChar = 0; hiddenWordChar < wordLength; hiddenWordChar++)
	{
		for (int32 guessChar = 0; guessChar < wordLength; guessChar++)
		{
			if (guess[guessChar] == hiddenWord[hiddenWordChar])
			{
				if (hiddenWordChar == guessChar)
				{
					bullCowCount.bulls++;
				}
				else
				{
					bullCowCount.cows++;
				}
			}
		}
	}

	if (bullCowCount.bulls == wordLength)
	{
		gameIsWon = true;
	}
	else
	{
		gameIsWon = false;
	}

	return bullCowCount;
}
