// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "PostProcessingCharacter.h"
#include "GameFramework/PlayerController.h"
#include "PostProcessingPlayerController.generated.h"

UCLASS()
class POSTPROCESSING_API APostProcessingPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	APostProcessingCharacter *PossessedCharacter;
	
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext *InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *ChangeWorldStateAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *ChangeMatrixAction;

	void CallChangeWorldState(const FInputActionValue &Value);
	void CallChangeMatrix(const FInputActionValue &Value);
};
