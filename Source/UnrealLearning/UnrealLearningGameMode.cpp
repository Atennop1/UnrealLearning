// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealLearningGameMode.h"
#include "UnrealLearningCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealLearningGameMode::AUnrealLearningGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
