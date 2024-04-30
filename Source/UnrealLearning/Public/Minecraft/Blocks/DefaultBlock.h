// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "IBlock.h"
#include "DefaultBlock.generated.h"

UCLASS()
class UNREALLEARNING_API ADefaultBlock : public AActor, public IBlock
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *Mesh;
	
	UPROPERTY(EditDefaultsOnly)
	float CurveSpeed;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *DestroyingCurve;
	FTimeline DestroyingTimeline;

	UPROPERTY()
	UMaterialInstanceDynamic *MaterialInstance;
	
	UFUNCTION()
	void OnDestroyingTick(float Alpha);
	
	UFUNCTION()
	void OnDestroyingFinished();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	ADefaultBlock();
	virtual void StartDestroying() override;
	virtual void StopDestroying() override;
};
