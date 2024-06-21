// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPickupable.generated.h"

UINTERFACE()
class UPickupable : public UInterface
{
	GENERATED_BODY()
};

class PICKUPSTEST_API IPickupable
{
	GENERATED_BODY()

public:
	virtual void PickUp() = 0;
};
