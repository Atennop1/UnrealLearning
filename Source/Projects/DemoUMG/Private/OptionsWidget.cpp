// Copyright Atennop. All Rights Reserved.

#include "OptionsWidget.h"

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnBackButtonPressed);
}

void UOptionsWidget::OnBackButtonPressed()
{
	UUserWidget *MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass);
	MenuWidget->AddToPlayerScreen();
	RemoveFromParent();
}
