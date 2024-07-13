// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DemoEffectsCharacter.h"
#include "GameFramework/PlayerController.h"
#include "DemoEffectsPlayerController.generated.h"

UCLASS()
class DEMOEFFECTS_API ADemoEffectsPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn *PossessingPawn) override;
	
private:
	UPROPERTY()
	ADemoEffectsCharacter *PossessedCharacter;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext *InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *CastAuraAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *BlastAction;

	void CallCastAura(const FInputActionValue &Value);
	void CallBlast(const FInputActionValue &Value);
};
