// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Sword/AttackTask.h"
#include "AIController.h"
#include "Enemy/GuardCharacter.h"

UAttackTask::UAttackTask()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AGuardCharacter *Character = Cast<AGuardCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	Character->GetAttackingComponent()->Attack();
	return EBTNodeResult::InProgress;
}

void UAttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (!Cast<AGuardCharacter>(OwnerComp.GetAIOwner()->GetPawn())->GetAttackingComponent()->GetIsAttacking())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
