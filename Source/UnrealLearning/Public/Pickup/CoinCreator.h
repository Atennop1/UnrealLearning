// Copyright Atennop. All Rights Reserved.

#pragma once

#include "IPickupable.h"
#include "Coin.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinCreator.generated.h"

UCLASS()
class UNREALLEARNING_API ACoinCreator : public AActor, public IPickupable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACoin> Coin;

	UPROPERTY(EditDefaultsOnly)
	FRotator SpawnRotator;
	
	UPROPERTY(EditDefaultsOnly)
	float SpawnPositionZ;
	
	UPROPERTY(EditDefaultsOnly)
	float SpawnPositionSpread;
	
public:
	ACoinCreator();
	virtual void PickUp() override;
};
