// Copyright Atennop. All Rights Reserved.

#include "Minecraft/MinecraftCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Minecraft/CharacterBlockDestroyerComponent.h"
#include "Minecraft/CharacterBlockPlacerComponent.h"

AMinecraftCharacter::AMinecraftCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	CharacterBlockPlacer = CreateDefaultSubobject<UCharacterBlockPlacerComponent>(TEXT("CharacterBlockPlacer"));
	CharacterBlockDestroyer = CreateDefaultSubobject<UCharacterBlockDestroyerComponent>(TEXT("CharacterBlockDestroyer"));
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
	EnhancedInputComponent->BindAction(PlaceBlockInputAction, ETriggerEvent::Triggered, CharacterBlockPlacer, &UCharacterBlockPlacerComponent::PlaceBlock);
	EnhancedInputComponent->BindAction(DestroyBlockInputAction, ETriggerEvent::Triggered, CharacterBlockDestroyer, &UCharacterBlockDestroyerComponent::DestroyBlock);
}
