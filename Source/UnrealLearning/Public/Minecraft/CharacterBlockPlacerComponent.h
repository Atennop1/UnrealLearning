// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBlockPlacerComponent.generated.h"

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class UNREALLEARNING_API UCharacterBlockPlacerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category=BlockPlacing)
	float LineTraceLength;
	
	UCharacterBlockPlacerComponent();
	void PlaceBlock(const struct FInputActionValue &Value);	
};
