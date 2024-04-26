// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IBlock.h"
#include "GameFramework/Actor.h"
#include "DefaultBlock.generated.h"

UCLASS()
class UNREALLEARNING_API ADefaultBlock : public AActor, public IBlock
{
	GENERATED_BODY()

private:
	ADefaultBlock();
	
public:
	virtual void Destroy() override;
};
