// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GuardController.generated.h"

UCLASS()
class GUARDAI_API AGuardController : public AAIController
{
	GENERATED_BODY()

public:
	AGuardController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree *BehaviorTree = nullptr;
};
