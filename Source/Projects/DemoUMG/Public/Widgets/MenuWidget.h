// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MenuWidget.generated.h"

UCLASS()
class DEMOUMG_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	UButton *StartButton;

	UPROPERTY(meta=(BindWidget))
	UButton *OptionsButton;

	UPROPERTY(meta=(BindWidget))
	UButton *ExitButton;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> GameWorld;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OptionsWidgetClass;

	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnOptionsButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

	virtual void NativeConstruct() override;
};
