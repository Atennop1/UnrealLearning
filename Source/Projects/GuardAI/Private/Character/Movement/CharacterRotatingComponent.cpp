// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/CharacterRotatingComponent.h"

#include "Character/GuardCharacter.h"

UCharacterRotatingComponent::UCharacterRotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterRotatingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGuardCharacter>(GetOwner());
	check(Character != nullptr)
}

void UCharacterRotatingComponent::Rotate(const FVector2D Input) const
{
	Character->AddControllerYawInput(Input.X);
	Character->AddControllerPitchInput(Input.Y);
}
