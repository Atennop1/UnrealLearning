// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/IsPlayerAliveService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DemoUMG/Public/Models/Health/HealthComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UIsPlayerAliveService::UIsPlayerAliveService()
{
	NodeName = "Is Player Alive Updating";
	IsPlayerAliveKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UIsPlayerAliveService, IsPlayerAliveKey));	
}

void UIsPlayerAliveService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	const ACharacter *Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	const UHealthComponent *Health = Character != nullptr ? Character->GetComponentByClass<UHealthComponent>() : nullptr; 
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(IsPlayerAliveKey.SelectedKeyName, Health != nullptr && !Health->IsDead());
}
