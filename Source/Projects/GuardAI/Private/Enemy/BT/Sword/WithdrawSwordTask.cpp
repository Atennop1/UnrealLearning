// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Sword/WithdrawSwordTask.h"
#include "AIController.h"
#include "Enemy/GuardCharacter.h"

UWithdrawSwordTask::UWithdrawSwordTask()
{
	NodeName = TEXT("Withdraw Sword");
	bNotifyTick = true;
}

EBTNodeResult::Type UWithdrawSwordTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AGuardCharacter *Character = Cast<AGuardCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	Character->GetSwordHoldingComponent()->Withdraw();
	return EBTNodeResult::InProgress;
}

void UWithdrawSwordTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (!Cast<AGuardCharacter>(OwnerComp.GetAIOwner()->GetPawn())->GetSwordHoldingComponent()->GetIsWithdrawing())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
