﻿// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Blocks/DefaultBlock.h"

ADefaultBlock::ADefaultBlock()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void ADefaultBlock::BeginPlay()
{
	Super::BeginPlay();
	TArray<UActorComponent*> Components;
	GetComponents(UStaticMeshComponent::StaticClass(), Components);
	
	for (const auto Component : Components)
	{
		Mesh = Cast<UStaticMeshComponent>(Component);
		
		if (MaterialInstance == nullptr)
			MaterialInstance = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
		
		MaterialInstance->SetScalarParameterValue("DestroyingProgress", 0);
		Mesh->SetMaterial(0, MaterialInstance);
	}
	
	FOnTimelineFloat ProgressUpdate;
	FOnTimelineEvent FinishedEvent;
	ProgressUpdate.BindUFunction(this, FName("OnDestroyingTick"));
	FinishedEvent.BindUFunction(this, FName("OnDestroyingFinished"));
	
	DestroyingTimeline.AddInterpFloat(DestroyingCurve, ProgressUpdate);
	DestroyingTimeline.SetTimelineFinishedFunc(FinishedEvent);
	DestroyingTimeline.SetPlayRate(DestroyingCurveSpeed);
}

void ADefaultBlock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	DestroyingTimeline.TickTimeline(DeltaSeconds);
}

void ADefaultBlock::OnDestroyingTick(float Alpha) const
{
	MaterialInstance->SetScalarParameterValue("DestroyingProgress", Alpha);
}

void ADefaultBlock::OnDestroyingFinished()
{
	GetWorld()->DestroyActor(this);
}

void ADefaultBlock::StartDestroying()
{
	DestroyingTimeline.PlayFromStart();
}

void ADefaultBlock::StopDestroying()
{
	MaterialInstance->SetScalarParameterValue("DestroyingProgress", 0);
	DestroyingTimeline.Stop();
}

