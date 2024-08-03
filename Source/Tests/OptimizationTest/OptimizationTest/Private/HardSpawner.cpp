// Copyright Atennop. All Rights Reserved.

#include "HardSpawner.h"
#include "GameFramework/Character.h"

AHardSpawner::AHardSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHardSpawner::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHardSpawner::OnTriggerBeginOverlap);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AHardSpawner::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto Character = Cast<ACharacter>(OtherActor); !IsValid(Character) || !Character->IsPlayerControlled())
		return;
	
	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetScale3D(FVector::One());
	GetWorld()->SpawnActor(ClassToSpawn, &SpawnTransform);
}

