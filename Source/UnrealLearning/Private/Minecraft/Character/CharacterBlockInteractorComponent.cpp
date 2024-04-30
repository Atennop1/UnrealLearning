// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Character/CharacterBlockInteractorComponent.h"
#include "Camera/CameraComponent.h"
#include "Minecraft/Blocks/IInteractableBlock.h"
#include "Minecraft/Character/MinecraftCharacter.h"

UCharacterBlockInteractorComponent::UCharacterBlockInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockInteractorComponent::Interact(const FInputActionValue& Value)
{
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	
	const UCameraComponent* CameraComponent = Cast<AMinecraftCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	const FVector StartPosition = CameraComponent->GetComponentTransform().GetLocation();
	const FVector EndPosition = StartPosition + CameraComponent->GetForwardVector() * LineTraceLength;

	if (FHitResult Result; GetWorld()->LineTraceSingleByChannel(Result, StartPosition, EndPosition, ECC_Visibility, CollisionParameters))
		if (IInteractableBlock *Block = Cast<IInteractableBlock>(Result.GetActor()); Block != nullptr)
			Block->Interact();
}
