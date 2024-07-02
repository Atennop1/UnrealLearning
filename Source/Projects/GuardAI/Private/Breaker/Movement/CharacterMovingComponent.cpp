// Copyright Atennop. All Rights Reserved.

#include "Breaker/Movement/CharacterMovingComponent.h"
#include "Breaker/BreakerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UCharacterMovingComponent::UCharacterMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABreakerCharacter>(GetOwner());
	check (Character != nullptr)
}

void UCharacterMovingComponent::Move(const FVector2D Input) const
{
	Character->AddMovementInput(UKismetMathLibrary::GetRightVector(Character->GetControlRotation()), Input.X);
	Character->AddMovementInput(UKismetMathLibrary::GetForwardVector(Character->GetControlRotation()), Input.Y);
}
