// Copyright Atennop. All Rights Reserved.

#include "Breaker/Movement/CharacterJumpingComponent.h"
#include "Breaker/BreakerCharacter.h"

UCharacterJumpingComponent::UCharacterJumpingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterJumpingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABreakerCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterJumpingComponent::StartJumping() const
{
	if (!Character->GetCrouchingComponent()->GetIsCrouching())
		Character->Jump();
}

void UCharacterJumpingComponent::StopJumping() const
{
	if (!Character->GetCrouchingComponent()->GetIsCrouching())
		Character->StopJumping();
}
