/*This is the console executable that makes use of the BulCow class
This acts as the view in a mvc pattern, and is responseable for all
user interaction. for game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h" 

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game.


// the entry point for the application.
int main()  
{
		
		bool bWantsToPlayAgain = false;
		do {
		PrintIntro();
		PlayGame();
		} while (AskToPlayAgain());
	return 0;
}
// introduce the game.
	void PrintIntro() 
{
	std::cout << "\n\n Welcome to Bulls and Cows a fun word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram i'm thinking of?\n";
	std::cout << std::endl;
	return;
}
	
	// starts the game.
	void PlayGame()
{
		BCGame.Reset();
		int32 MaxTries = BCGame.GetMaxTries();

	// Loop asking for the guesses while the game is not won
		// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { 
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and recieve counts.
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

	// loop continually until the user gives a valid guess.
	FText GetValidGuess() // TODO change to get valid guess
	{
		FText Guess = "";
		EGuessStatus Status = EGuessStatus::Invalid_Status;
		do {
			// get a guess from the player
			int32 CurrentTry = BCGame.GetCurrentTry();
			std::cout << "Try" << CurrentTry << ". Enter your guess: ";
			std::getline(std::cin, Guess);

			Status = BCGame.CheckGuessValidity(Guess);
			switch (Status)
			{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter an Isogram word (this is a word that has no letters Reapeated in it).\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "You have used uppercase letters in your guess please only use lowercase letters or turn off caps lock. \n";
				break;
			default:
				// asume the guess is vailid
				break;
			}
			std::cout << std::endl;
		} while (Status != EGuessStatus::Ok); // Keep looping until we get no errors.
		return Guess;
	}

	bool AskToPlayAgain()
	{
		std::cout << "Do you want to play again with the same hidden word y or n? ";
		FText Response = "";
		std::getline(std::cin, Response);
		return (Response[0] == 'y' || Response[0] == 'Y');
	}

	void PrintGameSummary()
	{
		if (BCGame.IsGameWon())
		{
			std::cout << "WELL DONE - YOU WIN!\n\n";
		}
		else {
			std::cout << "Better luck next time!\n\n";
		}
	}