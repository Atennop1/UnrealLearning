// Copyright Atennop. All Rights Reserved.

#include "Plate/Door.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(DoorMesh))

	FOnTimelineFloat OnTimelineUpdated;
	OnTimelineUpdated.BindUFunction(this, "OnTimelineUpdated");
	OpeningTimeline.AddInterpFloat(Curve, OnTimelineUpdated);
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OpeningTimeline.TickTimeline(DeltaTime);
}

void ADoor::Activate()
{
	OpeningTimeline.Play();
}

void ADoor::Deactivate()
{
	OpeningTimeline.Reverse();
}

void ADoor::OnTimelineUpdated(float Alpha) const
{
	DoorMesh->SetRelativeRotation(FRotator(0, FMath::Lerp(ClosedRotationZ, OpenedRotationZ, Alpha), 0));
}

