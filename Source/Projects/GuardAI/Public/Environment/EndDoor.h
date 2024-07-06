// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "EndDoor.generated.h"

UCLASS()
class GUARDAI_API AEndDoor : public AActor
{
	GENERATED_BODY()

public:
	AEndDoor();

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
	void OnTimelineUpdated(float Alpha);
};
