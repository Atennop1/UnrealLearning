﻿// Copyright Atennop. All Rights Reserved.

#include "Breaker/Other/CharacterFootstepsComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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

void UCharacterFootstepsComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(FootstepCooldownHandle);
}

void UCharacterFootstepsComponent::PlayFootstep()
{
	if (!CanFootstep)
		return;
	
	FHitResult HitResult;
	const bool WasHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Character->GetActorLocation(), Character->GetActorLocation() - FVector(0, 0, Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 10),
		TraceTypeQuery1, false, { Character }, EDrawDebugTrace::None, HitResult, true);

	if (WasHit)
	{
		CanFootstep = false;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootstepsCue, HitResult.Location);
		GetWorld()->GetTimerManager().SetTimer(FootstepCooldownHandle, [&] { CanFootstep = true; }, FootstepCooldown, false);
	}
}

