// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/CharacterJumpingComponent.h"

#include "Character/GuardCharacter.h"

UCharacterJumpingComponent::UCharacterJumpingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterJumpingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGuardCharacter>(GetOwner());
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
