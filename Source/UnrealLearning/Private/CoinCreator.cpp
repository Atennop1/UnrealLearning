// Copyright Atennop. All Rights Reserved.

#include "CoinCreator.h"

ACoinCreator::ACoinCreator()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACoinCreator::PickUp()
{
	GetWorld()->SpawnActor<AActor>(Cast<UClass>(Coin), SpawnPosition, SpawnRotator, FActorSpawnParameters());
}

