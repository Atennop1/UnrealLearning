// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterHealthComponent();
	bool IsAlive() const { return CurrentHealth > 0; }
	
	void TakeDamage(int DamageAmount) { ServerTakeDamage(DamageAmount); }
	void Heal(int HealingAmount) { ServerHeal(HealingAmount); }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;

	UPROPERTY(Replicated)
	int CurrentHealth;
	int MaxHealth = 100;

	UFUNCTION(Server, Reliable)
	void ServerTakeDamage(int DamageAmount);
	void ServerTakeDamage_Implementation(int DamageAmount);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastDeath(int DamageAmount);
	void MulticastDeath_Implementation(int DamageAmount);

	UFUNCTION(Server, Reliable)
	void ServerHeal(int HealingAmount);
	void ServerHeal_Implementation(int HealingAmount);
};
