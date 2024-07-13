// Copyright Atennop. All Rights Reserved.

#include "DemoEffectsPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CharacterAuraCastingComponent.h"
#include "Components/CharacterBlastingComponent.h"

void ADemoEffectsPlayerController::OnPossess(APawn *PossessingPawn)
{
	Super::OnPossess(PossessingPawn);
	PossessedCharacter = Cast<ADemoEffectsCharacter>(PossessingPawn);

	if (!PossessedCharacter)
		return;

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(CastAuraAction, ETriggerEvent::Triggered, this, &ADemoEffectsPlayerController::CallCastAura);
	EnhancedInputComponent->BindAction(BlastAction, ETriggerEvent::Triggered, this, &ADemoEffectsPlayerController::CallBlast);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ADemoEffectsPlayerController::CallCastAura(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetAuraCastingComponent()->CastAura(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ADemoEffectsPlayerController::CallBlast(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetBlastingComponent()->Blast(); }
