// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CharacterPositionSave.generated.h"

UCLASS()
class SAVINGTEST_API UCharacterPositionSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector CharacterPosition;
};
