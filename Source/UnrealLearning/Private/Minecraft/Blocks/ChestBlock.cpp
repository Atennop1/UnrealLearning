// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Blocks/ChestBlock.h"

AChestBlock::AChestBlock() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AChestBlock::Interact()
{
	IsOpened = !IsOpened;

	if (IsOpened)
	{
		OpeningTimeline.Play();
		return;
	}

	OpeningTimeline.Reverse();
}

void AChestBlock::OnTimelineTick(float Value) const
{
	const FTransform Transform = LidPivot->GetComponentTransform() ;
	const FRotator Rotator = Transform.Rotator();
	LidPivot->SetWorldTransform(FTransform(FRotator(Value, Rotator.Yaw, Rotator.Roll), Transform.GetTranslation(), Transform.GetScale3D()));
}

void AChestBlock::BeginPlay()
{
	Super::BeginPlay();
	
	for (const auto Iterator : GetComponentsByTag(USceneComponent::StaticClass(), TEXT("LidPivot")))
		LidPivot = Cast<USceneComponent>(Iterator);
	
	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, "OnTimelineTick");
	OpeningTimeline.AddInterpFloat(OpeningCurve, ProgressUpdate);
}

void AChestBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OpeningTimeline.TickTimeline(DeltaTime);
}
