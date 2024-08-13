// Copyright Atennop. All Rights Reserved.

#include "Character/Shooting/NetworkCharacterPeekingComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/NetworkCharacter.h"

UNetworkCharacterPeekingComponent::UNetworkCharacterPeekingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNetworkCharacterPeekingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(IsValid(Character))
	
	Camera = Character->GetComponentByClass<UCameraComponent>();
	check(Camera != nullptr)
	
	FOnTimelineFloat OnLeftTimelineUpdate;
	FOnTimelineFloat OnRightTimelineUpdate;
	OnLeftTimelineUpdate.BindUFunction(this, "PeekingLeftUpdate");
	OnRightTimelineUpdate.BindUFunction(this, "PeekingRightUpdate");
	
	PeekingLeftTimeline.AddInterpFloat(PeekingCurve, OnLeftTimelineUpdate);
	PeekingRightTimeline.AddInterpFloat(PeekingCurve, OnRightTimelineUpdate);
	NormalCameraRelativeLocation = Camera->GetRelativeLocation();
}

void UNetworkCharacterPeekingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	PeekingLeftTimeline.TickTimeline(DeltaTime);
	PeekingRightTimeline.TickTimeline(DeltaTime);
	Camera->SetRelativeLocation(NormalCameraRelativeLocation + FVector(0, CurrentLeftPeekingAmount + CurrentRightPeekingAmount, 0));
}

void UNetworkCharacterPeekingComponent::PeekingLeftUpdate(float Alpha)
{
	CurrentLeftPeekingAmount = -Alpha * PeekingAmount;
}

void UNetworkCharacterPeekingComponent::PeekingRightUpdate(float Alpha)
{
	CurrentRightPeekingAmount = Alpha * PeekingAmount;
}

void UNetworkCharacterPeekingComponent::MulticastStartPeekingLeft_Implementation()
{
	if (Character->GetHealthComponent()->IsAlive())
		PeekingLeftTimeline.Play();
}

void UNetworkCharacterPeekingComponent::MulticastStartPeekingRight_Implementation()
{
	if (Character->GetHealthComponent()->IsAlive())
		PeekingRightTimeline.Play();
}

