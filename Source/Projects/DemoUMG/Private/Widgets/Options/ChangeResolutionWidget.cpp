// Copyright Atennop. All Rights Reserved.

#include "Widgets/Options/ChangeResolutionWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UChangeResolutionWidget::Apply()
{
	UGameUserSettings::GetGameUserSettings()->SetScreenResolution(SupportedResolutions[CurrentResolutionIndex]);
}

void UChangeResolutionWidget::UpdateText()
{
	const FIntPoint CurrentResolution = SupportedResolutions[CurrentResolutionIndex];
	CurrentResolutionText->SetText(FText::FromString(UKismetStringLibrary::Conv_IntToString(CurrentResolution.X) + "x" + UKismetStringLibrary::Conv_IntToString(CurrentResolution.Y)));
}

void UChangeResolutionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	IncreaseButton->OnClicked.AddDynamic(this, &UChangeResolutionWidget::OnIncreaseButtonClicked);
	DecreaseButton->OnClicked.AddDynamic(this, &UChangeResolutionWidget::OnDecreaseButtonClicked);

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedResolutions);
	CurrentResolutionIndex = SupportedResolutions.Find(UGameUserSettings::GetGameUserSettings()->GetScreenResolution());
	UpdateText();
}

void UChangeResolutionWidget::OnDecreaseButtonClicked()
{
	if (CurrentResolutionIndex <= 0)
		return;

	CurrentResolutionIndex--;
	UpdateText();
}

void UChangeResolutionWidget::OnIncreaseButtonClicked()
{
	if (CurrentResolutionIndex + 1 >= SupportedResolutions.Num())
		return;

	CurrentResolutionIndex++;
	UpdateText();
}

