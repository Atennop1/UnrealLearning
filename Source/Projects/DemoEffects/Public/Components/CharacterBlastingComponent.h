// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DemoEffectsCharacter.h"
#include "Components/ActorComponent.h"
#include "CharacterBlastingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMOEFFECTS_API UCharacterBlastingComponent : public UActorComponent
{
	GENERATED_BODY()

public: 
	UCharacterBlastingComponent();
	
	void Blast();
	bool GetIsBlasting() const { return bIsBlasting; }

protected: 
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ADemoEffectsCharacter *Character = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FVector BlastSpawnLocation;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BlastClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *BlastingMontage = nullptr;
	bool bIsBlasting = false;

	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
};
