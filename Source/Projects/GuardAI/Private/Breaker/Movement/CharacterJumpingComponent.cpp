// Copyright Atennop. All Rights Reserved.

#include "Breaker/Movement/CharacterJumpingComponent.h"
#include "Breaker/BreakerCharacter.h"
#include "Perception/AISense_Hearing.h"

UCharacterJumpingComponent::UCharacterJumpingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterJumpingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABreakerCharacter>(GetOwner());
	check(Character != nullptr);
	Character->LandedDelegate.AddDynamic(this, &UCharacterJumpingComponent::OnLanded);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterJumpingComponent::OnLanded(const FHitResult& Hit)
{
	if (IsMakingNoise)
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), Character->GetActorLocation(), 1, Character, 0);
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
