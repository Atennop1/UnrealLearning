// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class UNREALLEARNING_API APortal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneCaptureComponent2D *Capture1;

	UPROPERTY(EditDefaultsOnly)
	USceneCaptureComponent2D *Capture2;

public:
	APortal();
};
