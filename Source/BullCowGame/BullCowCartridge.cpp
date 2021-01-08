// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    ProcessGuess(Input);
}

void UBullCowCartridge::SetupGame()
{
    TArray<FString> ValidWords;

    for (FString Word : Words)
    {
        if (Word.Len() > 3 && IsIsogram(Word) && Word.Len() < 5) {
            ValidWords.Emplace(Word);
        }
    }
    

    HiddenWord = ValidWords[rand() % ValidWords.Num()];
    Lives = 4;
    bGameOver = false;
    PrintLine(TEXT("Welcome!"));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess. \n Press enter to continue"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters :)"));
        return;
    }

    if (bGameOver) {
        ClearScreen();
        SetupGame();
        bGameOver = false;
        return;
    }
    if (Guess == HiddenWord) {
        PrintLine(TEXT("You have won!"));
        EndGame();
    }
    else {
        if (Lives == 0)
        {
            PrintLine(TEXT("You have lost"));
            PrintLine(TEXT("The word was: %s"), *HiddenWord);
            EndGame();
        }
        PrintLine(TEXT("Try again, you have %i lives left"), Lives);
        if (Lives < 4)
        {
            GiveClue(Guess);
        }
        --Lives;
    }
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 c = i + 1; c < Word.Len(); c++)
        {
            if (Word[i] == Word[c])
            {
                return false;
            }
        }
        
    }
    return true;
}

void UBullCowCartridge::GiveClue(FString Word)
{
    FString matches = TEXT("");
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 c = 0; c < HiddenWord.Len(); c++)
        {
            if (Word[i] == HiddenWord[c])
            {
                matches = matches + Word[i];
            }
        }
        
    }
    if (matches.Len())
    {
        PrintLine(TEXT("Clue: These letters you entered: %s\n are found in the secret word."), *matches);
    }
    else 
    {
        PrintLine(TEXT("No letters matched"));
    }
};