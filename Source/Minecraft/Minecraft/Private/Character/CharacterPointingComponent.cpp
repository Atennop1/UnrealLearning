// Copyright Atennop. All Rights Reserved.

#include "Character/CharacterPointingComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blocks/IBlock.h"
#include "Character/MinecraftCharacter.h"

UCharacterPointingComponent::UCharacterPointingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	LineTraceLength = 500;
}

void UCharacterPointingComponent::Calculate()
{
	if (WasCalculatedThisFrame)
		return;
	
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	
	const UCameraComponent* CameraComponent = Cast<AMinecraftCharacter>(GetOwner())->GetComponentByClass<UCameraComponent>();
	const FVector StartPosition = CameraComponent->GetComponentTransform().GetLocation();
	const FVector TheoreticalEndPosition = StartPosition + CameraComponent->GetForwardVector() * LineTraceLength;

	WasCalculatedThisFrame = true;
	IsPointing = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, TheoreticalEndPosition, ECC_Visibility, CollisionParameters);
	const FVector PointLocation = IsPointing ? HitResult.Location : TheoreticalEndPosition;
	
	if (!Debug)
		return;
	
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartPosition, PointLocation, FColor::Red, 10);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "[DEBUG] Hit object name: " + (IsPointing ? HitResult.GetActor()->GetName() : "no hit object"));
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "[DEBUG] Hit position: " + (IsPointing ? UKismetStringLibrary::Conv_VectorToString(PointLocation) : "none"));
}

void UCharacterPointingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	WasCalculatedThisFrame = false;
}

bool UCharacterPointingComponent::IsPointingAtSomething()
{
	Calculate();
	return IsPointing;
}

IBlock* UCharacterPointingComponent::GetPointingBlock()
{
	Calculate();
	return Cast<IBlock>(HitResult.GetActor());
}

FHitResult& UCharacterPointingComponent::GetHit()
{
	Calculate();
	return HitResult;
}
