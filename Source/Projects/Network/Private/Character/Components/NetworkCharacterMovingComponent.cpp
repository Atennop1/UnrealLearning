// Copyright Atennop. All Rights Reserved.

#include "Character/Components/NetworkCharacterMovingComponent.h"
#include "Character/NetworkCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UNetworkCharacterMovingComponent::UNetworkCharacterMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNetworkCharacterMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check (Character != nullptr)
}

void UNetworkCharacterMovingComponent::Move(const FVector2D Input) const
{
	Character->AddMovementInput(UKismetMathLibrary::GetRightVector(Character->GetControlRotation()), Input.X);
	Character->AddMovementInput(UKismetMathLibrary::GetForwardVector(Character->GetControlRotation()), Input.Y);
}
