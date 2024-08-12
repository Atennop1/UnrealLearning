// Copyright Atennop. All Rights Reserved.

#include "Character/NetworkPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ANetworkPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent();
}

void ANetworkPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	PossessedCharacter = Cast<ANetworkCharacter>(GetPawn());

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANetworkPlayerController::CallMove);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANetworkPlayerController::CallRotate);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ANetworkPlayerController::CallShoot);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ANetworkPlayerController::CallStartJumping);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ANetworkPlayerController::CallStopJumping);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ANetworkPlayerController::CallStartCrouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ANetworkPlayerController::CallStopCrouch);
	EnhancedInputComponent->BindAction(PeekLeftAction, ETriggerEvent::Started, this, &ANetworkPlayerController::CallStartPeekingLeft);
	EnhancedInputComponent->BindAction(PeekLeftAction, ETriggerEvent::Completed, this, &ANetworkPlayerController::CallStopPeekingLeft);
	EnhancedInputComponent->BindAction(PeekRightAction, ETriggerEvent::Started, this, &ANetworkPlayerController::CallStartPeekingRight);
	EnhancedInputComponent->BindAction(PeekRightAction, ETriggerEvent::Completed, this, &ANetworkPlayerController::CallStopPeekingRight);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallMove(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetMovingComponent()->Move(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallRotate(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetRotatingComponent()->Rotate(Value.Get<FVector2D>()); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallShoot(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetShootingComponent()->Shoot(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStartJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StartJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStopJumping(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetJumpingComponent()->StopJumping(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStartCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StartCrouching(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStopCrouch(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetCrouchingComponent()->StopCrouching(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStartPeekingLeft(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetPeekingComponent()->StartPeekingLeft(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStopPeekingLeft(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetPeekingComponent()->StopPeekingLeft(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStartPeekingRight(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetPeekingComponent()->StartPeekingRight(); }

// ReSharper disable once CppMemberFunctionMayBeConst
void ANetworkPlayerController::CallStopPeekingRight(const FInputActionValue& Value) { if (IsValid(PossessedCharacter)) PossessedCharacter->GetPeekingComponent()->StopPeekingRight(); }
