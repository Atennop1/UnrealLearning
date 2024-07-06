// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CallForHelpTask.generated.h"

UCLASS()
class GUARDAI_API UCallForHelpTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCallForHelpTask();
	
private:
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector IsCalledForHelpKey;

	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector CallLocationKey;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
