// Copyright Atennop. All Rights Reserved.

#include "Enemy/GuardController.h"

AGuardController::AGuardController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGuardController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
}

