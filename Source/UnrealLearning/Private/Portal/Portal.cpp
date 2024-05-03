// Copyright Atennop. All Rights Reserved.

#include "Portal/Portal.h"
#include "Components/SceneCaptureComponent2D.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;
	Capture1 = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture1"));
	Capture2 = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture2"));

	Capture1->SetupAttachment(Cast<USceneComponent>(GetComponentsByTag(USceneComponent::StaticClass(), "First")[0]));
	Capture2->SetupAttachment(Cast<USceneComponent>(GetComponentsByTag(USceneComponent::StaticClass(), "Second")[0]));
}
