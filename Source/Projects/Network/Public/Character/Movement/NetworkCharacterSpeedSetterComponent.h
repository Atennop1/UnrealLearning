// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterSpeedSetterComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterSpeedSetterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterSpeedSetterComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,  FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 600;

	UPROPERTY(EditDefaultsOnly)
	float CrouchSpeed = 300;
};
