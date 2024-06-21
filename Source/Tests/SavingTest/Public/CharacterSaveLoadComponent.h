// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSaveLoadComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SAVINGTEST_API UCharacterSaveLoadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterSaveLoadComponent();
	void Save(const struct FInputActionValue &Binding);
	void Load(const FInputActionValue &Binding);
};
