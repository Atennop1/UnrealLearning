// Copyright Atennop. All Rights Reserved.

#include "Character/NetworkPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ANetworkPlayerController::OnPossess(APawn* PossessingPawn)
{
	Super::OnPossess(PossessingPawn);
	PossessedCharacter = Cast<ANetworkCharacter>(PossessingPawn);

	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, "Possess");
	if (!IsValid(PossessedCharacter) || !IsLocalController() && GetNetMode() != NM_DedicatedServer)
		return;

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, "Attach");
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANetworkPlayerController::CallMove);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANetworkPlayerController::CallRotate);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ANetworkPlayerController::CallStartJumping);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ANetworkPlayerController::CallStopJumping);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ANetworkPlayerController::CallStartCrouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ANetworkPlayerController::CallStopCrouch);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallMove(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, "CallMove");
	if (IsValid(PossessedCharacter)) PossessedCharacter->GetMovingComponent()->Move(Value.Get<FVector2D>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallRotate(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetRotatingComponent()->Rotate(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStartJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StartJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStopJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StopJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStartCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StartCrouching(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStopCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StopCrouching(); }
