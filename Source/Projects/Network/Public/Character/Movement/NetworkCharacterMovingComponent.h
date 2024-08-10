// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterMovingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterMovingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterMovingComponent();
	
	void Move(const FVector2D Input) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;
};
