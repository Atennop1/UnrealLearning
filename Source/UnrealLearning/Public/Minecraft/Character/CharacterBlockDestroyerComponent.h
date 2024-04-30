// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterPointingComponent.h"
#include "Components/ActorComponent.h"
#include "CharacterBlockDestroyerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UCharacterBlockDestroyerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float Cooldown;
	bool CanDestroy = true;
	FTimerHandle CooldownTimerHandle;

	UPROPERTY()
	UCharacterPointingComponent *Pointing;

	UPROPERTY()
	TScriptInterface<IBlock> CurrentBlock;

protected:
	virtual void BeginPlay() override;
	UCharacterBlockDestroyerComponent();
	
public:
	void StartDestroying(const struct FInputActionValue &Value);
	void StopDestroying(const FInputActionValue &Value);
};
