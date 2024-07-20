// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "ChangeVolumeWidget.generated.h"

UCLASS()
class DEMOUMG_API UChangeVolumeWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	FString SlotName = "Volume";
	
	UPROPERTY(EditAnywhere)
	USoundMix *SoundMixModifier;

	UPROPERTY(EditAnywhere)
	USoundClass *SoundClass;
	
	UPROPERTY(meta=(BindWidget))
	USlider *VolumeSlider;
	
	UFUNCTION()
	void OnVolumeChanged(float Volume);
	virtual void NativeConstruct() override;
};
