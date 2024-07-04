// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Breaker/BreakerCharacter.h"
#include "Components/CharacterAttackingComponent.h"
#include "Components/CharacterPatrollingComponent.h"
#include "Components/CharacterSwordHoldingComponent.h"
#include "GuardCharacter.generated.h"

UCLASS()
class GUARDAI_API AGuardCharacter : public ABreakerCharacter
{
	GENERATED_BODY()

public:
	AGuardCharacter();

	UCharacterPatrollingComponent *GetPatrollingComponent() const { return PatrollingComponent; }
	UCharacterAttackingComponent *GetAttackingComponent() const { return AttackingComponent; }
	UCharacterSwordHoldingComponent *GetSwordHoldingComponent() const { return SwordHoldingComponent; }
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterPatrollingComponent *PatrollingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterAttackingComponent *AttackingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCharacterSwordHoldingComponent *SwordHoldingComponent = nullptr;
};
