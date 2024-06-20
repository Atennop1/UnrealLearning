// Copyright Atennop. All Rights Reserved.

#include "Character/CharacterBlockPlacerComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/MinecraftCharacter.h"
#include "Blocks/IBlock.h"

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
	if (Pointing->IsPointingAtSomething() && Pointing != nullptr)
	{
		TArray<AActor*> OverlappedActors;
		const AMinecraftCharacter *Character = Cast<AMinecraftCharacter>(GetOwner());
		const FRotator SpawnRotator = FRotator(0, Character->GetControlRotation().Yaw + 180, 0).GridSnap(FRotator(90, 90, 90));
		const FVector SpawnPosition = (Pointing->GetHit().Location + Pointing->GetHit().ImpactNormal * 60.f).GridSnap(100);
		const FTransform SpawnTransform = FTransform(SpawnRotator, SpawnPosition, FVector::OneVector);
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SpawnPosition, 45.0f, TArray<TEnumAsByte<EObjectTypeQuery>>(), nullptr, TArray<AActor*>(), OverlappedActors);
		
		if (!OverlappedActors.ContainsByPredicate([&](const AActor* Actor) { return Cast<ACharacter>(Actor) || Cast<IBlock>(Actor); }) && CanPlace)
		{
			CanPlace = false;
			GetWorld()->SpawnActor(BlockBlueprint, &SpawnTransform);
			GetOwner()->GetWorldTimerManager().SetTimer(CooldownTimerHandle, [&] { CanPlace = true; }, Cooldown, false, Cooldown);
		}
	}
}
