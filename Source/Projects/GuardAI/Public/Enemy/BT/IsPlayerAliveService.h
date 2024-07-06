// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTService.h"
#include "IsPlayerAliveService.generated.h"

UCLASS()
class GUARDAI_API UIsPlayerAliveService : public UBTService
{
	GENERATED_BODY()

public:
	UIsPlayerAliveService();
	
private:
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess))
	FBlackboardKeySelector IsPlayerAliveKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
