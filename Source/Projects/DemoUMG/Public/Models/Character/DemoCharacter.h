// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterGamePausingComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "FirstPersonCharacter.h"
#include "DemoCharacter.generated.h"

UCLASS()
class DEMOUMG_API ADemoCharacter : public AFirstPersonCharacter
{
	GENERATED_BODY()

public:
	ADemoCharacter();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext *InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *PauseInputAction;

	UPROPERTY(EditDefaultsOnly)
	UCharacterGamePausingComponent *GamePausingComponent;
};
