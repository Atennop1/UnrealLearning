// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/IsPlayerAliveDecorator.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DemoUMG/Public/Models/Health/HealthComponent.h"

UIsPlayerAliveDecorator::UIsPlayerAliveDecorator()
{
	NodeName = "IsPlayerAlive";
	PlayerKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UIsPlayerAliveDecorator, PlayerKey), AActor::StaticClass());	
}

bool UIsPlayerAliveDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AActor *Character = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	return Character != nullptr && !Character->GetComponentByClass<UHealthComponent>()->IsDead();
}
