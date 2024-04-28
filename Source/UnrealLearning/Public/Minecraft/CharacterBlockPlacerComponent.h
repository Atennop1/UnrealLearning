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
	TSubclassOf<AActor> BlockBlueprint;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceLength;

	UPROPERTY(EditDefaultsOnly)
	float Cooldown;
	bool CanPlace = true;
	FTimerHandle CooldownTimerHandle;
	
	UCharacterBlockPlacerComponent();
	
public:
	void PlaceBlock(const struct FInputActionValue &Value);	
};
