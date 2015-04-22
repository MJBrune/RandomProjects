// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "SumoGameState.generated.h"

/**
 *
 */
UCLASS()
class SUMOSMACK_API ASumoGameState : public AGameState
{
	GENERATED_BODY()
public:
	ASumoGameState(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "RoundBased")
		int32 restartCounter;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "RoundBased")
		bool restarting;

};
