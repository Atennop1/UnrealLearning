// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterJumpingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterJumpingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterJumpingComponent();

	void StartJumping() const;
	void StopJumping() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;
};
