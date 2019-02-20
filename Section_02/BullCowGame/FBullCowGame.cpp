#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame()
{ 
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTry; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "donkey";

	MyMaxTry = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false)// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;  // TODO write function
	}
	else if (false) // if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase; // TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::Ok;
	}
}
// recieves valid guess increments turn and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess.
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar] ) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow 
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}
