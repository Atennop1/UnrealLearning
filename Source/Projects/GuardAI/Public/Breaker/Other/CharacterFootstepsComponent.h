// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Breaker/BreakerCharacter.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include "CharacterFootstepsComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUARDAI_API UCharacterFootstepsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterFootstepsComponent();

	UFUNCTION(BlueprintCallable)
	void PlayFootstep();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	ABreakerCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<EPhysicalSurface>, USoundBase*> FootstepsSounds;
};
