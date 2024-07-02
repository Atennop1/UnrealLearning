// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/GetNextPatrolPointTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/GuardCharacter.h"

UGetNextPatrolPointTask::UGetNextPatrolPointTask()
{
	WaitingTimeBlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UGetNextPatrolPointTask, WaitingTimeBlackboardKey));
	PointLocationBlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UGetNextPatrolPointTask, PointLocationBlackboardKey));
}

EBTNodeResult::Type UGetNextPatrolPointTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController *Controller = OwnerComp.GetAIOwner();
	const AGuardCharacter *Character = Cast<AGuardCharacter>(Controller->GetPawn());
	
	if (!IsValid(Character))
		return EBTNodeResult::Failed;

	const APatrolPoint *Point = Character->GetPatrollingComponent()->GetPatrollingPath()->GetNextPatrolPoint();
	Controller->GetBlackboardComponent()->SetValueAsFloat(WaitingTimeBlackboardKey.SelectedKeyName, Point->GetWaitingTime());
	Controller->GetBlackboardComponent()->SetValueAsVector(PointLocationBlackboardKey.SelectedKeyName, Point->GetActorLocation());
	return EBTNodeResult::Succeeded;
}
