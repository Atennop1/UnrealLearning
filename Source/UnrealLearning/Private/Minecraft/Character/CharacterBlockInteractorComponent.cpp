// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Character/CharacterBlockInteractorComponent.h"
#include "Minecraft/Blocks/IInteractableBlock.h"
#include "Minecraft/Character/CharacterPointingComponent.h"
#include "Minecraft/Character/MinecraftCharacter.h"

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
