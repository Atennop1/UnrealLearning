// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Character/CharacterBlockPlacerComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Minecraft/Character/MinecraftCharacter.h"
#include "Minecraft/Blocks/IBlock.h"

UCharacterBlockPlacerComponent::UCharacterBlockPlacerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Cooldown = 0.15f;
}

void UCharacterBlockPlacerComponent::BeginPlay()
{
	Super::BeginPlay();
	Pointing = Cast<UCharacterPointingComponent>(GetOwner()->GetComponentByClass(UCharacterPointingComponent::StaticClass()));
}

void UCharacterBlockPlacerComponent::Select(const TSubclassOf<AActor> Block)
{
	BlockBlueprint = Block;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockPlacerComponent::Place(const FInputActionValue& Value)
{
	if (Pointing->GetPointingObject() != nullptr)
	{
		TArray<AActor*> OverlappedActors;
		const AMinecraftCharacter *Character = Cast<AMinecraftCharacter>(GetOwner());
		const UCameraComponent *CameraComponent = Character->GetFirstPersonCameraComponent();
		const FTransform SpawnTransform = FTransform(FRotator(0, Character->GetControlRotation().Yaw + 180, 0).GridSnap(FRotator(90, 90, 90)), (Pointing->GetPointLocation() - CameraComponent->GetForwardVector() * 7.5f).GridSnap(100), FVector::OneVector);
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SpawnTransform.GetLocation(), 45.0f, TArray<TEnumAsByte<EObjectTypeQuery>>(), nullptr, TArray<AActor*>(), OverlappedActors);
		
		if (!OverlappedActors.ContainsByPredicate([&](const AActor* Actor) { return Cast<ACharacter>(Actor) || Cast<IBlock>(Actor); }) && CanPlace)
		{
			CanPlace = false;
			GetWorld()->SpawnActor(BlockBlueprint, &SpawnTransform);
			GetOwner()->GetWorldTimerManager().SetTimer(CooldownTimerHandle, [&] { CanPlace = true; }, Cooldown, false, Cooldown);
		}
	}
}
