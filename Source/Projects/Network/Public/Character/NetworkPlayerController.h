// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "NetworkCharacter.h"
#include "GameFramework/PlayerController.h"
#include "NetworkPlayerController.generated.h"

UCLASS()
class NETWORK_API ANetworkPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void OnRep_PlayerState() override;

private:
	UPROPERTY()
	ANetworkCharacter *PossessedCharacter;
	
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext *InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *MoveAction;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *JumpAction;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *CrouchAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *PeekLeftAction;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *PeekRightAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *ShootAction;

	void CallMove(const FInputActionValue &Value);
	void CallRotate(const FInputActionValue &Value);
	void CallShoot(const FInputActionValue &Value);
	void CallStartJumping(const FInputActionValue &Value);
	void CallStopJumping(const FInputActionValue &Value);
	void CallStartCrouch(const FInputActionValue &Value);
	void CallStopCrouch(const FInputActionValue &Value);

	void CallStartPeekingLeft(const FInputActionValue &Value);
	void CallStopPeekingLeft(const FInputActionValue &Value);
	void CallStartPeekingRight(const FInputActionValue &Value);
	void CallStopPeekingRight(const FInputActionValue &Value);
};
