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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	UPROPERTY()
	ABreakerCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundCue *FootstepsCue = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float FootstepCooldown = 0.2f;
	bool CanFootstep = true;
	FTimerHandle FootstepCooldownHandle;
};
