// Copyright Atennop. All Rights Reserved.

#include "SavingTest/CharacterSaveLoadComponent.h"
#include "SavingTest/CharacterPositionSave.h"
#include "Kismet/GameplayStatics.h"

UCharacterSaveLoadComponent::UCharacterSaveLoadComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterSaveLoadComponent::Save(const FInputActionValue& Binding)
{
	const auto Save = Cast<UCharacterPositionSave>(UGameplayStatics::CreateSaveGameObject(UCharacterPositionSave::StaticClass()));
	Save->CharacterPosition = GetOwner()->GetTransform().GetLocation();
	UGameplayStatics::SaveGameToSlot(Save, "CharacterPosition", 0);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterSaveLoadComponent::Load(const FInputActionValue& Binding)
{
	if (!UGameplayStatics::DoesSaveGameExist("CharacterPosition", 0))
		return;
	
	const auto Save = Cast<UCharacterPositionSave>(UGameplayStatics::LoadGameFromSlot("CharacterPosition", 0));
	GetOwner()->SetActorLocation(Save->CharacterPosition);
}
