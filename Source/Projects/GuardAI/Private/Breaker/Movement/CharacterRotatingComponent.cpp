// Copyright Atennop. All Rights Reserved.

#include "Breaker/Movement/CharacterRotatingComponent.h"
#include "Breaker/BreakerCharacter.h"

UCharacterRotatingComponent::UCharacterRotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterRotatingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABreakerCharacter>(GetOwner());
	check(Character != nullptr)
}

void UCharacterRotatingComponent::Rotate(const FVector2D Input) const
{
	Character->AddControllerYawInput(Input.X);
	Character->AddControllerPitchInput(Input.Y);
}
