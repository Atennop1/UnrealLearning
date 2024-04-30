// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DefaultBlock.h"
#include "IInteractableBlock.h"
#include "GameFramework/Actor.h"
#include "LoggerBlock.generated.h"

UCLASS()
class UNREALLEARNING_API ALoggerBlock : public ADefaultBlock, public IInteractableBlock
{
	GENERATED_BODY()

protected:
	ALoggerBlock();
	
public:
	virtual void StartDestroying() override { Super::StartDestroying(); }
	virtual void StopDestroying() override { Super::StopDestroying(); }
	virtual void Interact() override;
};
