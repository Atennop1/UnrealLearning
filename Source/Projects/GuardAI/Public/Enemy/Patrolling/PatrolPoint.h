// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPoint.generated.h"

UCLASS()
class GUARDAI_API APatrolPoint : public AActor
{
	GENERATED_BODY()

public:
	APatrolPoint();
	float GetWaitingTime() const { return WaitingTime; }

private:
	UPROPERTY(EditAnywhere)
	float WaitingTime = 5.0f;
};
