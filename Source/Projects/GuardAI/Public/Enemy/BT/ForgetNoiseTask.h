// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ForgetNoiseTask.generated.h"

UCLASS()
class GUARDAI_API UForgetNoiseTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UForgetNoiseTask();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
