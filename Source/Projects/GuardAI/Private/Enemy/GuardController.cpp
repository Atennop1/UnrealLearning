// Copyright Atennop. All Rights Reserved.

#include "Enemy/GuardController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AGuardController::AGuardController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGuardController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
}

void AGuardController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	Super::UpdateControlRotation(DeltaTime, false);

	if (!bUpdatePawn)
		return;
	
	APawn* const MyPawn = GetPawn();
	const FRotator CurrentPawnRotation = MyPawn->GetActorRotation();
	SmoothTargetRotation = UKismetMathLibrary::RInterpTo_Constant(MyPawn->GetActorRotation(), ControlRotation, DeltaTime, SmoothRotationSpeed);
	
	if (CurrentPawnRotation.Equals(SmoothTargetRotation, 1e-3f) == false)
		MyPawn->FaceRotation(SmoothTargetRotation, DeltaTime);
}

