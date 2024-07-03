// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/GuardController.h"
#include "Perception/AIPerceptionComponent.h"
#include "GuardPerception.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UGuardPerception : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	UGuardPerception();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float LoosingTargetTime = 3.0f;

	UPROPERTY(EditDefaultsOnly)
	FName IsHearingPlayerVariableName = "IsHearingPlayer";
	
	UPROPERTY(EditDefaultsOnly)
	FName CanSeePlayerVariableName = "CanSeePlayer";
	
	UPROPERTY(EditDefaultsOnly)
	FName TargetVariableName = "TargetActor";

	UPROPERTY(EditDefaultsOnly)
	FName NoiseLocationVariableName = "NoiseLocation";

	UPROPERTY(EditDefaultsOnly)
	FName PredictionLocationVariableName = "PredictionLocation";

	UPROPERTY()
	AActor *SensedActor = nullptr;
	
	UPROPERTY()
	AGuardController *Controller = nullptr;
	FTimerHandle ChasingTimerHandle;
	
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
