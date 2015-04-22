// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SumoSmack.h"
#include "Engine.h"
#include "SumoSmackGameMode.h"
#include "SumoSmackCharacter.h"
#include "SumoGameState.h"

ASumoSmackGameMode::ASumoSmackGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	restartTime = 3;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/ThirdPerson/Blueprints/SumoSmackHud"));
	if (PlayerHUDBPClass.Class != NULL)
	{
		HUDClass = PlayerHUDBPClass.Class;
	}

	GameStateClass = ASumoGameState::StaticClass();
}

//void ASumoSmackGameMode::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	// Replicate to everyone
//	DOREPLIFETIME(ASumoSmackGameMode, restartCounter);
//	DOREPLIFETIME(ASumoSmackGameMode, restarting);
//}

void ASumoSmackGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	int32 PlayersAlive = 0;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (Iterator->Get()->GetPawn())
		{
			PlayersAlive++;
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%d"), PlayersAlive));
	if (PlayersAlive <= 1 && !GetGameState<ASumoGameState>()->restarting)
	{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			if (Role >= ROLE_Authority)
			{
				if (Iterator->Get()->GetPawn())
				{
					Iterator->Get()->GetPawn()->Destroy();
				}
			}
		}
		GetGameState<ASumoGameState>()->restarting = true;
		if (Role >= ROLE_Authority)
		{
			GetWorldTimerManager().SetTimer(this, &ASumoSmackGameMode::restartRound, restartTime, false);
		}
	}

	if (GetGameState<ASumoGameState>()->restarting)
	{
		GetGameState<ASumoGameState>()->restartCounter = restartTime - GetWorldTimerManager().GetTimerElapsed(this, &ASumoSmackGameMode::restartRound);
	}
}

void ASumoSmackGameMode::restartRound()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		RestartPlayer(Iterator->Get());
	}

	GetGameState<ASumoGameState>()->restarting = false;
}