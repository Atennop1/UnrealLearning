// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ParameterChangingInfo.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CharacterMatrixComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POSTPROCESSING_API UCharacterMatrixComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterMatrixComponent();
	void ChangeMatrix();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bIsLoaded = true;
	FTimeline MatrixTimeline;

	UPROPERTY(EditDefaultsOnly)
	UMaterialParameterCollection *ParameterCollection = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FParameterChangingInfo MatrixChangingInfo { };

	UFUNCTION()
	void OnParameterChanged(float Amount);
};
