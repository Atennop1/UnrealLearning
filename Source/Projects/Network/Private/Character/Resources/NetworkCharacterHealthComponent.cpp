// Copyright Atennop. All Rights Reserved.

#include "Character/Resources/NetworkCharacterHealthComponent.h"
#include "NetworkGameMode.h"
#include "Character/NetworkCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"
#include "UI/NetworkHUD.h"

UNetworkCharacterHealthComponent::UNetworkCharacterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
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
	if (IsAlive())
		return;
	
	CurrentHealth = 0;
	MulticastRagdoll();
	ClientDeleteUI();
	
	GetWorld()->GetTimerManager().SetTimer(RespawningHandle, [&]
	{
		Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode())->Respawn(Character->GetController());
	}, RespawningTime, false);
}

void UNetworkCharacterHealthComponent::MulticastRagdoll_Implementation()
{
	Character->GetMesh()->SetSimulatePhysics(true);
	Character->GetCapsuleComponent()->DestroyComponent();
}

void UNetworkCharacterHealthComponent::ClientDeleteUI_Implementation()
{
	CastChecked<ANetworkHUD>(CastChecked<APlayerController>(Character->GetController())->GetHUD())->DestroyUI();
}

void UNetworkCharacterHealthComponent::ServerHeal_Implementation(int HealingAmount)
{
	if (!IsAlive())
		return;
	
	CurrentHealth += HealingAmount;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}
