// Copyright Atennop. All Rights Reserved.

#include "Widgets/OptionsWidget.h"

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnBackButtonPressed);
	GameTabButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnGameTabButton);
	GraphicsTabButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnGraphicsTabButton);
}

void UOptionsWidget::OnBackButtonPressed()
{
	UUserWidget *MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass);
	MenuWidget->AddToPlayerScreen();
	RemoveFromParent();
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
