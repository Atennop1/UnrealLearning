// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "NetworkCharacterPeekingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterPeekingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterPeekingComponent();

	void StartPeekingLeft() { PeekingLeftTimeline.Play(); }
	void StopPeekingLeft() { PeekingLeftTimeline.Reverse(); }

	void StartPeekingRight() { PeekingRightTimeline.Play(); }
	void StopPeekingRight() { PeekingRightTimeline.Reverse(); }
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	class UCameraComponent *Camera = nullptr;
	FVector NormalCameraRelativeLocation;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *PeekingCurve = nullptr;
	FTimeline PeekingLeftTimeline;
	FTimeline PeekingRightTimeline;

	UPROPERTY(EditDefaultsOnly)
	float PeekingAmount = 60;
	float CurrentLeftPeekingAmount = 0;
	float CurrentRightPeekingAmount = 0;

	UFUNCTION()
	void PeekingLeftUpdate(float Alpha);

	UFUNCTION()
	void PeekingRightUpdate(float Alpha);
};
