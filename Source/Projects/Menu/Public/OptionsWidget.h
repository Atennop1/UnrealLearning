// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "OptionsWidget.generated.h"

UCLASS()
class MENU_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	UButton *BackButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UFUNCTION()
	void OnBackButtonPressed();
	
	virtual void NativeConstruct() override;
};
