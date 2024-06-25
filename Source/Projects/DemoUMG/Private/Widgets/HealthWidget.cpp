// Copyright Atennop. All Rights Reserved.

#include "Widgets/HealthWidget.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void UHealthWidget::OnHealthChanged(int NewHealth, int MaxHealth)
{
	if (IsValid(HealthProgressBar))
		HealthProgressBar->SetPercent((float)NewHealth / (float)MaxHealth);
}
