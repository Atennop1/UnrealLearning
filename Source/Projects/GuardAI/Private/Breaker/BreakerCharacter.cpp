// Copyright Atennop. All Rights Reserved.

#include "Breaker/BreakerCharacter.h"

ABreakerCharacter::ABreakerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABreakerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(MovingComponent != nullptr)
	check(RotatingComponent != nullptr)
	check(CrouchingComponent != nullptr)
	check(JumpingComponent != nullptr)
}

bool ABreakerCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible, int32* UserData) const
{
	FHitResult HitResult;
	const FVector SightTargetLocation = GetMesh()->GetBoneLocation("clavicle_l");
	const bool WasHit = GetWorld()->LineTraceSingleByChannel(HitResult, ObserverLocation, SightTargetLocation, ECC_Visibility, FCollisionQueryParams(FName(), false, IgnoreActor));
	
	if (WasHit && HitResult.GetActor() == this)
	{
		OutSeenLocation = SightTargetLocation;
		OutSightStrength = 1;
		return true;
	}

	OutSightStrength = 0;
	return false;
}
