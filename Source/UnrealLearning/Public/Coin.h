// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IPickupable.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class UNREALLEARNING_API ACoin : public AActor, public IPickupable
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	
public:	
	ACoin();
	virtual void PickUp() override;
};
