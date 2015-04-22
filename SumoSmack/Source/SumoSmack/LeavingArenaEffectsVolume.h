// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/PhysicsVolume.h"
#include "LeavingArenaEffectsVolume.generated.h"

/**
 *
 */
UCLASS()
class SUMOSMACK_API ALeavingArenaEffectsVolume : public APhysicsVolume
{
	GENERATED_UCLASS_BODY()
protected:
	virtual void ActorLeavingVolume(AActor* Other) override;
};
