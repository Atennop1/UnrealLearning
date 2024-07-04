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
	void Distract() const;

private:
	UPROPERTY(EditAnywhere)
	float Loudness = 1;
};
