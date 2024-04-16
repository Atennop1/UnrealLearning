// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPickupable.generated.h"

UINTERFACE()
class UPickUpable : public UInterface
{
	GENERATED_BODY()
};

class UNREALLEARNING_API IPickUpable
{
	GENERATED_BODY()

public:
	virtual void PickUp() = 0;
};
