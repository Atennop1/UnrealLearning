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
	UInputAction *PlaceBlockAction;
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction *DestroyBlockStartAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction *DestroyBlockStopAction;

	
	UPROPERTY(EditDefaultsOnly)
	class UCharacterBlockPlacerComponent *CharacterBlockPlacer;

	UPROPERTY(EditDefaultsOnly)
	class UCharacterBlockDestroyerComponent *CharacterBlockDestroyer;

	AMinecraftCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
