// Copyright Atennop. All Rights Reserved.

#include "CustomCharacter.h"
#include "IPickupable.h"
#include "Components/CapsuleComponent.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void ACustomCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	IPickupable* PickUpable = Cast<IPickupable>(OtherActor);
	
	if (PickUpable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("[DEBUG] Overlap"));
		PickUpable->PickUp();
	}
}

void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACustomCharacter::OnBeginOverlap);
}
