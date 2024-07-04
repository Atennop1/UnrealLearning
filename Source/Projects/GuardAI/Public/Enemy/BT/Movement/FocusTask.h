// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FocusTask.generated.h"

UCLASS()
class GUARDAI_API UFocusTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UFocusTask();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
