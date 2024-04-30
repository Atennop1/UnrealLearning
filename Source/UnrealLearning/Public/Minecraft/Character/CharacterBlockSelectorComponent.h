﻿// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBlockPlacerComponent.h"
#include "Components/ActorComponent.h"
#include "CharacterBlockSelectorComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UCharacterBlockSelectorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<int, TSubclassOf<AActor>> BlocksByIndex;

	UPROPERTY()
	UCharacterBlockPlacerComponent *BlockPlacer;

	virtual void BeginPlay() override;

public:
	UCharacterBlockSelectorComponent();
	void Select(const FInputActionValue &Value);
};