// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DefaultBlock.h"
#include "IInteractableBlock.h"
#include "ShrinkBlock.generated.h"

UCLASS()
class UNREALLEARNING_API AShrinkBlock : public ADefaultBlock, public IInteractableBlock
{
	GENERATED_BODY()

private:
	bool IsDecreasing = true;
	int AmountOfShrinks = 3;
	int CurrentAmountOfShrinks = 0;

protected:
	AShrinkBlock();

public:
	virtual void Interact() override;
	virtual void StartDestroying() override { Super::StartDestroying(); }
	virtual void StopDestroying() override { Super::StopDestroying(); }
};
