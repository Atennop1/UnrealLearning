// Copyright Atennop. All Rights Reserved.

#include "Widgets/PauseWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::OnResumeButtonClicked()
{
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	PlayerController->SetShowMouseCursor(false);
	RemoveFromParent();
}

void UPauseWidget::OnOptionsButtonClicked()
{
	TArray<UUserWidget*> OptionsWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), OptionsWidgets, OptionsWidgetClass);
	SetVisibility(ESlateVisibility::Hidden);
	
	if (OptionsWidgets.Num() != 0)
	{
		OptionsWidgets[0]->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	
	UUserWidget *OptionsWidget = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), OptionsWidgetClass);
	OptionsWidget->AddToViewport();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseWidget::OnToMenuButtonClicked()
{
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MenuWorld);
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeButtonClicked);
	OptionsButton->OnClicked.AddDynamic(this, &UPauseWidget::OnOptionsButtonClicked);
	ToMenuButton->OnClicked.AddDynamic(this, &UPauseWidget::OnToMenuButtonClicked);
}
