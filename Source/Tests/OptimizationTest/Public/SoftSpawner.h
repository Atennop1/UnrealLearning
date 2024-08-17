// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SoftSpawner.generated.h"

UCLASS()
class OPTIMIZATIONTEST_API ASoftSpawner : public AActor
{
	GENERATED_BODY()

public:
	ASoftSpawner();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UBoxComponent *Trigger = nullptr;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<AActor> ClassToSpawn;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnActor();
};
