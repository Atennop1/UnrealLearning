// Copyright Atennop. All Rights Reserved.

#include "Minecraft/MinecraftCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Minecraft/CharacterBlockDestroyerComponent.h"
#include "Minecraft/CharacterBlockPlacerComponent.h"
#include "Minecraft/CharacterBlockSelectorComponent.h"

AMinecraftCharacter::AMinecraftCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	CharacterBlockPlacer = CreateDefaultSubobject<UCharacterBlockPlacerComponent>(TEXT("CharacterBlockPlacer"));
	CharacterBlockDestroyer = CreateDefaultSubobject<UCharacterBlockDestroyerComponent>(TEXT("CharacterBlockDestroyer"));
	CharacterBlockSelector = CreateDefaultSubobject<UCharacterBlockSelectorComponent>(TEXT("CharacterBlockSelector"));
}

void AMinecraftCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);	
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, 1);
		}
	}

	auto *EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(PlaceBlockAction, ETriggerEvent::Triggered, CharacterBlockPlacer, &UCharacterBlockPlacerComponent::Place);
	EnhancedInputComponent->BindAction(DestroyBlockStartAction, ETriggerEvent::Triggered, CharacterBlockDestroyer, &UCharacterBlockDestroyerComponent::StartDestroying);
	EnhancedInputComponent->BindAction(DestroyBlockStopAction, ETriggerEvent::Triggered, CharacterBlockDestroyer, &UCharacterBlockDestroyerComponent::StopDestroying);
	EnhancedInputComponent->BindAction(SelectBlockAction, ETriggerEvent::Triggered, CharacterBlockSelector, &UCharacterBlockSelectorComponent::Select);
}
