// Copyright Atennop. All Rights Reserved.

#include "Character/GuardCharacter.h"

AGuardCharacter::AGuardCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGuardCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(MovingComponent != nullptr)
	check(RotatingComponent != nullptr)
	check(CrouchingComponent != nullptr)
	check(JumpingComponent != nullptr)
}
