// Copyright Atennop. All Rights Reserved.

#include "Widgets/Options/ChangeVolumeWidget.h"
#include "Kismet/GameplayStatics.h"

void UChangeVolumeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	VolumeSlider->OnValueChanged.AddDynamic(this, &UChangeVolumeWidget::OnVolumeChanged);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UChangeVolumeWidget::OnVolumeChanged(float Volume)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixModifier, SoundClass, Volume, 1, 0, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMixModifier);
}
