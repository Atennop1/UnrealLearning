// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthWidget.generated.h"

UCLASS()
class DEMOUMG_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnHealthChanged(int NewHealth, int MaxHealth);
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;
};
