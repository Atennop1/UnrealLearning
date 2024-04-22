// Copyright Atennop. All Rights Reserved.

#include "Minecraft/CharacterBlockPlacerComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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
	
	const UCameraComponent* Camera = Cast<AMinecraftCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	const FVector Start = Camera->GetComponentTransform().GetLocation();
	const FVector End = Start + Camera->GetForwardVector() * LineTraceLength;

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, CollisionParameters);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, HitResult.GetActor() != nullptr ? HitResult.ImpactPoint : End, FColor::Red, 100);
	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "[DEBUG] Hit object name: " + (HitResult.GetActor() != nullptr ? HitResult.GetActor()->GetName() : "No hit object"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "[DEBUG] Hit position: " + UKismetStringLibrary::Conv_VectorToString(HitResult.ImpactPoint));
}


