// Copyright Atennop. All Rights Reserved.

#include "Character/Resources/NetworkCharacterAmmoComponent.h"
#include "Character/NetworkCharacter.h"
#include "Net/UnrealNetwork.h"

UNetworkCharacterAmmoComponent::UNetworkCharacterAmmoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentAmmo = MaxAmmo;
}

void UNetworkCharacterAmmoComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ANetworkCharacter>(GetOwner());
	check(IsValid(Character));
}

void UNetworkCharacterAmmoComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UNetworkCharacterAmmoComponent, CurrentAmmo);
}

void UNetworkCharacterAmmoComponent::ServerSpend_Implementation(int AmmoAmount)
{
	if (!CanSpend(AmmoAmount))
		return;

	CurrentAmmo -= AmmoAmount;
}
