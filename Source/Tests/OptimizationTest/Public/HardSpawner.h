// Copyright Atennop. All Rights Reserved.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HardSpawner.generated.h"

UCLASS()
class OPTIMIZATIONTEST_API AHardSpawner : public AActor
{
	GENERATED_BODY()

public:
	AHardSpawner();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UBoxComponent *Trigger = nullptr;

	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AActor> ClassToSpawn;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
