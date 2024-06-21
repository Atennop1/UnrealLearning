// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSaveLoadComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "FirstPersonCharacter.h"
#include "SavingCharacter.generated.h"

UCLASS()
class SAVINGTEST_API ASavingCharacter : public AFirstPersonCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UCharacterSaveLoadComponent *SaveLoadComponent;
	
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext *InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *SaveInputAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *LoadInputAction;
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	ASavingCharacter();
};
