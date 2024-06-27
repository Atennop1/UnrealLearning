// Copyright Atennop. All Rights Reserved.

#include "Models/Health/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	OnHealthChanged.Execute(CurrentHealth, MaxHealth);
}

void UHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnHealthChanged.Unbind();
}

void UHealthComponent::Damage(const int DamageAmount)
{
	if (bIsDead)
		return;
	
	CurrentHealth -= DamageAmount;
	OnHealthChanged.Execute(CurrentHealth, MaxHealth);
	
	if (CurrentHealth > 0)
		return;

	bIsDead = true;
	CurrentHealth = 0;
	GetOwner()->Destroy();
}

void UHealthComponent::Heal(const int HealAmount)
{
	if (bIsDead)
		return;
	
	CurrentHealth += HealAmount;
	if (CurrentHealth >= MaxHealth)
		CurrentHealth = MaxHealth;

	OnHealthChanged.Execute(CurrentHealth, MaxHealth);
}
