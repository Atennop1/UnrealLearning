// Copyright Atennop. All Rights Reserved.

#include "Widgets/Options/ChangeLanguageWidget.h"
#include "Kismet/KismetInternationalizationLibrary.h"

void UChangeLanguageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TArray<FString> Cultures = UKismetInternationalizationLibrary::GetLocalizedCultures(true, false, false, false);

	for (const auto Culture : Cultures)
	{
		CulturesNames.Add(UKismetInternationalizationLibrary::GetCultureDisplayName(Culture), Culture);
		LanguageComboBox->AddOption(UKismetInternationalizationLibrary::GetCultureDisplayName(Culture));
	}

	LanguageComboBox->SetSelectedOption(UKismetInternationalizationLibrary::GetCultureDisplayName(UKismetInternationalizationLibrary::GetCurrentCulture()));
	LanguageComboBox->OnSelectionChanged.AddDynamic(this, &UChangeLanguageWidget::OnLanguageSelected);
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppPassValueParameterByConstReference
void UChangeLanguageWidget::OnLanguageSelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	UKismetInternationalizationLibrary::SetCurrentCulture(*CulturesNames.Find(SelectedItem));
}
