// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FirstPersonCharacter.h"
#include "PickupCharacter.generated.h"

UCLASS(Meta=(BlueprintSpawnableComponent))
class PICKUPSTEST_API APickupCharacter : public AFirstPersonCharacter
{
private:
	GENERATED_BODY()
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult &SweepResult);
	
	virtual void BeginPlay() override;
};

