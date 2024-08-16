// Copyright Atennop. All Rights Reserved.

#include "UI/NetworkHUD.h"
#include "Character/NetworkCharacter.h"

void ANetworkHUD::SpawnUI()
{
	Character = Cast<ANetworkCharacter>(GetOwningPawn());
	ResourcesWidget = CreateWidget<UNetworkResourcesWidget>(PlayerOwner, ResourcesWidgetClass);
	ResourcesWidget->AddToViewport();

	Character->GetHealthComponent()->OnHealthUpdated.AddDynamic(ResourcesWidget, &UNetworkResourcesWidget::UpdateHealthText);
	Character->GetAmmoComponent()->OnAmmoUpdated.AddDynamic(ResourcesWidget, &UNetworkResourcesWidget::UpdateAmmoText);
}

void ANetworkHUD::DestroyUI()
{
	if (IsValid(Character))
	{
		Character->GetHealthComponent()->OnHealthUpdated.RemoveDynamic(ResourcesWidget, &UNetworkResourcesWidget::UpdateHealthText);
		Character->GetAmmoComponent()->OnAmmoUpdated.RemoveDynamic(ResourcesWidget, &UNetworkResourcesWidget::UpdateAmmoText);
		Character = nullptr;
	}

	if (IsValid(ResourcesWidget))
	{
		ResourcesWidget->RemoveFromParent();
		ResourcesWidget = nullptr;
	}
}
