// Copyright Atennop. All Rights Reserved.

#include "Coin.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACoin::PickUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("Coin picked up"));
	Destroy();
}

