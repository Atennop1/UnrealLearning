// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/NetworkCharacterJumpingComponent.h"
#include "Character/NetworkCharacter.h"

UNetworkCharacterJumpingComponent::UNetworkCharacterJumpingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNetworkCharacterJumpingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(Character != nullptr);
}

void UNetworkCharacterJumpingComponent::StartJumping() const
{
	if (!Character->GetHealthComponent()->IsAlive())
		return;
	
	if (!Character->GetCrouchingComponent()->GetIsCrouching())
		Character->Jump();
}

void UNetworkCharacterJumpingComponent::StopJumping() const
{
	if (!Character->GetHealthComponent()->IsAlive())
		return;
	
	if (!Character->GetCrouchingComponent()->GetIsCrouching())
		Character->StopJumping();
}
