// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Healer.generated.h"

UCLASS()
class DEMOUMG_API AHealer : public AActor
{
	GENERATED_BODY()

public:
	AHealer();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	int HealingAmount = 20;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UPrimitiveComponent *Collision = nullptr;

	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
