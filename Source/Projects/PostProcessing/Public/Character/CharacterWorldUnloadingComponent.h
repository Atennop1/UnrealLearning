// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ParameterChangingInfo.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CharacterWorldUnloadingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POSTPROCESSING_API UCharacterWorldUnloadingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterWorldUnloadingComponent();
	void ChangeWorldState();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bIsLoaded = true;
	FTimeline WorldUnloadingTimeline;

	UPROPERTY(EditDefaultsOnly)
	UMaterialParameterCollection *ParameterCollection = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FParameterChangingInfo UnlitChangingInfo { };

	UPROPERTY(EditDefaultsOnly)
	FParameterChangingInfo GreyChangingInfo { };
	
	UPROPERTY(EditDefaultsOnly)
	FParameterChangingInfo OutlineChangingInfo { };
	
	UPROPERTY(EditDefaultsOnly)
	FParameterChangingInfo DarknessChangingInfo { };

	UFUNCTION()
	void OnUnlitParameterChanged(float Amount);
	
	UFUNCTION()
	void OnGreyParameterChanged(float Amount);
	
	UFUNCTION()
	void OnOutlineParameterChanged(float Amount);
	
	UFUNCTION()
	void OnDarknessParameterChanged(float Amount);
};
