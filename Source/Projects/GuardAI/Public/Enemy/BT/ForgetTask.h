// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ForgetTask.generated.h"

UCLASS()
class GUARDAI_API UForgetTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UForgetTask();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
