// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DemoEffectsCharacter.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CharacterAuraCastingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMOEFFECTS_API UCharacterAuraCastingComponent : public UActorComponent
{
	GENERATED_BODY()

public: 
	UCharacterAuraCastingComponent();
	
	void CastAura();
	bool GetIsCasting() const { return bIsCasting; }

protected: 
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	ADemoEffectsCharacter *Character = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FVector AuraSpawnLocation;

	UPROPERTY(EditDefaultsOnly)
	FVector AuraSpawnSize;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> AuraClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *AuraCastingMontage = nullptr;
	
	UPROPERTY()
	AActor *SpawnedAuraActor = nullptr;
	bool bIsCasting = false;
	bool bIsActive = false;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *AuraAppearingCurve = nullptr;
	FTimeline AuraAppearingTimeline;

	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	UFUNCTION()
	void OnTimelineUpdated(float Alpha);
};
