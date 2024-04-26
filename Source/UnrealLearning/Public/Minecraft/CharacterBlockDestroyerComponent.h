// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBlockDestroyerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UCharacterBlockDestroyerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float LineTraceLength;
	
	UPROPERTY(EditDefaultsOnly)
	float Cooldown;
	bool CanPlace = true;
	FTimerHandle CooldownTimerHandle;
	
	UCharacterBlockDestroyerComponent();

public:
	void DestroyBlock(const struct FInputActionValue &Value);
};
