// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FirstPerson/UnrealLearningCharacter.h"
#include "MinecraftCharacter.generated.h"

UCLASS()
class UNREALLEARNING_API AMinecraftCharacter : public AUnrealLearningCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext *InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *PlaceBlockInputAction;
	
	UPROPERTY(EditDefaultsOnly)
	class UCharacterBlockPlacerComponent *CharacterBlockPlacer;

	AMinecraftCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
