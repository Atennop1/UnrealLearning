// Copyright Atennop. All Rights Reserved.

#include "Character/Components/NetworkCharacterCrouchingComponent.h"
#include "Character/NetworkCharacter.h"
#include "Components/CapsuleComponent.h"

UNetworkCharacterCrouchingComponent::UNetworkCharacterCrouchingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNetworkCharacterCrouchingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(Character != nullptr)
	
	FOnTimelineFloat OnTimelineUpdate;
	OnTimelineUpdate.BindUFunction(this, "CrouchUpdate");
	CrouchingTimeline.AddInterpFloat(CrouchingCurve, OnTimelineUpdate);
	NormalHalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
}

void UNetworkCharacterCrouchingComponent::StartCrouching()
{	
	IsCrouching = true;
	CrouchingTimeline.Play();
}

void UNetworkCharacterCrouchingComponent::StopCrouching()
{
	IsCrouching = false;
	CrouchingTimeline.Reverse();
}

void UNetworkCharacterCrouchingComponent::CrouchUpdate(float Alpha) const
{
	const float HalfHeight = FMath::Lerp(NormalHalfHeight, CrouchedHalfHeight, Alpha);
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(HalfHeight);
	Character->GetMesh()->SetRelativeLocation(FVector(0, 0, HalfHeight * -1));
}

void UNetworkCharacterCrouchingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CrouchingTimeline.TickTimeline(DeltaTime);
}
