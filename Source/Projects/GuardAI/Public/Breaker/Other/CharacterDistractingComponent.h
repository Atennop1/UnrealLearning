// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Environment/Distractor.h"
#include "CharacterDistractingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterDistractingComponent : public UActorComponent
{
	GENERATED_BODY()

public: 
	UCharacterDistractingComponent();
	void Distract();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	class ABreakerCharacter *Character = nullptr;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	ADistractor *CurrentDistractor = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float CheckingSphereRadius = 300;

	UPROPERTY(EditDefaultsOnly)
	float MaximumDistance = 750;

	void ClearDistractor();
	void SetDistractor(ADistractor *NewDistractor);
};
