// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/ForgetTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UForgetTask::UForgetTask()
{
	NodeName = "Forget";
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UForgetTask, BlackboardKey));
}

EBTNodeResult::Type UForgetTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}