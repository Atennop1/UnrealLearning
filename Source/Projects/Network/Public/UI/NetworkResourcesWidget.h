// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NetworkResourcesWidget.generated.h"

UCLASS()
class NETWORK_API UNetworkResourcesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateHealthText(int NewHealth);

	UFUNCTION()
	void UpdateAmmoText(int NewAmmo);
	
private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock *HealthText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *AmmoText;
};
