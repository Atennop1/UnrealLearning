// Copyright Atennop. All Rights Reserved.

#include "Widgets/Options/ChangeWindowModeWidget.h"
#include "GameFramework/GameUserSettings.h"

void UChangeWindowModeWidget::Apply()
{
	UGameUserSettings::GetGameUserSettings()->SetFullscreenMode(CurrentWindowMode);
}

void UChangeWindowModeWidget::UpdateText() const
{
	switch (CurrentWindowMode)
	{
	case EWindowMode::Fullscreen:
		CurrentWindowModeText->SetText(FText::FromString("Fullscreen"));
		break;

	case EWindowMode::Windowed:
		CurrentWindowModeText->SetText(FText::FromString("Windowed"));
		break;
		
	case EWindowMode::WindowedFullscreen:
		CurrentWindowModeText->SetText(FText::FromString("Fullscreen Windowed"));
		break;
		
	default:;
	}
}

void UChangeWindowModeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	IncreaseButton->OnClicked.AddDynamic(this, &UChangeWindowModeWidget::OnIncreaseButtonClicked);
	DecreaseButton->OnClicked.AddDynamic(this, &UChangeWindowModeWidget::OnDecreaseButtonClicked);

	CurrentWindowMode = UGameUserSettings::GetGameUserSettings()->GetFullscreenMode();
	UpdateText();
}

void UChangeWindowModeWidget::OnDecreaseButtonClicked()
{
	if ((int)CurrentWindowMode == 0)
		return;

	CurrentWindowMode = static_cast<EWindowMode::Type>(static_cast<TEnumAsByte<EWindowMode::Type>>((int)CurrentWindowMode - 1));
	UpdateText();
}

void UChangeWindowModeWidget::OnIncreaseButtonClicked()
{
	if ((int)CurrentWindowMode == 2)
		return;

	CurrentWindowMode = static_cast<EWindowMode::Type>(static_cast<TEnumAsByte<EWindowMode::Type>>((int)CurrentWindowMode + 1));
	UpdateText();
}
