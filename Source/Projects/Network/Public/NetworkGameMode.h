// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/NetworkCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "NetworkGameMode.generated.h"

UCLASS()
class NETWORK_API ANetworkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void Respawn(AController *Controller) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANetworkCharacter> CharacterClass;
};
