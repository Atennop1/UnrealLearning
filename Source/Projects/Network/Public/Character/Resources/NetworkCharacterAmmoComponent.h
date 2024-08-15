// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterAmmoComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAmmoUpdatingDelegate, int, NewAmmo);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterAmmoComponent();
	FAmmoUpdatingDelegate OnAmmoUpdated;
	
	bool CanSpend(int AmmoAmount) const { return CurrentAmmo - AmmoAmount >= 0; }
	void Spend(int AmmoAmount) { ServerSpend(AmmoAmount); }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentAmmo)
	int CurrentAmmo;

	UPROPERTY(EditDefaultsOnly)
	int MaxAmmo = 25;

	UFUNCTION()
	void OnRep_CurrentAmmo() const
	{
		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, "Ammo");
		OnAmmoUpdated.Broadcast(CurrentAmmo);
	}
	
	UFUNCTION(Server, Reliable)
	void ServerSpend(int AmmoAmount);
	void ServerSpend_Implementation(int AmmoAmount);
};
