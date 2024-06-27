// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "ChangeLanguageWidget.generated.h"

UCLASS()
class DEMOUMG_API UChangeLanguageWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UComboBoxString> LanguageComboBox;
	TMap<FString, FString> CulturesNames;
	bool bCanSelectLanguage = true;

	UFUNCTION()
	void OnLanguageSelected(FString SelectedItem, ESelectInfo::Type SelectionType);
	void CreateCulturesName();
	virtual void NativeConstruct() override;
};
