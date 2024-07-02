// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Breaker/BreakerCharacter.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "BreakerPlayerController.generated.h"

UCLASS()
class GUARDAI_API ABreakerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn *PossessingPawn) override;
	
private:
	UPROPERTY()
	ABreakerCharacter *PossessedCharacter;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext *InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *MoveAction;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *JumpAction;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *StartCrouchAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *StopCrouchAction;

	void CallMove(const FInputActionValue &Value);
	void CallRotate(const FInputActionValue &Value);
	void CallStartJumping(const FInputActionValue &Value);
	void CallStopJumping(const FInputActionValue &Value);
	void CallStartCrouch(const FInputActionValue &Value);
	void CallStopCrouch(const FInputActionValue &Value);
};
