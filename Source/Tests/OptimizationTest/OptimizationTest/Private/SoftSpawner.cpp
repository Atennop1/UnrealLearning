// Copyright Atennop. All Rights Reserved.

#include "SoftSpawner.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Character.h"

ASoftSpawner::ASoftSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASoftSpawner::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASoftSpawner::OnTriggerBeginOverlap);	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASoftSpawner::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto Character = Cast<ACharacter>(OtherActor); IsValid(Character) && Character->IsPlayerControlled())
		UAssetManager::GetStreamableManager().RequestAsyncLoad(ClassToSpawn.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &ASoftSpawner::SpawnActor));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASoftSpawner::SpawnActor()
{
	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetScale3D(FVector::One());
	GetWorld()->SpawnActor(ClassToSpawn.Get(), &SpawnTransform);
}


