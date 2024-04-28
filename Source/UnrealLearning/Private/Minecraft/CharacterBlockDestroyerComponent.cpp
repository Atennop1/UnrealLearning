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
void UCharacterBlockDestroyerComponent::StartBlockDestroying(const FInputActionValue& Value)
{
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	
	const UCameraComponent* CameraComponent = Cast<AMinecraftCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	const FVector StartPosition = CameraComponent->GetComponentTransform().GetLocation();
	const FVector EndPosition = StartPosition + CameraComponent->GetForwardVector() * LineTraceLength;

	if (FHitResult Result; GetWorld()->LineTraceSingleByChannel(Result, StartPosition, EndPosition, ECC_Visibility, CollisionParameters))
	{
		if (IBlock *Block = Cast<IBlock>(Result.GetActor()); Block != nullptr)
		{
			if (CurrentBlock == Block || !CanDestroy)
				return;
			
			CanDestroy = false;
			StopBlockDestroying(NULL);
			CurrentBlock.SetInterface(Block);
			CurrentBlock.SetObject(Cast<UObject>(Block));
			
			CurrentBlock->StartDestroying();
			GetOwner()->GetWorldTimerManager().SetTimer(CooldownTimerHandle, [&] { CanDestroy = true; }, Cooldown, false, Cooldown);
			return;
		}
	}

	StopBlockDestroying(NULL);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockDestroyerComponent::StopBlockDestroying(const FInputActionValue& Value)
{
	if (CurrentBlock != nullptr)
		CurrentBlock->StopDestroying();

	CurrentBlock = nullptr;
}

