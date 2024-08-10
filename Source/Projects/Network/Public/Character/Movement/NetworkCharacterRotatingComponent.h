// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterRotatingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterRotatingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterRotatingComponent();

	void Rotate(const FVector2D Input) const;	

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;
};
