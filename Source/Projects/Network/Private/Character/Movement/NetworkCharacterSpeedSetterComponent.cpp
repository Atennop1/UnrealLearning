// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/NetworkCharacterSpeedSetterComponent.h"
#include "Character/NetworkCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UNetworkCharacterSpeedSetterComponent::UNetworkCharacterSpeedSetterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNetworkCharacterSpeedSetterComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(Character != nullptr);
}

void UNetworkCharacterSpeedSetterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Character->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (Character->GetCrouchingComponent()->GetIsCrouching() && Character->GetCharacterMovement()->MaxWalkSpeed > CrouchSpeed)
		Character->GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}
