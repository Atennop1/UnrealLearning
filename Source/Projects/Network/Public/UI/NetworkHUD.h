// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkResourcesWidget.h"
#include "Character/NetworkCharacter.h"
#include "GameFramework/HUD.h"
#include "NetworkHUD.generated.h"

UCLASS()
class NETWORK_API ANetworkHUD : public AHUD
{
	GENERATED_BODY()

public:
	void SpawnUI();
	void DestroyUI();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { DestroyUI(); }

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNetworkResourcesWidget> ResourcesWidgetClass;

	UPROPERTY()
	ANetworkCharacter *Character;

	UPROPERTY()
	UNetworkResourcesWidget *ResourcesWidget;
};
