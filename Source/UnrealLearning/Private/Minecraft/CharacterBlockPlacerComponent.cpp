// Copyright Atennop. All Rights Reserved.

#include "Minecraft/CharacterBlockPlacerComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Minecraft/MinecraftCharacter.h"
#include "Minecraft/Blocks/IBlock.h"

UCharacterBlockPlacerComponent::UCharacterBlockPlacerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	LineTraceLength = 500;
	Cooldown = 0.15f;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockPlacerComponent::PlaceBlock(const FInputActionValue& Value)
{
	if (!CanPlace)
		return;
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	
	const UCameraComponent* CameraComponent = Cast<AMinecraftCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	const FVector StartPosition = CameraComponent->GetComponentTransform().GetLocation();
	const FVector TheoreticalEndPosition = StartPosition + CameraComponent->GetForwardVector() * LineTraceLength;

	bool WasHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, TheoreticalEndPosition, ECC_Visibility, CollisionParameters);
	FVector PracticalEndPosition = WasHit ? HitResult.Location : TheoreticalEndPosition;

	if (WasHit)
	{
		TArray<AActor*> OverlappedActors;
		FVector SpawnLocation = (PracticalEndPosition - CameraComponent->GetForwardVector() * LineTraceLength * 0.015f).GridSnap(100);
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SpawnLocation, 30.0f, TArray<TEnumAsByte<EObjectTypeQuery>>(), nullptr, TArray<AActor*>(), OverlappedActors);
		
		if (!OverlappedActors.ContainsByPredicate([&](const AActor* Actor) { return Cast<ACharacter>(Actor) || Cast<IBlock>(Actor); }))
		{
			CanPlace = false;
			GetWorld()->SpawnActor(BlockBlueprint, &SpawnLocation);
			GetOwner()->GetWorldTimerManager().SetTimer(CooldownTimerHandle, [&] { CanPlace = true; }, Cooldown, false, Cooldown);
		}
	}

	if (!Debug)
		return;
	
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartPosition, PracticalEndPosition, FColor::Red, 10);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "[DEBUG] Hit object name: " + (WasHit ? HitResult.GetActor()->GetName() : "no hit object"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "[DEBUG] Hit position: " + (WasHit ? UKismetStringLibrary::Conv_VectorToString(PracticalEndPosition) : "none"));
}
