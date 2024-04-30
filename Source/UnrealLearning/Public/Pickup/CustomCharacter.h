// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FirstPerson/UnrealLearningCharacter.h"
#include "CustomCharacter.generated.h"

UCLASS(Meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API ACustomCharacter : public AUnrealLearningCharacter
{
private:
	GENERATED_BODY()
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult &SweepResult);
	
	virtual void BeginPlay() override;
};

