// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SublevelsDoor.generated.h"

UCLASS()
class OPTIMIZATIONTEST_API ASublevelsDoor : public AActor
{
	GENERATED_BODY()

public:
	ASublevelsDoor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UBoxComponent *FirstTrigger = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UBoxComponent *SecondTrigger = nullptr;

	UPROPERTY(EditInstanceOnly)
	TSoftObjectPtr<UWorld> FirstSublevel;

	UPROPERTY(EditInstanceOnly)
	TSoftObjectPtr<UWorld> SecondSublevel;
	bool IsFirstCurrent = true;

	UFUNCTION()
	void OnFirstBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSecondBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
