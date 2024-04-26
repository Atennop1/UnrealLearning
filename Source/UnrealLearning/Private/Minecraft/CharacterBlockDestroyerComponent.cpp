// Copyright Atennop. All Rights Reserved.

#include "Minecraft/CharacterBlockDestroyerComponent.h"

#include "Camera/CameraComponent.h"
#include "Minecraft/MinecraftCharacter.h"
#include "Minecraft/Blocks/IBlock.h"

UCharacterBlockDestroyerComponent::UCharacterBlockDestroyerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	LineTraceLength = 500;
	Cooldown = 0.15f;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockDestroyerComponent::DestroyBlock(const FInputActionValue& Value)
{
	if (!CanPlace)
		return;
	
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	
	const UCameraComponent* CameraComponent = Cast<AMinecraftCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	const FVector StartPosition = CameraComponent->GetComponentTransform().GetLocation();
	const FVector EndPosition = StartPosition + CameraComponent->GetForwardVector() * LineTraceLength;

	if (FHitResult Result; GetWorld()->LineTraceSingleByChannel(Result, StartPosition, EndPosition, ECC_Visibility, CollisionParameters))
	{
		if (IBlock *Block = Cast<IBlock>(Result.GetActor()); Block != nullptr)
		{
			CanPlace = false;
			Block->Destroy();
			GetOwner()->GetWorldTimerManager().SetTimer(CooldownTimerHandle, [&] { CanPlace = true; }, Cooldown, false, Cooldown);
		}
	}
}

