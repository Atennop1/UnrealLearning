// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "IBlock.h"
#include "DefaultBlock.generated.h"

UCLASS()
class MINECRAFT_API ADefaultBlock : public AActor, public IBlock
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *Mesh;
	
	UPROPERTY(EditDefaultsOnly)
	float DestroyingCurveSpeed;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *DestroyingCurve;
	FTimeline DestroyingTimeline;

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance;
	
	UFUNCTION()
	void OnDestroyingTick(float Alpha) const;
	
	UFUNCTION()
	void OnDestroyingFinished();

protected:
	UStaticMeshComponent* GetMesh() const { return Mesh; }
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	ADefaultBlock();
	
public:
	virtual void StartDestroying() override;
	virtual void StopDestroying() override;
};
