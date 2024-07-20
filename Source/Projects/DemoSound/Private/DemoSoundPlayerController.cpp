// Copyright Atennop. All Rights Reserved.

#include "DemoSoundPlayerController.h"

void ADemoSoundPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetAudioListenerOverride(GetCharacter()->GetMesh(), FVector(0, 0, 90), FRotator::ZeroRotator);
}
