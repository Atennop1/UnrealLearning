// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GetNextPatrolPointTask.generated.h"

UCLASS()
class GUARDAI_API UGetNextPatrolPointTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UGetNextPatrolPointTask();
	
private:
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess))
	FBlackboardKeySelector WaitingTimeBlackboardKey;

	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess))
	FBlackboardKeySelector PointLocationBlackboardKey;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
