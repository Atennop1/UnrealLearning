// Copyright Atennop. All Rights Reserved.

#include "Breaker/Other/CharacterFootstepsComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AISense_Hearing.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UCharacterFootstepsComponent::UCharacterFootstepsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterFootstepsComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABreakerCharacter>(GetOwner());
	check(IsValid(Character))
}

void UCharacterFootstepsComponent::PlayFootstep()
{
	FHitResult HitResult;
	const bool WasHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Character->GetActorLocation(), Character->GetActorLocation() - FVector(0, 0, Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 10),
		TraceTypeQuery1, false, { Character }, EDrawDebugTrace::None, HitResult, true);

	if (WasHit && FootstepsSounds.Contains(HitResult.Component->GetMaterial(0)->GetPhysicalMaterial()->SurfaceType))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootstepsSounds[HitResult.Component->GetMaterial(0)->GetPhysicalMaterial()->SurfaceType], HitResult.Location);
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), Character->GetActorLocation(), 1, Character, 0);
	}
}

