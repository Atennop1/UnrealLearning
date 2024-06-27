// Copyright Atennop. All Rights Reserved.

#include "Models/Health/Damager.h"
#include "Models/Health/HealthComponent.h"

ADamager::ADamager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADamager::BeginPlay()
{
	Super::BeginPlay();
	check(IsValid(Collision))
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADamager::OnCollisionBeginOverlap);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ADamager::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHealthComponent *HealthComponent = OtherActor->GetComponentByClass<UHealthComponent>();
	if (!IsValid(HealthComponent))
		return;

	HealthComponent->Damage(DamageAmount);
}
