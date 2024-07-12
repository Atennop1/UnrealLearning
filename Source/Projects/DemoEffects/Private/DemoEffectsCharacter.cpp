// Copyright Atennop. All Rights Reserved.

#include "DemoEffectsCharacter.h"

ADemoEffectsCharacter::ADemoEffectsCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADemoEffectsCharacter::Move(const FInputActionValue& Value)
{
	if (bCanMove)
		Super::Move(Value);
}

void ADemoEffectsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}