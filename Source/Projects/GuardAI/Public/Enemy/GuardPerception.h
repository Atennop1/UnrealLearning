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

private:
	UPROPERTY()
	AGuardController *Controller = nullptr;
	
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
