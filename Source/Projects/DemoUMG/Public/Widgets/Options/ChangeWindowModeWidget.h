// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IApplyableSettingWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ChangeWindowModeWidget.generated.h"

UCLASS()
class DEMOUMG_API UChangeWindowModeWidget : public UUserWidget, public IAppliableSettingWidget
{
	GENERATED_BODY()

public:
	virtual void Apply() override;

private:
	UPROPERTY(meta=(BindWidget))
	UButton *DecreaseButton;

	UPROPERTY(meta=(BindWidget))
	UButton *IncreaseButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *CurrentWindowModeText;
	EWindowMode::Type CurrentWindowMode;

	void UpdateText() const;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnDecreaseButtonClicked();
	
	UFUNCTION()
	void OnIncreaseButtonClicked();
};
