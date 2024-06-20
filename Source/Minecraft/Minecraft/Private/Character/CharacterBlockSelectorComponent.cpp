// Copyright Atennop. All Rights Reserved.

#include "Character/CharacterBlockSelectorComponent.h"
#include "InputActionValue.h"

UCharacterBlockSelectorComponent::UCharacterBlockSelectorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterBlockSelectorComponent::BeginPlay()
{
	Super::BeginPlay();
	BlockPlacer = Cast<UCharacterBlockPlacerComponent>(GetOwner()->GetComponentByClass(UCharacterBlockPlacerComponent::StaticClass()));
	BlockPlacer->Select(BlocksByIndex[1]);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockSelectorComponent::Select(const FInputActionValue& Value)
{
	if (const int Index = (int)Value.Get<float>(); BlocksByIndex.Contains(Index))
		BlockPlacer->Select(BlocksByIndex[Index]);
}
