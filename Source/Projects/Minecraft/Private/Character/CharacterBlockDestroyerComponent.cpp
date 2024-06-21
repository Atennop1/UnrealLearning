// Copyright Atennop. All Rights Reserved.

#include "Character/CharacterBlockDestroyerComponent.h"
#include "Character/MinecraftCharacter.h"
#include "Blocks/IBlock.h"

UCharacterBlockDestroyerComponent::UCharacterBlockDestroyerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Cooldown = 0.15f;
}

void UCharacterBlockDestroyerComponent::BeginPlay()
{
	Super::BeginPlay();
	Pointing = Cast<UCharacterPointingComponent>(GetOwner()->GetComponentByClass(UCharacterPointingComponent::StaticClass()));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockDestroyerComponent::StartDestroying(const FInputActionValue& Value)
{
	IBlock *Block = Pointing->GetPointingBlock();
	if (CurrentBlock == Block || !CanDestroy)
		return;
	
	if (Block == nullptr)
	{
		StopDestroying(NULL);
		return;
	}

	CanDestroy = false;
	StopDestroying(NULL);
	CurrentBlock.SetInterface(Block);
	CurrentBlock.SetObject(Cast<UObject>(Block));
	
	CurrentBlock->StartDestroying();
	GetOwner()->GetWorldTimerManager().SetTimer(CooldownTimerHandle, [&] { CanDestroy = true; }, Cooldown, false, Cooldown);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockDestroyerComponent::StopDestroying(const FInputActionValue& Value)
{
	if (CurrentBlock != nullptr)
		CurrentBlock->StopDestroying();

	CurrentBlock = nullptr;
}
