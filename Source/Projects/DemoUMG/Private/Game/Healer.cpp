// Copyright Atennop. All Rights Reserved.

#include "Game/Healer.h"
#include "Game/HealthComponent.h"

AHealer::AHealer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHealer::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(Collision))
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AHealer::OnCollisionBeginOverlap);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AHealer::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHealthComponent *HealthComponent = OtherActor->GetComponentByClass<UHealthComponent>();
	if (!IsValid(HealthComponent))
		return;

	HealthComponent->Heal(HealingAmount);
}



