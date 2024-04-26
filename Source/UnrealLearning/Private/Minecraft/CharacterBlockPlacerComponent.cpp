// Copyright Atennop. All Rights Reserved.

#include "Minecraft/CharacterBlockPlacerComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Minecraft/IBlock.h"
#include "Minecraft/MinecraftCharacter.h"

UCharacterBlockPlacerComponent::UCharacterBlockPlacerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterBlockPlacerComponent::PlaceBlock(const FInputActionValue& Value)
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	
	const UCameraComponent* CameraComponent = Cast<AMinecraftCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	const FVector StartPosition = CameraComponent->GetComponentTransform().GetLocation();
	const FVector TheoreticalEndPosition = StartPosition + CameraComponent->GetForwardVector() * LineTraceLength;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, TheoreticalEndPosition, ECC_Visibility, CollisionParameters);
	bool WasHit = HitResult.GetActor() != nullptr;
	FVector PracticalEndPosition = WasHit ? HitResult.Location : TheoreticalEndPosition;

	if (WasHit)
	{
		TArray<AActor*> OverlappedActors;
		FVector SpawnLocation = (PracticalEndPosition - CameraComponent->GetForwardVector() * LineTraceLength * 0.015f).GridSnap(100);
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SpawnLocation, 30.0f, TArray<TEnumAsByte<EObjectTypeQuery>>(), nullptr, TArray<AActor*>(), OverlappedActors);
		
		if (!OverlappedActors.ContainsByPredicate([&](const AActor* Actor) { return Cast<ACharacter>(Actor) || Cast<IBlock>(Actor); }))
			GetWorld()->SpawnActor(BlockBlueprint, &SpawnLocation);
	}

	if (!Debug)
		return;
	
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartPosition, PracticalEndPosition, FColor::Red, 10);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "[DEBUG] Hit object name: " + (WasHit ? HitResult.GetActor()->GetName() : "no hit object"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "[DEBUG] Hit position: " + (WasHit ? UKismetStringLibrary::Conv_VectorToString(PracticalEndPosition) : "none"));
}
