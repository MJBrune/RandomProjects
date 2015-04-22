// Fill out your copyright notice in the Description page of Project Settings.

#include "SumoSmack.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "SumoGameState.h"



ASumoGameState::ASumoGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = true;
	restartCounter = 0;
	restarting = false;
}

void ASumoGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(ASumoGameState, restartCounter);
	DOREPLIFETIME(ASumoGameState, restarting);
}