// Copyright Atennop. All Rights Reserved.

#include "Character/PostProcessingCharacter.h"
#include "Camera/CameraComponent.h"

APostProcessingCharacter::APostProcessingCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APostProcessingCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(WorldUnloadingComponent))
	check(IsValid(MatrixComponent))
	
	FPostProcessSettings PostProcessSettings = FPostProcessSettings();
	PostProcessSettings.WeightedBlendables = TArray { FWeightedBlendable(1, CurrentPostProcessMaterial) };
	GetFirstPersonCameraComponent()->PostProcessSettings = PostProcessSettings;
}
