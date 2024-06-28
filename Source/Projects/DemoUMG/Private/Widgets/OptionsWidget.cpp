// Copyright Atennop. All Rights Reserved.

#include "Widgets/OptionsWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnBackButtonPressed);
	GameTabButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnGameTabButton);
	GraphicsTabButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnGraphicsTabButton);
}

void UOptionsWidget::OnBackButtonPressed()
{
	TArray<UUserWidget*> MenuWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), MenuWidgets, MenuWidgetClass);
	SetVisibility(ESlateVisibility::Hidden);
	
	if (MenuWidgets.Num() != 0)
	{
		MenuWidgets[0]->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	
	UUserWidget *MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass);
	MenuWidget->AddToViewport();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionsWidget::OnGameTabButton()
{
	TabsWidgetSwitcher->SetActiveWidgetIndex(0);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionsWidget::OnGraphicsTabButton()
{
	TabsWidgetSwitcher->SetActiveWidgetIndex(1);
}
