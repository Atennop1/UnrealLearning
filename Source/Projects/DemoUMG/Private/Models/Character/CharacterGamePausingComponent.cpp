// Copyright Atennop. All Rights Reserved.

#include "Models/Character/CharacterGamePausingComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

UCharacterGamePausingComponent::UCharacterGamePausingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterGamePausingComponent::OnPauseActionTriggered(const FInputActionValue& Binding)
{
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		CreatedPauseWidget->RemoveFromParent();
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
		return;
	}

	CreatedPauseWidget = CreateWidget(PlayerController, PauseWidgetClass);
	CreatedPauseWidget->AddToViewport();
	PlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

