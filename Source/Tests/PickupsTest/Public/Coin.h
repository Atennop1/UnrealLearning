// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IPickupable.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class PICKUPSTEST_API ACoin : public AActor, public IPickupable
{
	GENERATED_BODY()

public:	
	ACoin();
	virtual void PickUp() override;
};
