// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    ClearScreen();
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    }
    if (Input == HiddenWord) {
        PrintLine(TEXT("You have won!"));
        EndGame();
    }
    else {
        if (Lives == 0)
        {
            PrintLine(TEXT("You have lost"));
            EndGame();
        }
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
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