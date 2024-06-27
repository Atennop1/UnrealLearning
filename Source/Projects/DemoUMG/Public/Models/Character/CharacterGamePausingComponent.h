// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "CharacterGamePausingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMOUMG_API UCharacterGamePausingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnPauseActionTriggered(const FInputActionValue& Binding);
	
	UCharacterGamePausingComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY()
	UUserWidget *CreatedPauseWidget = nullptr;
};
