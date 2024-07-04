// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SetMovementSpeedTask.generated.h"

UCLASS()
class GUARDAI_API USetMovementSpeedTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USetMovementSpeedTask();
	
private:
	UPROPERTY(EditInstanceOnly)
	float NewSpeed = 500;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
