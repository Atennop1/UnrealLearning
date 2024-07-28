// Copyright Atennop. All Rights Reserved.

#include "Character/PhysicsCharacter.h"
#include "EnhancedInputComponent.h"
#include "Character/PhysicsCharacterGrabbingComponent.h"

APhysicsCharacter::APhysicsCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GrabbingComponent = CreateDefaultSubobject<UPhysicsCharacterGrabbingComponent>(TEXT("GrabbingComponent"));
}

void APhysicsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		EnhancedInputComponent->BindAction(GrabInputAction, ETriggerEvent::Triggered, GrabbingComponent, &UPhysicsCharacterGrabbingComponent::Grab);
}
