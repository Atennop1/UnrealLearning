// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterPointingComponent.h"
#include "Components/ActorComponent.h"
#include "CharacterBlockInteractorComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UCharacterBlockInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UCharacterPointingComponent *Pointing;

protected:
	virtual void BeginPlay() override;
	UCharacterBlockInteractorComponent();
	
public:
	void Interact(const struct FInputActionValue &Value);
};
