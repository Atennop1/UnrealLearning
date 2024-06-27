// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "ChangeResolutionScaleWidget.generated.h"

UCLASS()
class DEMOUMG_API UChangeResolutionScaleWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	USlider *ResolutionScaleSlider;

	UFUNCTION()
	void OnResolutionScaleSliderValueChanged(float Value);
	virtual void NativeConstruct() override;
};
