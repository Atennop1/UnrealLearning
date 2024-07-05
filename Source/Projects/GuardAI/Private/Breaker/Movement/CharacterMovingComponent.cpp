// Copyright Atennop. All Rights Reserved.

#include "Breaker/Movement/CharacterMovingComponent.h"
#include "Breaker/BreakerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AISense_Hearing.h"

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

	if (IsMakingNoise && !Character->GetCrouchingComponent()->GetIsCrouching() && !Character->GetCharacterMovement()->IsFalling())
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), Character->GetActorLocation(), 1, Character);
}
