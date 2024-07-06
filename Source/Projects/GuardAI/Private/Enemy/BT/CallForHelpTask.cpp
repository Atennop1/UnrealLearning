// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/CallForHelpTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/GuardCharacter.h"
#include "Kismet/GameplayStatics.h"

UCallForHelpTask::UCallForHelpTask()
{
	NodeName = "Call For Help";
	IsCalledForHelpKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UCallForHelpTask, IsCalledForHelpKey));
	CallLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCallForHelpTask, CallLocationKey));
	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCallForHelpTask, TargetActorKey), AActor::StaticClass());
}

EBTNodeResult::Type UCallForHelpTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGuardCharacter::StaticClass(), Enemies);
	const AActor *Target = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (!IsValid(Target))
		return EBTNodeResult::Failed;
	
	for (const auto EnemyActor : Enemies)
	{
		const AGuardCharacter *EnemyCharacter = Cast<AGuardCharacter>(EnemyActor);
		AAIController *EnemyController = Cast<AAIController>(EnemyCharacter->GetController());

		if (EnemyActor != OwnerComp.GetAIOwner()->GetPawn())
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(IsCalledForHelpKey.SelectedKeyName, false);
			EnemyController->GetBlackboardComponent()->SetValueAsBool(IsCalledForHelpKey.SelectedKeyName, true);
			EnemyController->GetBlackboardComponent()->SetValueAsVector(CallLocationKey.SelectedKeyName, Target->GetActorLocation());
		}
	}
	
	return EBTNodeResult::Succeeded;
}
