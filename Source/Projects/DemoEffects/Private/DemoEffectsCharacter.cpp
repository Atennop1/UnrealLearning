// Copyright Atennop. All Rights Reserved.

#include "DemoEffectsCharacter.h"
#include "Components/CharacterAuraCastingComponent.h"
#include "Components/CharacterBlastingComponent.h"

ADemoEffectsCharacter::ADemoEffectsCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADemoEffectsCharacter::Jump()
{
	if (bCanMove)
		Super::Jump();
}

void ADemoEffectsCharacter::Move(const FInputActionValue& Value)
{
	if (bCanMove)
		Super::Move(Value);
}

void ADemoEffectsCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(AuraCastingComponent))
	check(IsValid(BlastingComponent))
}