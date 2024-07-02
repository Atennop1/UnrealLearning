// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CharacterCrouchingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterCrouchingComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UCharacterCrouchingComponent();

	void StartCrouching();
	void StopCrouching();

	UFUNCTION(BlueprintCallable)
	bool GetIsCrouching() const { return IsCrouching; }
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	class ABreakerCharacter *Character = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *CrouchingCurve = nullptr;
	FTimeline CrouchingTimeline;
	bool IsCrouching = false;

	UPROPERTY(EditDefaultsOnly)
	float CrouchedHalfHeight = 50;
	float NormalHalfHeight = 100;

	UFUNCTION()
	void CrouchUpdate(float Alpha) const;
};
