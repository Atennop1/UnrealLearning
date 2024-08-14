// Copyright Atennop. All Rights Reserved.

#include "Character/NetworkCharacterHealthComponent.h"
#include "NetworkGameMode.h"
#include "Character/NetworkCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

UNetworkCharacterHealthComponent::UNetworkCharacterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

void UNetworkCharacterHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(IsValid(Character));
}

void UNetworkCharacterHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(RespawningHandle);
}

void UNetworkCharacterHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UNetworkCharacterHealthComponent, CurrentHealth);
}

void UNetworkCharacterHealthComponent::ServerTakeDamage_Implementation(int DamageAmount)
{
	if (!IsAlive())
		return;

	CurrentHealth -= DamageAmount;
	if (!IsAlive())
		MulticastDeath(DamageAmount);
}

void UNetworkCharacterHealthComponent::MulticastDeath_Implementation(int DamageAmount)
{
	CurrentHealth = 0;
	Character->GetMesh()->SetSimulatePhysics(true);
	Character->GetCapsuleComponent()->DestroyComponent();
	
	GetWorld()->GetTimerManager().SetTimer(RespawningHandle, [&]
	{
		Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode())->Respawn(Character->GetController());
	}, RespawningTime, false);
}

void UNetworkCharacterHealthComponent::ServerHeal_Implementation(int HealingAmount)
{
	if (!IsAlive())
		return;
	
	CurrentHealth += HealingAmount;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}
