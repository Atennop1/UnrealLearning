// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/FirstPerson/Public/FirstPersonProjectile.h"
#include "PhysicsProjectile.generated.h"

UCLASS()
class PHYSICSSIMULATION_API APhysicsProjectile : public AFirstPersonProjectile
{
	GENERATED_BODY()

public:
	APhysicsProjectile();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> DestructorClass;

	UPROPERTY(EditDefaultsOnly)
	FVector DestructorSize;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
};
