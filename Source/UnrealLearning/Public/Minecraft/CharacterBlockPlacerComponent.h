// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBlockPlacerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UCharacterBlockPlacerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	bool Debug;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceLength;

	UPROPERTY(EditDefaultsOnly)
	float Cooldown;
	bool CanPlace = true;
	FTimerHandle CooldownTimerHandle;

	UPROPERTY()
	TSubclassOf<AActor> BlockBlueprint;
	
	UCharacterBlockPlacerComponent();
	
public:
	void Select(TSubclassOf<AActor> Block);
	void Place(const struct FInputActionValue &Value);	
};
