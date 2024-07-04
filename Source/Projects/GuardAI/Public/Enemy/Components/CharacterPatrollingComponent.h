// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Patrolling/PatrollingPath.h"
#include "Components/ActorComponent.h"
#include "CharacterPatrollingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterPatrollingComponent();
	
	void Init(APatrollingPath *NewPatrollingPath) { PatrollingPath = NewPatrollingPath; }
	APatrollingPath *GetPatrollingPath() const { return PatrollingPath; }

private:
	UPROPERTY(EditInstanceOnly)
	APatrollingPath *PatrollingPath = nullptr;
};
