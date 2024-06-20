// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IBlock.h"
#include "UObject/Interface.h"
#include "IInteractableBlock.generated.h"

UINTERFACE()
class UInteractableBlock : public UBlock
{
	GENERATED_BODY()
};

class MINECRAFT_API IInteractableBlock : public IBlock
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;
};
