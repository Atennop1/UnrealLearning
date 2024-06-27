// Copyright Atennop. All Rights Reserved.

#include "Widgets/Options/ChangeResolutionScaleWidget.h"
#include "GameFramework/GameUserSettings.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void UChangeResolutionScaleWidget::OnResolutionScaleSliderValueChanged(float Value)
{
	UGameUserSettings::GetGameUserSettings()->SetResolutionScaleNormalized(Value);
}

void UChangeResolutionScaleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ResolutionScaleSlider->OnValueChanged.AddDynamic(this, &UChangeResolutionScaleWidget::OnResolutionScaleSliderValueChanged);
	ResolutionScaleSlider->SetValue(UGameUserSettings::GetGameUserSettings()->GetResolutionScaleNormalized());
}
