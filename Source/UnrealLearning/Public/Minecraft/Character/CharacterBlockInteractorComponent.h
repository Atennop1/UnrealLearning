// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "CharacterBlockInteractorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UCharacterBlockInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float LineTraceLength;
	
	UPROPERTY(EditDefaultsOnly)
	float Cooldown;
	bool CanDestroy = true;
	FTimerHandle CooldownTimerHandle;

public:
	UCharacterBlockInteractorComponent();
	void Interact(const FInputActionValue &Value);
};
