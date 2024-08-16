// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCharacterHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthUpdatingDelegate, int, NewHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETWORK_API UNetworkCharacterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetworkCharacterHealthComponent();

	FHealthUpdatingDelegate OnHealthUpdated;
	bool IsAlive() const { return CurrentHealth > 0; }
	
	void TakeDamage(int DamageAmount) { ServerTakeDamage(DamageAmount); }
	void Heal(int HealingAmount) { ServerHeal(HealingAmount); }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY()
	class ANetworkCharacter *Character = nullptr;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	int CurrentHealth;
	int MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly)
	int RespawningTime = 5;
	FTimerHandle RespawningHandle;

	UFUNCTION()
	void OnRep_CurrentHealth() const { OnHealthUpdated.Broadcast(CurrentHealth); }
	
	UFUNCTION(Server, Reliable)
	void ServerTakeDamage(int DamageAmount);
	void ServerTakeDamage_Implementation(int DamageAmount);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRagdoll();
	void MulticastRagdoll_Implementation();

	UFUNCTION(Client, Reliable)
	void ClientDeleteUI();
	void ClientDeleteUI_Implementation();

	UFUNCTION(Server, Reliable)
	void ServerHeal(int HealingAmount);
	void ServerHeal_Implementation(int HealingAmount);
};
