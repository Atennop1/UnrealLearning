// Copyright Atennop. All Rights Reserved.

#include "Models/Character/DemoCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

ADemoCharacter::ADemoCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GamePausingComponent = CreateDefaultSubobject<UCharacterGamePausingComponent>(TEXT("GamePausingComponent"));
}

void ADemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	auto *EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(PauseInputAction, ETriggerEvent::Triggered, GamePausingComponent, &UCharacterGamePausingComponent::Pause);
}

