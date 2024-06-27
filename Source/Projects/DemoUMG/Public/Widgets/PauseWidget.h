// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PauseWidget.generated.h"

UCLASS()
class DEMOUMG_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	UButton *ResumeButton;

	UPROPERTY(meta=(BindWidget))
	UButton *OptionsButton;

	UPROPERTY(meta=(BindWidget))
	UButton *ToMenuButton;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MenuWorld;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OptionsWidgetClass;

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnOptionsButtonClicked();

	UFUNCTION()
	void OnToMenuButtonClicked();

	virtual void NativeConstruct() override;
};
