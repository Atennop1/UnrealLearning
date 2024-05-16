// Copyright Atennop. All Rights Reserved.

#include "SavingTest/SavingCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASavingCharacter::ASavingCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	SaveLoadComponent = CreateDefaultSubobject<UCharacterSaveLoadComponent>(TEXT("SaveLoad"));
}

void ASavingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const auto PlayerController = Cast<APlayerController>(GetController()))
	{
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	auto *EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(SaveInputAction, ETriggerEvent::Triggered, SaveLoadComponent, &UCharacterSaveLoadComponent::Save);
	EnhancedInputComponent->BindAction(LoadInputAction, ETriggerEvent::Triggered, SaveLoadComponent, &UCharacterSaveLoadComponent::Load);
}

