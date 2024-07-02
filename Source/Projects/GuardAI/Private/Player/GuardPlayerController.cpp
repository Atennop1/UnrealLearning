// Copyright Atennop. All Rights Reserved.

#include "Player/GuardPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void AGuardPlayerController::OnPossess(APawn *PossessingPawn)
{
	Super::OnPossess(PossessingPawn);
	PossessedCharacter = Cast<AGuardCharacter>(PossessingPawn);

	if (!PossessedCharacter)
		return;

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGuardPlayerController::CallMove);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGuardPlayerController::CallRotate);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AGuardPlayerController::CallStartJumping);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGuardPlayerController::CallStopJumping);
	EnhancedInputComponent->BindAction(StartCrouchAction, ETriggerEvent::Triggered, this, &AGuardPlayerController::CallStartCrouch);
	EnhancedInputComponent->BindAction(StopCrouchAction, ETriggerEvent::Completed, this, &AGuardPlayerController::CallStopCrouch);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AGuardPlayerController::CallMove(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetMovingComponent()->Move(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AGuardPlayerController::CallRotate(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetRotatingComponent()->Rotate(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AGuardPlayerController::CallStartJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StartJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AGuardPlayerController::CallStopJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StopJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AGuardPlayerController::CallStartCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StartCrouching(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AGuardPlayerController::CallStopCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StopCrouching(); }
