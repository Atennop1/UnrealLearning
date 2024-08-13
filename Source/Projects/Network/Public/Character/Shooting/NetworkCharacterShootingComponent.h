// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterShootingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterShootingComponent();

	void Shoot() { ServerShoot(); }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;

	UPROPERTY()
	class UCameraComponent *Camera = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int Damage = 25;

	UFUNCTION(Server, Reliable)
	void ServerShoot();
	void ServerShoot_Implementation();
};
