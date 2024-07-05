// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/ForgetNoiseTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UForgetNoiseTask::UForgetNoiseTask()
{
	NodeName = "Forget Noise";
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UForgetNoiseTask, BlackboardKey));
}

EBTNodeResult::Type UForgetNoiseTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}


