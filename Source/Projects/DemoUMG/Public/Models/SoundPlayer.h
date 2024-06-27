// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "SoundPlayer.generated.h"

UCLASS()
class DEMOUMG_API ASoundPlayer : public AActor
{
	GENERATED_BODY()

public:
	ASoundPlayer();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USoundBase *SoundToPlay = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UPrimitiveComponent *Collision = nullptr;

	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
