// Copyright Atennop. All Rights Reserved.

#include "Character/CharacterBlockInteractorComponent.h"
#include "Blocks/IInteractableBlock.h"
#include "Character/CharacterPointingComponent.h"
#include "Character/MinecraftCharacter.h"

UCharacterBlockInteractorComponent::UCharacterBlockInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterBlockInteractorComponent::BeginPlay()
{
	Super::BeginPlay();
	Pointing = Cast<UCharacterPointingComponent>(GetOwner()->GetComponentByClass(UCharacterPointingComponent::StaticClass()));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockInteractorComponent::Interact(const FInputActionValue& Value)
{
	if (IInteractableBlock *Block = Cast<IInteractableBlock>(Pointing->GetPointingBlock()); Block != nullptr)
		Block->Interact();
}
