// Copyright Atennop. All Rights Reserved.

#include "Widgets/Options/ChangeVolumeWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Options/VolumeSaveGame.h"

void UChangeVolumeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	VolumeSlider->OnValueChanged.AddDynamic(this, &UChangeVolumeWidget::OnVolumeChanged);

	if (!UGameplayStatics::DoesSaveGameExist("Volume", 0))
		return;
	
	const auto Save = Cast<UVolumeSaveGame>(UGameplayStatics::LoadGameFromSlot("Volume", 0));
	VolumeSlider->SetValue(Save->Volume);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UChangeVolumeWidget::OnVolumeChanged(float Volume)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixModifier, SoundClass, Volume, 1, 0, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMixModifier);

	const auto Save = Cast<UVolumeSaveGame>(UGameplayStatics::CreateSaveGameObject(UVolumeSaveGame::StaticClass()));
	Save->Volume = Volume;
	UGameplayStatics::SaveGameToSlot(Save, "Volume", 0);
}
