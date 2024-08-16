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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;

	UPROPERTY()
	class UCameraComponent *Camera = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int Damage = 25;

	UPROPERTY(EditDefaultsOnly)
	float DelayTime = 0.3;
	bool CanShoot = true;
	FTimerHandle DelayHandle;

	UFUNCTION(Server, Reliable)
	void ServerShoot();
	void ServerShoot_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastShoot();
	void MulticastShoot_Implementation();
};
