// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/NetworkCharacterRotatingComponent.h"
#include "Character/NetworkCharacter.h"

UNetworkCharacterRotatingComponent::UNetworkCharacterRotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNetworkCharacterRotatingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(Character != nullptr)
}

void UNetworkCharacterRotatingComponent::Rotate(const FVector2D Input) const
{
	Character->AddControllerYawInput(Input.X);
	Character->AddControllerPitchInput(Input.Y);
}

