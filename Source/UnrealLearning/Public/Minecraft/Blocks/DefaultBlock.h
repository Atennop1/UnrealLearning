// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IBlock.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "DefaultBlock.generated.h"

UCLASS()
class UNREALLEARNING_API ADefaultBlock : public AActor, public IBlock
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *Mesh;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface *MaterialInterface;

	UPROPERTY()
	UMaterialInstanceDynamic *MaterialInstance;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *DestroyingCurve;
	FTimeline DestroyingTimeline;
	
	UFUNCTION()
	void OnDestroyingTick(float Alpha);
	
	UFUNCTION()
	void OnDestroyingFinished();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	ADefaultBlock();
	
public:
	virtual void StartDestroying() override;
	virtual void StopDestroying() override;
};
