#pragma once

#include "game.h"
#include "main.h"

int main()
{
	bool playAgain;

	do
	{
		printIntro();
		int wordLength = askForWordLength();
		playGame(wordLength);
		playAgain = askToPlayAgain();
	} while (playAgain);

	return 0;
}

