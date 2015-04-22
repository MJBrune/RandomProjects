// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "SumoSmackGameMode.generated.h"

UCLASS(minimalapi)
class ASumoSmackGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASumoSmackGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;
	virtual void restartRound();
	//UPROPERTY(/*Replicated, */BlueprintReadWrite, Category = "RoundBased")
	//int32 restartCounter;
	float restartTime;
	//UPROPERTY(/*Replicated, */BlueprintReadWrite, Category = "RoundBased")
	//bool restarting;
};