// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/CharacterMovingComponent.h"

#include "Character/GuardCharacter.h"

UCharacterMovingComponent::UCharacterMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGuardCharacter>(GetOwner());
	check (Character != nullptr)
}

void UCharacterMovingComponent::Move(const FVector2D Input) const
{
	Character->AddMovementInput(Character->GetActorRightVector(), Input.X);
	Character->AddMovementInput(Character->GetActorForwardVector(), Input.Y);
}
