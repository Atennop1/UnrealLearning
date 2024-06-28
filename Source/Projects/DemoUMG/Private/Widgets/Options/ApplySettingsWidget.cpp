// Copyright Atennop. All Rights Reserved.

#include "Widgets/Options/ApplySettingsWidget.h"
#include "GameFramework/GameUserSettings.h"

void UApplySettingsWidget::OnApplyButtonClicked()
{
	for (const auto Widget : AppliableSettingWidgets)
		Cast<IAppliableSettingWidget>(Widget.GetObject())->Apply();

	UGameUserSettings::GetGameUserSettings()->ApplySettings(true);
}

void UApplySettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ApplyButton->OnClicked.AddDynamic(this, &UApplySettingsWidget::OnApplyButtonClicked);
}
