// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/CharacterSpeedSetterComponent.h"
#include "Character/GuardCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterSpeedSetterComponent::UCharacterSpeedSetterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterSpeedSetterComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGuardCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterSpeedSetterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Character->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (Character->GetCrouchingComponent()->GetIsCrouching() && Character->GetCharacterMovement()->MaxWalkSpeed > CrouchSpeed)
		Character->GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}
