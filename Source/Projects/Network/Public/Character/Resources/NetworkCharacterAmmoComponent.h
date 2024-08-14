// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterAmmoComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterAmmoComponent();
	
	bool CanSpend(int AmmoAmount) const { return CurrentAmmo - AmmoAmount >= 0; }
	void Spend(int AmmoAmount) { ServerSpend(AmmoAmount); }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;

	UPROPERTY(Replicated)
	int CurrentAmmo;

	UPROPERTY(EditDefaultsOnly)
	int MaxAmmo = 25;

	UFUNCTION(Server, Reliable)
	void ServerSpend(int AmmoAmount);
	void ServerSpend_Implementation(int AmmoAmount);
};
