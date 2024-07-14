// Copyright Atennop. All Rights Reserved.

#include "Models/Character/CharacterGamePausingComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

UCharacterGamePausingComponent::UCharacterGamePausingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterGamePausingComponent::Pause()
{
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		TArray<UUserWidget*> PauseWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), PauseWidgets, PauseWidgetClass);
	
		if (PauseWidgets.Num() != 0)
		{
			if (!PauseWidgets[0]->IsVisible())
				return;
			
			PauseWidgets[0]->SetVisibility(ESlateVisibility::Hidden);
		}
		
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
		return;
	}

	PlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	TArray<UUserWidget*> PauseWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), PauseWidgets, PauseWidgetClass);
	
	if (PauseWidgets.Num() != 0)
	{
		PauseWidgets[0]->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	
	UUserWidget *PauseWidget = CreateWidget(PlayerController, PauseWidgetClass);
	PauseWidget->AddToViewport();
}

