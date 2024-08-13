// Copyright Atennop. All Rights Reserved.

#include "Character/NetworkCharacter.h"

ANetworkCharacter::ANetworkCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANetworkCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent != nullptr)
	check(MovingComponent != nullptr)
	check(RotatingComponent != nullptr)
	check(CrouchingComponent != nullptr)
	check(JumpingComponent != nullptr)
	check(PeekingComponent != nullptr)
	check(ShootingComponent != nullptr)
}
