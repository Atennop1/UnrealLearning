// Copyright Atennop. All Rights Reserved.

#include "Character/PostProcessingPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APostProcessingPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedCharacter = Cast<APostProcessingCharacter>(InPawn);

	if (!PossessedCharacter)
		return;

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(ChangeWorldStateAction, ETriggerEvent::Triggered, this, &APostProcessingPlayerController::CallChangeWorldState);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APostProcessingPlayerController::CallChangeWorldState(const FInputActionValue& Value)
{
	if (IsValid(PossessedCharacter))
		PossessedCharacter->GetWorldUnloadingComponent()->ChangeWorldState();
}
