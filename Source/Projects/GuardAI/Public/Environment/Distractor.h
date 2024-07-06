// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Distractor.generated.h"

UCLASS()
class GUARDAI_API ADistractor : public AActor
{
	GENERATED_BODY()

public:
	ADistractor();

	bool GetCanDistract() const { return CanDistract; }
	void Distract();

private:
	UPROPERTY(EditAnywhere)
	float Loudness = 1;

	UPROPERTY(EditAnywhere)
	USoundBase *DistractSound = nullptr;

	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> DistractPositions;
	bool CanDistract = true;
};
