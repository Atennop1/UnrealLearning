// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Breaker/BreakerCharacter.h"
#include "Patrolling/CharacterPatrollingComponent.h"
#include "GuardCharacter.generated.h"

UCLASS()
class GUARDAI_API AGuardCharacter : public ABreakerCharacter
{
	GENERATED_BODY()

public:
	AGuardCharacter();

	UCharacterPatrollingComponent *GetPatrollingComponent() const { return PatrollingComponent; }
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterPatrollingComponent *PatrollingComponent = nullptr;
};
