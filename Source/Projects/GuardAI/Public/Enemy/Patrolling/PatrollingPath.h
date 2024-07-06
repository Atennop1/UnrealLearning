// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PatrolPoint.h"
#include "GameFramework/Actor.h"
#include "PatrollingPath.generated.h"

UCLASS()
class GUARDAI_API APatrollingPath : public AActor
{
	GENERATED_BODY()

public:
	APatrollingPath();
	APatrolPoint *GetNextPatrolPoint();

private:
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess))
	TArray<APatrolPoint*> Points;
	int CurrentPointIndex = -1;
};
