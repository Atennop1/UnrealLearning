// Copyright Atennop. All Rights Reserved.

#include "Enemy/GuardPerception.h"

UGuardPerception::UGuardPerception()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGuardPerception::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<AGuardController>(GetOwner());
	
	check(IsValid(Controller));
	OnTargetPerceptionUpdated.AddDynamic(this, &UGuardPerception::OnPerceptionUpdated);
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UGuardPerception::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor->IsA(AGuardController::StaticClass()))
		return;

	
}

