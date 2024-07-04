// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Movement/UnfocusTask.h"
#include "AIController.h"

UUnfocusTask::UUnfocusTask()
{
	NodeName = TEXT("Unfocus");
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UUnfocusTask, BlackboardKey), AActor::StaticClass());
}

EBTNodeResult::Type UUnfocusTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController *AIController = OwnerComp.GetAIOwner();
	AIController->GetPawn()->bUseControllerRotationYaw = false;
	AIController->ClearFocus(EAIFocusPriority::Gameplay);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}