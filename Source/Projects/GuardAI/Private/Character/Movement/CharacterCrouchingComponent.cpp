﻿// Copyright Atennop. All Rights Reserved.

#include "Character/Movement/CharacterCrouchingComponent.h"
#include "Character/GuardCharacter.h"
#include "Components/CapsuleComponent.h"

UCharacterCrouchingComponent::UCharacterCrouchingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterCrouchingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGuardCharacter>(GetOwner());
	check(Character != nullptr)
	
	FOnTimelineFloat OnTimelineUpdate;
	OnTimelineUpdate.BindUFunction(this, "CrouchUpdate");
	CrouchingTimeline.AddInterpFloat(CrouchingCurve, OnTimelineUpdate);
	NormalHalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
}

void UCharacterCrouchingComponent::StartCrouching()
{	
	IsCrouching = true;
	CrouchingTimeline.Play();
}

void UCharacterCrouchingComponent::StopCrouching()
{
	IsCrouching = false;
	CrouchingTimeline.Reverse();
}

void UCharacterCrouchingComponent::CrouchUpdate(float Alpha) const
{
	const float HalfHeight = FMath::Lerp(NormalHalfHeight, CrouchedHalfHeight, Alpha);
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(HalfHeight);
	Character->GetMesh()->SetRelativeLocation(FVector(0, 0, HalfHeight * -1));
}

void UCharacterCrouchingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CrouchingTimeline.TickTimeline(DeltaTime);
}
