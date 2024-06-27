// Copyright Atennop. All Rights Reserved.

#include "Models/DemoHUD.h"
#include "Models/HealthComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void ADemoHUD::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PlayerController) || !IsValid(HealthWidgetClass))
		return;

	HealthWidget = Cast<UHealthWidget>(CreateWidget(PlayerController, HealthWidgetClass));
	HealthWidget->AddToViewport();

	const ACharacter *Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!IsValid(Character))
		return;

	UHealthComponent *HealthComponent = Character->GetComponentByClass<UHealthComponent>();
	HealthComponent->OnHealthChanged.BindDynamic(HealthWidget, &UHealthWidget::OnHealthChanged);
}

void ADemoHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (IsValid(HealthWidget))
		HealthWidget->RemoveFromParent();
}
