// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Movement/SetMovementSpeedTask.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USetMovementSpeedTask::USetMovementSpeedTask()
{
	NodeName = TEXT("Set Movement Speed");
}

EBTNodeResult::Type USetMovementSpeedTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ACharacter *Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	Character->GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}