// Copyright Atennop. All Rights Reserved.

#include "Enemy/GuardController.h"

AGuardController::AGuardController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGuardController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
}

