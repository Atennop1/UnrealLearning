// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damager.generated.h"

UCLASS()
class DEMOUMG_API ADamager : public AActor
{
	GENERATED_BODY()

public:
	ADamager();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	int DamageAmount = 20;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UPrimitiveComponent *Collision = nullptr;

	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
