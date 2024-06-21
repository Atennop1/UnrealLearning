// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterPointingComponent.h"
#include "Components/ActorComponent.h"
#include "CharacterBlockPlacerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINECRAFT_API UCharacterBlockPlacerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float Cooldown;
	bool CanPlace = true;
	FTimerHandle CooldownTimerHandle;

	UPROPERTY()
	UCharacterPointingComponent *Pointing;
	
	UPROPERTY()
	TSubclassOf<AActor> BlockBlueprint;

protected:
	virtual void BeginPlay() override;
	UCharacterBlockPlacerComponent();
	
public:
	void Select(TSubclassOf<AActor> Block);
	void Place(const struct FInputActionValue &Value);	
};
