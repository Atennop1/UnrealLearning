// Copyright Atennop. All Rights Reserved.

#include "UI/NetworkResourcesWidget.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void UNetworkResourcesWidget::UpdateHealthText(int NewHealth)
{
	HealthText->SetText(FText::FromString(FString::FromInt(NewHealth)));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UNetworkResourcesWidget::UpdateAmmoText(int NewAmmo)
{
	AmmoText->SetText(FText::FromString(FString::FromInt(NewAmmo)));
}
