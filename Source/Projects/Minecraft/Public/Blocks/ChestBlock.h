// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DefaultBlock.h"
#include "IInteractableBlock.h"
#include "GameFramework/Actor.h"
#include "ChestBlock.generated.h"

UCLASS()
class MINECRAFT_API AChestBlock : public ADefaultBlock, public IInteractableBlock
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *OpeningCurve;
	FTimeline OpeningTimeline;
	bool IsOpened = false;

	UPROPERTY()
	USceneComponent *LidPivot;

	UFUNCTION()
	void OnTimelineTick(float Value) const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	AChestBlock();
	
public:
	virtual void Interact() override;
	virtual void StartDestroying() override { Super::StartDestroying(); }
	virtual void StopDestroying() override { Super::StopDestroying(); }
};
