// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blocks/IBlock.h"
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
	bool CanDestroy = true;
	FTimerHandle CooldownTimerHandle;

	UPROPERTY()
	TScriptInterface<IBlock> CurrentBlock = TScriptInterface<IBlock>();
	
	UCharacterBlockDestroyerComponent();

public:
	void StartBlockDestroying(const struct FInputActionValue &Value);
	void StopBlockDestroying(const FInputActionValue &Value);
};
