// Copyright Atennop. All Rights Reserved.

#include "PickupCharacter.h"
#include "Components/CapsuleComponent.h"
#include "IPickupable.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void APickupCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	IPickupable* Pickupable = Cast<IPickupable>(OtherActor);
	
	if (Pickupable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("[DEBUG] Overlap"));
		Pickupable->PickUp();
	}
}

void APickupCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APickupCharacter::OnBeginOverlap);
}
