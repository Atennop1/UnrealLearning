// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsPlayerAliveDecorator.generated.h"

UCLASS()
class GUARDAI_API UIsPlayerAliveDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UIsPlayerAliveDecorator();
	
private:
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess))
	FBlackboardKeySelector PlayerKey;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
