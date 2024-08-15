// Copyright Atennop. All Rights Reserved.

#include "UI/NetworkHUD.h"
#include "Character/NetworkCharacter.h"

void ANetworkHUD::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ANetworkCharacter>(GetOwningPawn());
	ResourcesWidget = CreateWidget<UNetworkResourcesWidget>(GetWorld(), ResourcesWidgetClass);
	ResourcesWidget->AddToViewport();

	Character->GetHealthComponent()->OnHealthUpdated.AddDynamic(ResourcesWidget, &UNetworkResourcesWidget::UpdateHealthText);
	Character->GetAmmoComponent()->OnAmmoUpdated.AddDynamic(ResourcesWidget, &UNetworkResourcesWidget::UpdateAmmoText);
}

void ANetworkHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Character->GetHealthComponent()->OnHealthUpdated.RemoveDynamic(ResourcesWidget, &UNetworkResourcesWidget::UpdateHealthText);
	Character->GetAmmoComponent()->OnAmmoUpdated.RemoveDynamic(ResourcesWidget, &UNetworkResourcesWidget::UpdateAmmoText);

	if (IsValid(ResourcesWidget))
		ResourcesWidget->RemoveFromParent();
}
