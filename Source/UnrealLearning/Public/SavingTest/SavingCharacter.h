// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSaveLoadComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "FirstPerson/UnrealLearningCharacter.h"
#include "SavingCharacter.generated.h"

UCLASS()
class UNREALLEARNING_API ASavingCharacter : public AUnrealLearningCharacter
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
