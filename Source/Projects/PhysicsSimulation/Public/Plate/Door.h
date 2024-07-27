// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Activatable.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class PHYSICSSIMULATION_API ADoor : public AActor, public IActivatable
{
	GENERATED_BODY()

public:
	ADoor();

	virtual void Activate() override;
	virtual void Deactivate() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float ClosedRotationZ = 0;

	UPROPERTY(EditAnywhere)
	float OpenedRotationZ = 110;

	UPROPERTY(EditAnywhere)
	UCurveFloat *Curve = nullptr;
	FTimeline OpeningTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStaticMeshComponent *DoorMesh = nullptr;

	UFUNCTION()
	void OnTimelineUpdated(float Alpha) const;
};
