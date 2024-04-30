// Copyright Atennop. All Rights Reserved.

#include "Minecraft/Blocks/DefaultBlock.h"

ADefaultBlock::ADefaultBlock()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void ADefaultBlock::BeginPlay()
{
	Super::BeginPlay();
	FOnTimelineFloat ProgressUpdate;
	FOnTimelineEvent FinishedEvent;
	
	MaterialInstance = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
	Mesh->SetMaterial(0, MaterialInstance);
	MaterialInstance->SetScalarParameterValue("DestroyingProgress", 0);

	ProgressUpdate.BindUFunction(this, FName("OnDestroyingTick"));
	FinishedEvent.BindUFunction(this, FName("OnDestroyingFinished"));
	DestroyingTimeline.AddInterpFloat(DestroyingCurve, ProgressUpdate);
	DestroyingTimeline.SetTimelineFinishedFunc(FinishedEvent);
	DestroyingTimeline.SetPlayRate(CurveSpeed);
}

void ADefaultBlock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	DestroyingTimeline.TickTimeline(DeltaSeconds);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ADefaultBlock::OnDestroyingTick(float Alpha)
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

