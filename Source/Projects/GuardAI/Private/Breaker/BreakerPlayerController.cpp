// Copyright Atennop. All Rights Reserved.

#include "Breaker/BreakerPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void ABreakerPlayerController::OnPossess(APawn *PossessingPawn)
{
	Super::OnPossess(PossessingPawn);
	PossessedCharacter = Cast<ABreakerCharacter>(PossessingPawn);

	if (!PossessedCharacter)
		return;

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABreakerPlayerController::CallMove);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABreakerPlayerController::CallRotate);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABreakerPlayerController::CallStartJumping);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABreakerPlayerController::CallStopJumping);
	EnhancedInputComponent->BindAction(StartCrouchAction, ETriggerEvent::Triggered, this, &ABreakerPlayerController::CallStartCrouch);
	EnhancedInputComponent->BindAction(StopCrouchAction, ETriggerEvent::Completed, this, &ABreakerPlayerController::CallStopCrouch);
	EnhancedInputComponent->BindAction(DistractAction, ETriggerEvent::Triggered, this, &ABreakerPlayerController::CallDistract);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, PossessedCharacter->GetPausingComponent(), &UCharacterGamePausingComponent::Pause);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ABreakerPlayerController::CallMove(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetMovingComponent()->Move(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ABreakerPlayerController::CallRotate(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetRotatingComponent()->Rotate(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ABreakerPlayerController::CallStartJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StartJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ABreakerPlayerController::CallStopJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StopJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ABreakerPlayerController::CallStartCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StartCrouching(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ABreakerPlayerController::CallStopCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StopCrouching(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ABreakerPlayerController::CallDistract(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetDistractingComponent()->Distract(); }
