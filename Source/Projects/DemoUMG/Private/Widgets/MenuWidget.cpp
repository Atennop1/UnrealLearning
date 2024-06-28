// Copyright Atennop. All Rights Reserved.

#include "Widgets/MenuWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartButtonClicked);
	OptionsButton->OnClicked.AddDynamic(this, &UMenuWidget::OnOptionsButtonClicked);
	ExitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnExitButtonClicked);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UMenuWidget::OnStartButtonClicked()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), GameWorld);
}

void UMenuWidget::OnOptionsButtonClicked()
{
	TArray<UUserWidget*> OptionsWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), OptionsWidgets, OptionsWidgetClass);
	SetVisibility(ESlateVisibility::Hidden);
	
	if (OptionsWidgets.Num() != 0)
	{
		OptionsWidgets[0]->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	
	UUserWidget *OptionsWidget = CreateWidget(GetWorld(), OptionsWidgetClass);
	OptionsWidget->AddToViewport();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UMenuWidget::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
