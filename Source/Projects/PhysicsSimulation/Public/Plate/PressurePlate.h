// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Activatable.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

UCLASS()
class PHYSICSSIMULATION_API APressurePlate : public AActor
{
	GENERATED_BODY()

public:
	APressurePlate();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent *Trigger = nullptr;
	int PressersCount = 0;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *Button = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *Frame = nullptr;
	
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess))
	AActor *ActivatableActor;

	UPROPERTY()
	TScriptInterface<IActivatable> Activatable;

	UPROPERTY(EditAnywhere)
	FVector ActivatedButtonRelativePosition;
	
	UPROPERTY(EditAnywhere)
	FVector DeactivatedButtonRelativePosition;

	UPROPERTY(EditAnywhere)
	UMaterial *ActivatedMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial *DeactivatedMaterial;

	UPROPERTY(EditAnywhere)
	UCurveFloat *ActivatingCurve;
	FTimeline ActivatingTimeline;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnActivatingTimelineUpdate(float Alpha) const;
};
