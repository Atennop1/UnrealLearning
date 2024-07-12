// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DemoEffectsCharacter.h"
#include "Components/ActorComponent.h"
#include "CharacterAuraCastingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMOEFFECTS_API UCharacterAuraCastingComponent : public UActorComponent
{
	GENERATED_BODY()

public: 
	UCharacterAuraCastingComponent();
	void CastAura();

protected: 
	virtual void BeginPlay() override;

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

	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
};
