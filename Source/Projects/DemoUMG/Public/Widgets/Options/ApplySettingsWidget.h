// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IApplyableSettingWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ApplySettingsWidget.generated.h"

UCLASS()
class DEMOUMG_API UApplySettingsWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	TArray<TScriptInterface<IAppliableSettingWidget>> AppliableSettingWidgets;

	UPROPERTY(meta=(BindWidget))
	UButton *ApplyButton;

	UFUNCTION()
	void OnApplyButtonClicked();
	virtual void NativeConstruct() override;
};
