// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Sword/SheathSwordTask.h"
#include "AIController.h"
#include "Enemy/GuardCharacter.h"

USheathSwordTask::USheathSwordTask()
{
	NodeName = TEXT("Sheath Sword");
	bNotifyTick = true;
}

EBTNodeResult::Type USheathSwordTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AGuardCharacter *Character = Cast<AGuardCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	Character->GetSwordHoldingComponent()->Sheath();
	return EBTNodeResult::InProgress;
}

void USheathSwordTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (!Cast<AGuardCharacter>(OwnerComp.GetAIOwner()->GetPawn())->GetSwordHoldingComponent()->GetIsSheathing())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
