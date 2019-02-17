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

FBullCowGame BCGame; // instantiate a new game.


// the entry point for the application.
int main()  
{
		PrintIntro();
		bool bWantsToPlayAgain = false;
		do {
		PlayGame();
		} while (AskToPlayAgain());
	return 0;
}
// introduce the game.
	void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows a fun word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram i'm thinking of?\n";
	std::cout << std::endl;
	return;
}
	
	// starts the game.
	void PlayGame()
{
		// BCGame.Reset();
		int32 MaxTries = BCGame.GetMaxTries();
		std::cout << MaxTries << std::endl;

	// Loop for the number of turns asking for the guesses.
	for (int32 count = 1; count <= MaxTries; count++) 
	{ // TODO change from for to while
		FText Guess = GetValidGuess(); // TODO make loop checking valid.

		// submit valid guess to the game, and recieve counts.
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	// TODO summerise game. 
}

	// loop continually until the user gives a valid guess.
	FText GetValidGuess() // TODO change to get valid guess
	{
		EGuessStatus Status = EGuessStatus::Invalid_Status;
		do {
			// get a guess from the player
			int32 CurrentTry = BCGame.GetCurrentTry();
			std::cout << "Try" << CurrentTry << ". Enter your guess: ";
			FText Guess = "";
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
				return Guess;
			}
		} while (Status != EGuessStatus::Ok); // Keep looping until we get no errors.
 
	}

	bool AskToPlayAgain()
	{
		std::cout << "Do you want to play again y or n? ";
		FText Response = "";
		std::getline(std::cin, Response);
		return (Response[0] == 'y' || Response[0] == 'Y');
	}
