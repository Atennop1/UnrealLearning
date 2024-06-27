// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "OptionsWidget.generated.h"

UCLASS()
class DEMOUMG_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	UButton *BackButton;

	UPROPERTY(meta=(BindWidget))
	UButton *GameTabButton;

	UPROPERTY(meta=(BindWidget))
	UButton *GraphicsTabButton;

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher *TabsWidgetSwitcher;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnBackButtonPressed();

	UFUNCTION()
	void OnGameTabButton();
	
	UFUNCTION()
	void OnGraphicsTabButton();	
};
