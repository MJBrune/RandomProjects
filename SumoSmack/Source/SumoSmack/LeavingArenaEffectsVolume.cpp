// Fill out your copyright notice in the Description page of Project Settings.

#include "SumoSmack.h"
#include "LeavingArenaEffectsVolume.h"


ALeavingArenaEffectsVolume::ALeavingArenaEffectsVolume(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ALeavingArenaEffectsVolume::ActorLeavingVolume(AActor* Other)
{
	Other->Destroy();
}
