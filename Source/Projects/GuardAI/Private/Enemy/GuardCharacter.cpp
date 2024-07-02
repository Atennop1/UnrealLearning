// Copyright Atennop. All Rights Reserved.

#include "Enemy/GuardCharacter.h"

AGuardCharacter::AGuardCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGuardCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(PatrollingComponent))
}
