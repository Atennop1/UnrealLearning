// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Activatable.generated.h"

UINTERFACE()
class UActivatable : public UInterface
{
	GENERATED_BODY()
};

class PHYSICSSIMULATION_API IActivatable
{
	GENERATED_BODY()

public:
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
};
