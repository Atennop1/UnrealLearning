// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WithdrawSwordTask.generated.h"

UCLASS()
class GUARDAI_API UWithdrawSwordTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UWithdrawSwordTask();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
