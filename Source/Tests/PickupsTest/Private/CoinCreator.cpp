// Copyright Atennop. All Rights Reserved.

#include "CoinCreator.h"

ACoinCreator::ACoinCreator()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACoinCreator::PickUp()
{
	GetWorld()->SpawnActor<ACoin>(Coin,
		FVector(FMath::RandRange(0.0f, SpawnPositionSpread) * (FMath::RandBool() ? -1 : 1),
		FMath::RandRange(0.0f, SpawnPositionSpread) * (FMath::RandBool() ? -1 : 1), SpawnPositionZ),
		SpawnRotator);
}

