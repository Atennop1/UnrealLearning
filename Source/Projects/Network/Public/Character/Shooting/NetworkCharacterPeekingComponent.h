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

	void StartPeekingLeft() { ServerStartPeekingLeft(); }
	void StopPeekingLeft() { ServerStopPeekingLeft(); }

	void StartPeekingRight() { ServerStartPeekingRight(); }
	void StopPeekingRight() { ServerStopPeekingRight(); }
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;
	
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

	UFUNCTION(Server, Reliable)
	void ServerStartPeekingLeft();
	void ServerStartPeekingLeft_Implementation() { MulticastStartPeekingLeft(); }

	UFUNCTION(Server, Reliable)
	void ServerStopPeekingLeft();
	void ServerStopPeekingLeft_Implementation() { MulticastStopPeekingLeft(); }

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartPeekingLeft();
	void MulticastStartPeekingLeft_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStopPeekingLeft();
	void MulticastStopPeekingLeft_Implementation() { PeekingLeftTimeline.Reverse(); }

	UFUNCTION(Server, Reliable)
	void ServerStartPeekingRight();
	void ServerStartPeekingRight_Implementation() { MulticastStartPeekingRight(); }

	UFUNCTION(Server, Reliable)
	void ServerStopPeekingRight();
	void ServerStopPeekingRight_Implementation() { MulticastStopPeekingRight(); }

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartPeekingRight();
	void MulticastStartPeekingRight_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStopPeekingRight();
	void MulticastStopPeekingRight_Implementation() { PeekingRightTimeline.Reverse(); }
};
