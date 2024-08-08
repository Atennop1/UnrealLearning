// Copyright Atennop. All Rights Reserved.

#include "Character/NetworkCharacter.h"

ANetworkCharacter::ANetworkCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANetworkCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(MovingComponent != nullptr)
	check(RotatingComponent != nullptr)
	check(CrouchingComponent != nullptr)
	check(JumpingComponent != nullptr)
}