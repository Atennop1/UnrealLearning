// Copyright Atennop. All Rights Reserved.

#include "Character/PhysicsProjectile.h"
#include "Components/SphereComponent.h"

APhysicsProjectile::APhysicsProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APhysicsProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentHit.AddDynamic(this, &APhysicsProjectile::OnProjectileHit);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APhysicsProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const FVector SpawnLocation = Hit.Location + Hit.Normal * -10;
	AActor *Destructor = GetWorld()->SpawnActor(DestructorClass, &SpawnLocation, &FRotator::ZeroRotator);
	
	Destructor->SetActorScale3D(DestructorSize);
	Destructor->SetLifeSpan(1);

	if (const auto MeshComponent = Cast<USkeletalMeshComponent>(OtherComp); IsValid(MeshComponent))
		MeshComponent->SetSimulatePhysics(true);
}
