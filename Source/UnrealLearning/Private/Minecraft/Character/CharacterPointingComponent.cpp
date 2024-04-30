// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Character/CharacterPointingComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Minecraft/Blocks/IBlock.h"
#include "Minecraft/Character/MinecraftCharacter.h"

UCharacterPointingComponent::UCharacterPointingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	LineTraceLength = 500;
}

void UCharacterPointingComponent::Calculate()
{
	if (WasCalculatedThisFrame)
		return;
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	
	const UCameraComponent* CameraComponent = Cast<AMinecraftCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	const FVector StartPosition = CameraComponent->GetComponentTransform().GetLocation();
	const FVector TheoreticalEndPosition = StartPosition + CameraComponent->GetForwardVector() * LineTraceLength;

	bool IsPointingAtSomething = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, TheoreticalEndPosition, ECC_Visibility, CollisionParameters);
	PointLocation = IsPointingAtSomething ? HitResult.Location : TheoreticalEndPosition;
	PointedObject = HitResult.GetActor();
	WasCalculatedThisFrame = true;
	
	if (!Debug)
		return;
	
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartPosition, PointLocation, FColor::Red, 10);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "[DEBUG] Hit object name: " + (IsPointingAtSomething ? HitResult.GetActor()->GetName() : "no hit object"));
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "[DEBUG] Hit position: " + (IsPointingAtSomething ? UKismetStringLibrary::Conv_VectorToString(PointLocation) : "none"));
}

void UCharacterPointingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	WasCalculatedThisFrame = false;
}

UObject* UCharacterPointingComponent::GetPointingObject()
{
	Calculate();
	return PointedObject;
}

IBlock* UCharacterPointingComponent::GetPointingBlock()
{
	Calculate();
	return Cast<IBlock>(PointedObject);
}

FVector UCharacterPointingComponent::GetPointLocation()
{
	Calculate();
	return PointLocation;
}
