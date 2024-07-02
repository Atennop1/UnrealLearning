// Copyright Atennop. All Rights Reserved.

#include "Breaker/BreakerCharacter.h"

ABreakerCharacter::ABreakerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABreakerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(MovingComponent != nullptr)
	check(RotatingComponent != nullptr)
	check(CrouchingComponent != nullptr)
	check(JumpingComponent != nullptr)
}
