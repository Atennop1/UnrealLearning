// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/AmbientSound.h"
#include "AmbientZone.generated.h"

UCLASS()
class DEMOSOUND_API AAmbientZone : public AActor
{
	GENERATED_BODY()

public:
	AAmbientZone();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent *TriggerBox;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	FName NoneName = "Nothing";
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	FName TriggerName = "";
	
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess))
	AAmbientSound *Ambient = nullptr;

	UFUNCTION() 
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() 
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
